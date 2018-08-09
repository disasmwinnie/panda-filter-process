/**
 *
 * Authors:
 * Sergej Schmidt          sergejNOSPAMmsgpeek.net
 *
 * This work is licensed under the terms of the GNU GPL, version 2.
 * See the LICENSE file in the top-level directory.
 */

#include "panda-filter-process.h"

void
ERR(std::string msg) {
    std::cerr << "[FILTER-PROCESS](ERR): " << msg << std:: endl;
}

void
NFO(std::string msg) {
    std::cout << "[FILTER-PROCESS](NFO): " << msg << std:: endl;
}

bool
init_plugin(void *self) {
  std::cout << "--]] panda-filter-process plugin loaded [[--" << std::endl;
  panda_require("osi");
  assert(init_osi_api());

  panda_require("osi_linux");
  assert(init_osi_linux_api());

  if( panda_os_familyno != OS_LINUX )
  {
    ERR("FILTER-PROCESS only supports GNU/Linux guests.");
    return false;
  }

  panda_cb pcb = { .asid_changed = on_asid_change };
  panda_register_callback(self, PANDA_CB_ASID_CHANGED, pcb);
  return true;
}

void uninit_plugin(void *self)
{
  NFO("EXECUTED PROCESSES DURING TRACE:");
  for( auto it=proc_names.begin(); it != proc_names.end(); ++it )
  {
    std::cout << *it << ", ";
  }
  std::cout << std::endl;
}

int
on_asid_change(CPUState *cpu, target_ulong old_pgd, target_ulong new_pgd)
{
  NFO("ASID changed, previous process name was:");
  NFO(current_proc_name);
  collect_proc_names(cpu, NULL);
  set_current_proc_name(cpu);
	return 0;
}

void
collect_proc_names(CPUState* cpu, TranslationBlock* tb)
{
  OsiProc *cp = get_current_process(cpu);
  if(cp == NULL || cp->name == 0 || cp->offset == 0) {
    ERR("Failed to get the process name.");  // causes to much noise
    free_osiproc(cp);
    return; // can possibly fail
  }

  std::string pn = std::string(cp->name);

  // Only unique ones
  auto it =  std::find(proc_names.begin(), proc_names.end(), pn);
  if( it == proc_names.end() )
  {
    proc_names.push_back(pn);
  }
}

void
set_current_proc_name(CPUState* cpu) {
  OsiProc *cp = get_current_process(cpu);

  if(cp == NULL || cp->name == 0 || cp->offset == 0) {
    free_osiproc(cp);
    ERR("Could not set process name.");
    return;
  }
  current_proc_name = std::string(cp->name);
}
