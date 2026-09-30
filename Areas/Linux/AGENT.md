# Linux 学习区

本区独立于 `Areas/Language/C++`。当前轨道是 [MemoryManagement](MemoryManagement/README.md)，按“概念 → 用户态观察 → 内核机制 → 受控实验”推进。

- 学习笔记用中文，保留内核符号、系统调用和命令的英文原名。
- 每个实验放在 `MemoryManagement/CaseStudy/<NN_topic>/`，附一条可执行的运行命令，记录预期现象及其限制。
- 内核实现随版本变化；讨论源码时先运行 `uname -r` 并记录版本，优先使用对应版本的源码或文档。
- 前期实验只读 `/proc` 并运行普通用户程序；涉及 cgroup 限额、内核参数或 OOM 的实验先在隔离环境中设计与执行。
- 进度以 README 中的勾选框为准；完成阶段后写下观察结果，再标记完成。
