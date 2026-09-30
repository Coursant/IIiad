# Linux 内存管理学习路线

目标：从“进程看到什么”走到“内核如何分配、回收和限制内存”。先建立模型，再用小实验核对，最后按正在使用的内核版本读源码。当前环境若为 WSL2，观测结果也可能受到宿主机和配置影响；不要把具体数值当成普遍常量。

## 开始前

```bash
uname -r
getconf PAGE_SIZE
cat /proc/meminfo | head
```

记下内核版本和页大小。建议为每阶段保留“预测 → 命令/代码 → 输出 → 解释 → 尚不确定的点”的短笔记。阶段完成标准是能解释观测现象，而不是运行过命令。

## 逐步路线

| 阶段 | 要回答的问题 | 阅读顺序 | 动手交付与完成标准 | 进度 |
|---|---|---|---|---|
| 1. 地址空间与按需分配 | 虚拟地址、映射、物理页有什么区别？为什么申请后未必立刻占用 RAM？ | OSTEP 第 13–15、18 章；内核 [Concepts overview](https://docs.kernel.org/admin-guide/mm/concepts.html)；[mmap(2)](https://man7.org/linux/man-pages/man2/mmap.2.html) | 运行 [01_mmap_faults](CaseStudy/01_mmap_faults/)；解释映射建立前后、逐页写入后 minor faults 的变化。 | [ ] |
| 2. 页表与缺页 | CPU 如何翻译地址？TLB、页表和缺页异常各做什么？ | OSTEP 第 18–21 章；内核 [Page Tables](https://docs.kernel.org/mm/page_tables.html) 与 [Process Addresses](https://docs.kernel.org/mm/process_addrs.html) | 画出一次匿名页首次读/写的路径；用 `/proc/self/maps`、`/proc/self/smaps` 或 `getrusage(2)` 对照。区分缺页次数和实际页数。 | [ ] |
| 3. 进程内存统计与共享 | VSS/Size、RSS、PSS、匿名页、文件页分别在量什么？ | [proc_pid_smaps(5)](https://man7.org/linux/man-pages/man5/proc_pid_smaps.5.html)；[proc(5)](https://man7.org/linux/man-pages/man5/proc.5.html) | 写小程序分别建立匿名映射、文件映射；记录 `smaps` 中的 Size/Rss/Pss/Private_Dirty，并解释至少一处差异。 | [ ] |
| 4. 物理页分配 | node、zone、buddy allocator、slab/slub 负责什么？ | 内核 [Physical Memory](https://docs.kernel.org/mm/physical_memory.html) 与 [Memory Allocation Guide](https://docs.kernel.org/core-api/memory-allocation.html)；OSTEP 第 17 章 | 用 `/proc/buddyinfo`、`/proc/slabinfo` 做只读观察；对照当前版本 `mm/page_alloc.c`、`mm/slub.c` 画分配路径。 | [ ] |
| 5. 页缓存、回收与压力 | 文件页为何可回收？匿名页何时需要 swap？什么时候发生 OOM？ | 内核 [Concepts overview](https://docs.kernel.org/admin-guide/mm/concepts.html) 中 Page cache/Reclaim/OOM；[Multi-Gen LRU](https://docs.kernel.org/admin-guide/mm/multigen_lru.html)；OSTEP 第 21–23 章 | 比较读取文件前后的 `/proc/meminfo` 和 `/proc/vmstat`；写清缓存与可用内存的关系。不要在主环境制造 OOM。 | [ ] |
| 6. cgroup 与进阶专题 | 如何限制一组进程的内存？THP、NUMA 改变什么？ | 内核 [cgroup v2 Memory](https://docs.kernel.org/admin-guide/cgroup-v2.html#memory)、[Transparent Hugepage](https://docs.kernel.org/admin-guide/mm/transhuge.html)、[NUMA Memory Policy](https://docs.kernel.org/admin-guide/mm/numa_memory_policy.html) | 先只读查看当前 cgroup 的 `memory.current`、`memory.stat`、`memory.events`；随后在隔离 VM/容器中设计限额实验并记录现象。 | [ ] |

## 核心教学参考

1. [*Operating Systems: Three Easy Pieces*（OSTEP）](https://pages.cs.wisc.edu/~remzi/OSTEP/)：免费分章教材。第 13–23 章覆盖地址空间、分页、TLB、页置换及 Linux VM 案例；先读它建立抽象模型。作者还提供 [配套练习](https://pages.cs.wisc.edu/~remzi/OSTEP/Homework/homework.html)。教材中的简化模型不等同于当前 Linux 实现。
2. [Linux Kernel Memory Management 文档索引](https://docs.kernel.org/admin-guide/mm/index.html)：概念与实际机制的主参考；[内核 MM 文档](https://docs.kernel.org/mm/index.html) 进一步解释实现结构。文档的 `latest` 页面可能比本机内核新。
3. [Linux man-pages](https://man7.org/linux/man-pages/)：核对系统调用与 `/proc` 接口的语义。先看 `mmap(2)`、`getrusage(2)`、`proc_pid_smaps(5)`，再按实验扩展。

## 后续实现顺序

每完成一阶段再新增一个独立案例；先预测现象，再写代码，最后用 `/proc` 或系统调用验证。阶段 2 可实现 `fork()` 写时复制观察，阶段 3 做匿名/文件映射对照，阶段 4 做用户态 buddy 模拟器以理解算法，阶段 5 做安全的页缓存观察。用户态模拟器只用于理解算法，不宣称复现 Linux 内核。

读内核源码时，先由当前版本文档定位结构和函数，再看相同版本的 `mm/`、`include/linux/mm*.h`；不要把旧书里的函数名直接当成当前内核接口。若要真正修改内核分配器，先在可恢复的 VM 中构建、启动和验证内核，作为路线后期的单独项目。
