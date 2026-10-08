# CUDA 与算子：先正确，再解释性能

[返回总览](../README.md) · [统一清单](../CHECKLIST.md)

原文资料：[CUDA](../Resources/Zhihu/03_CUDA/README.md) · [CUDA Graph](../Resources/Zhihu/04_CUDAGraph/README.md) · [算子](../Resources/Zhihu/12_Operators/README.md) · [FA](../Resources/Zhihu/19_FlashAttention/README.md) · [Triton](../Resources/Zhihu/07_Triton/README.md) · [cuTile](../Resources/Zhihu/05_cuTile/README.md) · [TileLang](../Resources/Zhihu/06_TileLang/README.md)。

任务范围：K01–K18。目标：独立写出一个小算子，用正确性检查和计时回答“哪里慢、为什么改、改后怎样”。

## 学习顺序

线程映射 → 访存/同步 → Reduce → GEMM/Softmax → Profiling → Triton/FlashAttention。先在清单中选择 P0，每次只推进一个可验证任务。以下案例是待实现任务书，尚无代码或实测结果；学习到对应任务时再创建目录。

## 独立案例任务书

| 计划目录（本模块 CaseStudy 下） | 条件 | 交付与验证 | 对应任务 |
|---|---|---|---|
| `01_vector_add/` | 单 GPU / CUDA | 含边界保护、错误检查、CPU 参考和 event 计时；区分带宽与启动开销。 | K01–03、K13 |
| `02_reduce/` | 单 GPU / CUDA | 从朴素版本到分块归约，验证尾块与浮点误差；保留每版结果。 | K04–06 |
| `03_softmax/` | 单 GPU / CUDA 或 Triton | 不同长度、dtype、尾块的正确性与耗时；解释在线 softmax 的必要性。 | K09、K11–12 |
| `04_gemm/` | 单 GPU / CUDA | 朴素到 tiled；比较方阵和非方阵，解释何时小 shape 不受益。 | K07–08 |

每个案例附运行命令、固定依赖、正确性检查与限制；报告用 [Experiment 模板](../Templates/Experiment.md)。没有对应硬件时保留实机验收，不将推导或模拟记作实测。

## 面试追问

- 为什么 block 同步不能保证整个 grid 同步？
- 为什么 occupancy 更高不一定更快？
- FlashAttention 节省的是什么 IO，为什么仍是 exact attention？

## 阅读与验收

- [CUDA 官方指南](https://docs.nvidia.com/cuda/cuda-programming-guide/)：执行模型、存储、同步与异步。
- [Triton 教程](https://triton-lang.org/main/getting-started/tutorials/index.html)：从 vector add / fused softmax 选一个重写并加变式。
- [FlashAttention](https://arxiv.org/abs/2205.14135)：读 IO 动机与分块算法，自己推导合并步骤。

每次阅读只为解决一个问题，最终留下自己的推导、例子或实验；源文档版本与日期写入记录。模块完成不靠“看完资料”判断，按统一清单逐项贴证据。
