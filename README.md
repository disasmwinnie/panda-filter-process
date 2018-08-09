Plugin: panda-itaint
===========

Summary
-------
This is a test plugin for panda2 which explores process filtering capabilities.


Arguments
---------

Dependencies
------------
It depends on the **osi**, **osi\_linux** and **syscalls2** plugins And, **taint2** plugin is also included since, otherwise compilation fails. Compile error:

```bash
// here every osi is affected
[...]
/home/winnie/git/panda/panda/plugins/syscalls2/syscalls2.h:10:59: error: ‘target_ulong’ has not been declared
 void syscall_return_switch_windows_7_x86 ( CPUState *env, target_ulong pc, target_ulong ordinal, ReturnPoint &rp);
^
/home/winnie/git/panda/panda/plugins/syscalls2/syscalls2.h:10:76: error: ‘target_ulong’ has not been declared
 void syscall_return_switch_windows_7_x86 ( CPUState *env, target_ulong pc, target_ulong ordinal, ReturnPoint &rp);

home/winnie/git/panda/panda/plugins/syscalls2/syscalls2.h:11:62: error: ‘target_ulong’ has not been declared
void syscall_return_switch_windows_2000_x86 ( CPUState *env, target_ulong pc, target_ulong ordinal, ReturnPoint &rp);
^
[...]
```

Known Issues
------------------


Example
-------

```bash
 $PANDABIN -hda $PATHTOVMS/debian7_x86.qcow2 -monitor telnet:localhost:2222,server,nowait -vga std -display sdl -m 512 -netdev user,id=eth11,hostfwd=tcp::1122-:22 -device rtl8139,netdev=eth11 -replay ~/BIND9 -os linux-32-debian-3.2.81-686-pae -panda panda-filter-process

> [...]
> [FILTER-PROCESS](NFO): `a
> [FILTER-PROCESS](NFO): ASID changed, previous process name was:
> [FILTER-PROCESS](NFO): `a
>  /home/winnie/BIND9-rr-nondet.log:  log is empty.
> /home/winnie/BIND9-rr-nondet.log:  log is empty.
> Replay completed successfully. 1
> Time taken was: 4 seconds.
> Stats:
> RR_INPUT_1 number = 0, size = 0 bytes
> RR_INPUT_2 number = 0, size = 0 bytes
> RR_INPUT_4 number = 1738, size = 24332 bytes
> RR_INPUT_8 number = 24349, size = 438282 bytes
> RR_INTERRUPT_REQUEST number = 2934, size = 41076 bytes
> RR_EXIT_REQUEST number = 0, size = 0 bytes
> RR_SKIPPED_CALL number = 464, size = 152097 bytes
> RR_END_OF_LOG number = 1, size = 10 bytes
> RR_PENDING_INTERRUPTS number = 0, size = 0 bytes
> RR_EXCEPTION number = 0, size = 0 bytes
> max_queue_len = 161
> Checksum of guest memory: 0x7c8bc60b
> Replay completed successfully 2.
> exiting loop in cpus.c. 
> [FILTER-PROCESS](NFO): EXECUTED PROCESSES DURING TRACE:
> `a      zo `m `k `l   `c `d `e   `g     w,,  p+, , `*, `!þ `%þ `-, 
```

The result above is bogus.
