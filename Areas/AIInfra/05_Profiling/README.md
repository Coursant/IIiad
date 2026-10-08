# 性能分析：从假设到证据

[返回总览](../README.md) · [统一清单](../CHECKLIST.md)

原文资料：[显存](../Resources/Zhihu/15_GPUMemory/README.md) · [通信](../Resources/Zhihu/16_Communication/README.md) · [加速](../Resources/Zhihu/21_Acceleration/README.md)。

任务范围：P01–P12。目标：能区分 CPU、数据传输、GPU、通信和排队瓶颈，并用正确测量支持结论。

## 学习顺序

测量协议 → 时间线 → kernel counters → 单变量实验 → 端到端收益/回归。先在清单中选择 P0，每次只推进一个可验证任务。以下案例是待实现任务书，尚无代码或实测结果；学习到对应任务时再创建目录。

## 独立案例任务书

| 计划目录（本模块 CaseStudy 下） | 条件 | 交付与验证 | 对应任务 |
|---|---|---|---|
| `01_timing_protocol/` | CPU；异步 GPU 计时需 GPU | 演示未预热/未同步测量的偏差；将稳态、冷启动和端到端分开。 | P01–03 |
| `02_timeline/` | CPU profiler 或 GPU Nsight Systems | 标注一次运行的热点、空洞、传输和等待；提出两个可证伪假设。 | P05 |
| `03_roofline/` | 单 GPU / Nsight Compute | 对一个算子计算强度并对照测量，说明实际流量与理想流量差异。 | P04、P06 |
| `04_benchmark_report/` | 实际服务或明确标注的模拟 | 记录输入/输出长度分布、到达模型、失败数、分位数与原始数据。 | P08–12 |

每个案例附运行命令、固定依赖、正确性检查与限制；报告用 [Experiment 模板](../Templates/Experiment.md)。没有对应硬件时保留实机验收，不将推导或模拟记作实测。

## 面试追问

- 为什么只看 GPU utilization 无法判断是否充分利用算力？
- profiler 会怎样扰动结果？何时用未插桩结果报告性能？
- 热点加速 2 倍，端到端收益上限怎么估计？

## 阅读与验收

- [Nsight Systems](https://docs.nvidia.com/nsight-systems/UserGuide/index.html)：先找端到端时间线。
- [Nsight Compute](https://docs.nvidia.com/nsight-compute/ProfilingGuide/index.html)：再看单个 kernel 的限制。

每次阅读只为解决一个问题，最终留下自己的推导、例子或实验；源文档版本与日期写入记录。模块完成不靠“看完资料”判断，按统一清单逐项贴证据。
