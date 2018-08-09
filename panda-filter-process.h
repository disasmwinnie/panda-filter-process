/**
 *
 * Authors:
 * Sergej Schmidt          sergejNOSPAMmsgpeek.net
 *
 * This work is licensed under the terms of the GNU GPL, version 2.
 * See the LICENSE file in the top-level directory.
 */

#ifndef PANDA_FILTER_PROCESS_H_
#define PANDA_FILTER_PROCESS_H_

// This needs to be defined before anything is included in order to get
// the PRIx64 macro
#define __STDC_FORMAT_MACROS

#include <iostream>
#include <string>
#include <list>
#include <algorithm>


/* Sideproblem: This is weird, if I let this include out, then "target_ulong"
 * is not defined. Wtf? */
#include "taint2/taint2.h"

#include "syscalls2/syscalls2.h"
#include "panda/plugin.h"
#include "panda/plugin_plugin.h"

// These need to be extern "C" so that the ABI is compatible with
// QEMU/PANDA, which is written in C
extern "C" {

#include "osi/osi_types.h"
#include "osi/osi_ext.h"

#include "osi_linux/osi_linux_ext.h"

#include "syscalls2/gen_syscalls_ext_typedefs.h"


bool
init_plugin(void *);

void
uninit_plugin(void *);
}

#define MAX_FILENAME_LEN 40

int
on_asid_change(CPUState *cpu, target_ulong old_pgd, target_ulong new_pgd);

void
collect_proc_names(CPUState* cpu, TranslationBlock* tb);

void
set_current_proc_name(CPUState* cpu);

std::string
current_proc_name;

std::list<std::string>
proc_names;
#endif
