# 01 · 匿名映射与按需分配

运行：

```bash
cd Areas/Linux/MemoryManagement/CaseStudy/01_mmap_faults
./run.sh
```

程序建立 16 MiB 匿名私有映射，先观测 minor faults，再每隔一页写入一个字节并再次观测。预测：`mmap()` 后 fault 增量通常很小；触页后增量上升。数值不会固定等于页数，因为运行库、页大小、透明大页及内核行为都可能影响计数。

读完输出后回答：`mmap()` 建立了什么？首次写入时又发生了什么？为什么 minor fault 不必然表示从磁盘读取？可对照 [mmap(2)](https://man7.org/linux/man-pages/man2/mmap.2.html)、[getrusage(2)](https://man7.org/linux/man-pages/man2/getrusage.2.html) 与内核 [Concepts overview](https://docs.kernel.org/admin-guide/mm/concepts.html)。
