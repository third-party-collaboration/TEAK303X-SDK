cmd_/home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_82571.o := gcc -Wp,-MD,/home/My_project/oak3030/e1000e-0.5.18.3/src/.e1000_82571.o.d  -nostdinc -isystem /usr/lib/gcc/i386-redhat-linux/4.0.2/include -D__KERNEL__ -Iinclude  -include include/linux/autoconf.h -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -O2 -pipe -msoft-float -mpreferred-stack-boundary=2  -march=i686 -mtune=pentium3  -ffreestanding -Iinclude/asm-i386/mach-default -fno-omit-frame-pointer -fno-optimize-sibling-calls -g  -Wdeclaration-after-statement -Wno-pointer-sign -DDRIVER_E1000E -DDRIVER_NAME=e1000e -DDRIVER_NAME_CAPS=E1000E -DLINUX -D__KERNEL__ -DMODULE -O2 -pipe -Wall -I/lib/modules/2.6.18/build/include -I.     -DMODULE -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(e1000_82571)"  -D"KBUILD_MODNAME=KBUILD_STR(e1000e)" -c -o /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_82571.o /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_82571.c

deps_/home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_82571.o := \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_82571.c \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000.h \
    $(wildcard include/config/e1000e/msix.h) \
    $(wildcard include/config/e1000e/napi.h) \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/resources/64bit.h) \
  include/linux/posix_types.h \
  include/linux/stddef.h \
  include/linux/compiler.h \
  include/linux/compiler-gcc4.h \
    $(wildcard include/config/forced/inlining.h) \
  include/linux/compiler-gcc.h \
  include/asm/posix_types.h \
  include/asm/types.h \
    $(wildcard include/config/highmem64g.h) \
    $(wildcard include/config/lbd.h) \
    $(wildcard include/config/lsf.h) \
  include/asm/io.h \
    $(wildcard include/config/x86/oostore.h) \
    $(wildcard include/config/x86/ppro/fence.h) \
    $(wildcard include/config/x86/numaq.h) \
  include/linux/string.h \
  include/asm/string.h \
    $(wildcard include/config/x86/use/3dnow.h) \
  include/asm-generic/iomap.h \
  include/linux/linkage.h \
  include/asm/linkage.h \
    $(wildcard include/config/x86/alignment/16.h) \
  include/asm/byteorder.h \
    $(wildcard include/config/x86/bswap.h) \
  include/linux/byteorder/little_endian.h \
  include/linux/byteorder/swab.h \
  include/linux/byteorder/generic.h \
  include/linux/vmalloc.h \
  include/linux/spinlock.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/debug/lock/alloc.h) \
  include/linux/preempt.h \
    $(wildcard include/config/debug/preempt.h) \
  include/linux/thread_info.h \
  include/linux/bitops.h \
  include/asm/bitops.h \
  include/asm/alternative.h \
  include/asm-generic/bitops/sched.h \
  include/asm-generic/bitops/hweight.h \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/ext2-non-atomic.h \
  include/asm-generic/bitops/le.h \
  include/asm-generic/bitops/minix.h \
  include/asm/thread_info.h \
    $(wildcard include/config/4kstacks.h) \
    $(wildcard include/config/debug/stack/usage.h) \
  include/asm/page.h \
    $(wildcard include/config/x86/pae.h) \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/highmem4g.h) \
    $(wildcard include/config/page/offset.h) \
    $(wildcard include/config/physical/start.h) \
    $(wildcard include/config/flatmem.h) \
  include/asm-generic/memory_model.h \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem.h) \
    $(wildcard include/config/out/of/line/pfn/to/page.h) \
  include/asm-generic/page.h \
  include/asm/processor.h \
    $(wildcard include/config/x86/ht.h) \
    $(wildcard include/config/mk8.h) \
    $(wildcard include/config/mk7.h) \
  include/asm/vm86.h \
    $(wildcard include/config/vm86.h) \
  include/asm/math_emu.h \
  include/asm/sigcontext.h \
  include/asm/segment.h \
  include/asm/cpufeature.h \
  include/asm/msr.h \
  include/asm/system.h \
    $(wildcard include/config/x86/cmpxchg64.h) \
    $(wildcard include/config/x86/cmpxchg.h) \
  include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/printk.h) \
  /usr/lib/gcc/i386-redhat-linux/4.0.2/include/stdarg.h \
  include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  include/asm-generic/bug.h \
  include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
    $(wildcard include/config/x86.h) \
  include/asm/irqflags.h \
  include/linux/cache.h \
  include/asm/cache.h \
    $(wildcard include/config/x86/l1/cache/shift.h) \
  include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  include/asm/percpu.h \
  include/asm-generic/percpu.h \
  include/linux/cpumask.h \
    $(wildcard include/config/hotplug/cpu.h) \
  include/linux/bitmap.h \
  include/linux/stringify.h \
  include/linux/spinlock_types.h \
  include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/generic/hardirqs.h) \
    $(wildcard include/config/prove/locking.h) \
  include/linux/list.h \
  include/linux/poison.h \
  include/linux/prefetch.h \
  include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  include/linux/stacktrace.h \
    $(wildcard include/config/stacktrace.h) \
  include/linux/spinlock_types_up.h \
  include/linux/spinlock_up.h \
  include/linux/spinlock_api_up.h \
  include/asm/atomic.h \
    $(wildcard include/config/m386.h) \
  include/asm-generic/atomic.h \
  include/linux/netdevice.h \
    $(wildcard include/config/ax25.h) \
    $(wildcard include/config/ax25/module.h) \
    $(wildcard include/config/tr.h) \
    $(wildcard include/config/net/ipip.h) \
    $(wildcard include/config/ipv6.h) \
    $(wildcard include/config/ipv6/module.h) \
    $(wildcard include/config/netpoll.h) \
    $(wildcard include/config/net/poll/controller.h) \
    $(wildcard include/config/net/divert.h) \
    $(wildcard include/config/netpoll/trap.h) \
    $(wildcard include/config/net/dma.h) \
    $(wildcard include/config/proc/fs.h) \
  include/linux/if.h \
  include/linux/socket.h \
    $(wildcard include/config/compat.h) \
  include/asm/socket.h \
  include/asm/sockios.h \
  include/linux/sockios.h \
  include/linux/uio.h \
  include/linux/hdlc/ioctl.h \
  include/linux/if_ether.h \
    $(wildcard include/config/sysctl.h) \
  include/linux/skbuff.h \
    $(wildcard include/config/netfilter.h) \
    $(wildcard include/config/bridge/netfilter.h) \
    $(wildcard include/config/vlan/8021q.h) \
    $(wildcard include/config/vlan/8021q/module.h) \
    $(wildcard include/config/nf/conntrack.h) \
    $(wildcard include/config/nf/conntrack/module.h) \
    $(wildcard include/config/net/sched.h) \
    $(wildcard include/config/net/cls/act.h) \
    $(wildcard include/config/network/secmark.h) \
    $(wildcard include/config/highmem.h) \
  include/linux/time.h \
  include/linux/seqlock.h \
  include/linux/mm.h \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/shmem.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/debug/pagealloc.h) \
  include/linux/sched.h \
    $(wildcard include/config/detect/softlockup.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/pm.h) \
  include/linux/auxvec.h \
  include/asm/auxvec.h \
  include/asm/param.h \
    $(wildcard include/config/hz.h) \
  include/linux/capability.h \
  include/asm/current.h \
  include/linux/timex.h \
    $(wildcard include/config/time/interpolation.h) \
  include/asm/timex.h \
    $(wildcard include/config/x86/elan.h) \
  include/asm/tsc.h \
    $(wildcard include/config/x86/tsc.h) \
    $(wildcard include/config/x86/generic.h) \
  include/linux/config.h \
    $(wildcard include/config/h.h) \
  include/linux/jiffies.h \
  include/linux/calc64.h \
  include/asm/div64.h \
  include/linux/rbtree.h \
  include/linux/errno.h \
  include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \
  include/linux/nodemask.h \
  include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/asm/semaphore.h \
  include/linux/wait.h \
  include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  include/asm/rwsem.h \
  include/asm/ptrace.h \
    $(wildcard include/config/frame/pointer.h) \
  include/asm/mmu.h \
  include/asm/cputime.h \
  include/asm-generic/cputime.h \
  include/linux/smp.h \
  include/linux/sem.h \
    $(wildcard include/config/sysvipc.h) \
  include/linux/ipc.h \
  include/asm/ipcbuf.h \
  include/asm/sembuf.h \
  include/linux/signal.h \
  include/asm/signal.h \
  include/asm-generic/signal.h \
  include/asm/siginfo.h \
  include/asm-generic/siginfo.h \
  include/linux/securebits.h \
  include/linux/fs_struct.h \
  include/linux/completion.h \
  include/linux/pid.h \
  include/linux/rcupdate.h \
  include/linux/percpu.h \
  include/linux/slab.h \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/debug/slab.h) \
  include/linux/gfp.h \
    $(wildcard include/config/dma/is/dma32.h) \
  include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
    $(wildcard include/config/acpi/hotplug/memory.h) \
    $(wildcard include/config/acpi/hotplug/memory/module.h) \
  include/linux/memory_hotplug.h \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
  include/linux/notifier.h \
  include/linux/mutex.h \
  include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
  include/asm/topology.h \
  include/asm-generic/topology.h \
  include/linux/kmalloc_sizes.h \
    $(wildcard include/config/large/allocs.h) \
  include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
  include/linux/futex.h \
    $(wildcard include/config/futex.h) \
  include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  include/linux/param.h \
  include/linux/resource.h \
  include/asm/resource.h \
  include/asm-generic/resource.h \
  include/linux/timer.h \
  include/linux/hrtimer.h \
    $(wildcard include/config/no/idle/hz.h) \
  include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  include/linux/aio.h \
  include/linux/workqueue.h \
  include/linux/aio_abi.h \
  include/linux/sysdev.h \
  include/linux/kobject.h \
  include/linux/sysfs.h \
    $(wildcard include/config/sysfs.h) \
  include/linux/kref.h \
  include/linux/pm.h \
  include/linux/prio_tree.h \
  include/linux/fs.h \
    $(wildcard include/config/dnotify.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/inotify.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
    $(wildcard include/config/security.h) \
  include/linux/limits.h \
  include/linux/ioctl.h \
  include/asm/ioctl.h \
  include/asm-generic/ioctl.h \
  include/linux/kdev_t.h \
  include/linux/dcache.h \
    $(wildcard include/config/profiling.h) \
  include/linux/stat.h \
  include/asm/stat.h \
  include/linux/radix-tree.h \
  include/linux/quota.h \
  include/linux/dqblk_xfs.h \
  include/linux/dqblk_v1.h \
  include/linux/dqblk_v2.h \
  include/linux/nfs_fs_i.h \
  include/linux/nfs.h \
  include/linux/sunrpc/msg_prot.h \
  include/linux/fcntl.h \
  include/asm/fcntl.h \
  include/asm-generic/fcntl.h \
    $(wildcard include/config/64bit.h) \
  include/linux/err.h \
  include/asm/pgtable.h \
    $(wildcard include/config/highpte.h) \
  include/asm/fixmap.h \
    $(wildcard include/config/x86/local/apic.h) \
    $(wildcard include/config/x86/io/apic.h) \
    $(wildcard include/config/x86/visws/apic.h) \
    $(wildcard include/config/x86/f00f/bug.h) \
    $(wildcard include/config/x86/cyclone/timer.h) \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/pci/mmconfig.h) \
  include/asm/acpi.h \
    $(wildcard include/config/acpi/sleep.h) \
  include/acpi/pdc_intel.h \
  include/asm/apicdef.h \
  include/asm/kmap_types.h \
    $(wildcard include/config/debug/highmem.h) \
  include/asm/pgtable-2level-defs.h \
  include/asm/pgtable-2level.h \
  include/asm-generic/pgtable-nopmd.h \
  include/asm-generic/pgtable-nopud.h \
  include/asm-generic/pgtable.h \
  include/linux/page-flags.h \
    $(wildcard include/config/s390.h) \
    $(wildcard include/config/swap.h) \
  include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
    $(wildcard include/config/dma/is/normal.h) \
  include/linux/highmem.h \
  include/asm/cacheflush.h \
    $(wildcard include/config/debug/rodata.h) \
  include/asm/highmem.h \
  include/linux/interrupt.h \
    $(wildcard include/config/generic/irq/probe.h) \
  include/linux/irqreturn.h \
  include/linux/hardirq.h \
    $(wildcard include/config/preempt/bkl.h) \
    $(wildcard include/config/virt/cpu/accounting.h) \
  include/linux/smp_lock.h \
    $(wildcard include/config/lock/kernel.h) \
  include/asm/hardirq.h \
  include/linux/irq.h \
    $(wildcard include/config/irq/per/cpu.h) \
    $(wildcard include/config/irq/release/method.h) \
    $(wildcard include/config/generic/pending/irq.h) \
    $(wildcard include/config/irqbalance.h) \
    $(wildcard include/config/pci/msi.h) \
    $(wildcard include/config/auto/irq/affinity.h) \
  include/asm/irq.h \
  include/asm-i386/mach-default/irq_vectors.h \
  include/asm-i386/mach-default/irq_vectors_limits.h \
  include/asm/hw_irq.h \
  include/linux/profile.h \
  include/asm/sections.h \
  include/asm-generic/sections.h \
  include/linux/irq_cpustat.h \
  include/asm/tlbflush.h \
    $(wildcard include/config/x86/invlpg.h) \
  include/linux/poll.h \
  include/asm/poll.h \
  include/asm/uaccess.h \
    $(wildcard include/config/x86/intel/usercopy.h) \
    $(wildcard include/config/x86/wp/works/ok.h) \
  include/linux/net.h \
  include/linux/sysctl.h \
  include/linux/textsearch.h \
  include/linux/module.h \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/kallsyms.h) \
  include/linux/kmod.h \
    $(wildcard include/config/kmod.h) \
  include/linux/elf.h \
  include/linux/elf-em.h \
  include/asm/elf.h \
    $(wildcard include/config/compat/vdso.h) \
  include/asm/user.h \
  include/linux/utsname.h \
  include/asm/desc.h \
  include/asm/ldt.h \
  include/linux/moduleparam.h \
  include/asm/local.h \
  include/asm/module.h \
    $(wildcard include/config/m486.h) \
    $(wildcard include/config/m586.h) \
    $(wildcard include/config/m586tsc.h) \
    $(wildcard include/config/m586mmx.h) \
    $(wildcard include/config/m686.h) \
    $(wildcard include/config/mpentiumii.h) \
    $(wildcard include/config/mpentiumiii.h) \
    $(wildcard include/config/mpentiumm.h) \
    $(wildcard include/config/mpentium4.h) \
    $(wildcard include/config/mk6.h) \
    $(wildcard include/config/mcrusoe.h) \
    $(wildcard include/config/mefficeon.h) \
    $(wildcard include/config/mwinchipc6.h) \
    $(wildcard include/config/mwinchip2.h) \
    $(wildcard include/config/mwinchip3d.h) \
    $(wildcard include/config/mcyrixiii.h) \
    $(wildcard include/config/mviac3/2.h) \
    $(wildcard include/config/mgeodegx1.h) \
    $(wildcard include/config/mgeode/lx.h) \
    $(wildcard include/config/regparm.h) \
  include/net/checksum.h \
  include/asm/checksum.h \
  include/linux/in6.h \
  include/linux/dmaengine.h \
    $(wildcard include/config/dma/engine.h) \
  include/linux/device.h \
  include/linux/ioport.h \
  include/linux/klist.h \
  include/linux/if_packet.h \
  include/linux/pci.h \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/isa.h) \
    $(wildcard include/config/eisa.h) \
    $(wildcard include/config/pci/domains.h) \
  include/linux/pci_regs.h \
  include/linux/pci_ids.h \
  include/linux/mod_devicetable.h \
  include/linux/dmapool.h \
  include/asm/scatterlist.h \
  include/asm/pci.h \
  include/asm-generic/pci-dma-compat.h \
  include/linux/dma-mapping.h \
  include/asm/dma-mapping.h \
  include/asm-generic/pci.h \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/kcompat.h \
    $(wildcard include/config/e1000/napi.h) \
    $(wildcard include/config/ixgb/napi.h) \
    $(wildcard include/config/e1000/disable/packet/split.h) \
    $(wildcard include/config/igb/disable/packet/split.h) \
    $(wildcard include/config/inet/lro.h) \
    $(wildcard include/config/inet/lro/module.h) \
    $(wildcard include/config/space/len.h) \
    $(wildcard include/config/netdevices/multiqueue.h) \
  include/linux/version.h \
  include/linux/etherdevice.h \
  include/linux/random.h \
  include/linux/delay.h \
  include/asm/delay.h \
  include/linux/in.h \
  include/linux/ip.h \
  include/linux/udp.h \
  include/net/inet_sock.h \
  include/net/flow.h \
  include/net/sock.h \
    $(wildcard include/config/netdebug.h) \
    $(wildcard include/config/net.h) \
  include/linux/security.h \
    $(wildcard include/config/security/network.h) \
    $(wildcard include/config/security/network/xfrm.h) \
  include/linux/binfmts.h \
  include/linux/shm.h \
  include/asm/shmparam.h \
  include/asm/shmbuf.h \
  include/linux/msg.h \
  include/asm/msgbuf.h \
  include/linux/key.h \
  include/linux/filter.h \
  include/net/dst.h \
    $(wildcard include/config/net/cls/route.h) \
    $(wildcard include/config/xfrm.h) \
  include/linux/rtnetlink.h \
  include/linux/netlink.h \
  include/net/neighbour.h \
  include/linux/seq_file.h \
  include/net/request_sock.h \
  include/linux/mii.h \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/hw.h \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_regs.h \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_defines.h \
    $(wildcard include/config/res.h) \
    $(wildcard include/config/fault.h) \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_mac.h \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_phy.h \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_nvm.h \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_manage.h \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_82571.h \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_80003es2lan.h \
  /home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_ich8lan.h \
    $(wildcard include/config/ich8m.h) \

/home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_82571.o: $(deps_/home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_82571.o)

$(deps_/home/My_project/oak3030/e1000e-0.5.18.3/src/e1000_82571.o):
