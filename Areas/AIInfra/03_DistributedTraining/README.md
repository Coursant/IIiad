# 分布式训练：显存、计算与通信的账本

[返回总览](../README.md) · [统一清单](../CHECKLIST.md)

原文资料：[训练](../Resources/Zhihu/09_Training/README.md) · [5D并行](../Resources/Zhihu/13_5DParallelism/README.md) · [Megatron-LM](../Resources/Zhihu/14_MegatronLM/README.md) · [通信](../Resources/Zhihu/16_Communication/README.md) · [框架](../Resources/Zhihu/17_Frameworks/README.md) · [RL](../Resources/Zhihu/10_RL/README.md) · [微调](../Resources/Zhihu/11_FineTuning/README.md)。

任务范围：D01–D18。目标：面对模型放不下或训练扩展差，能选择并行方案并解释代价。

## 学习顺序

单卡账本 → DDP/通信 → ZeRO/FSDP → TP/PP → 拓扑/恢复/扩展。先在清单中选择 P0，每次只推进一个可验证任务。以下案例是待实现任务书，尚无代码或实测结果；学习到对应任务时再创建目录。

## 独立案例任务书

| 计划目录（本模块 CaseStudy 下） | 条件 | 交付与验证 | 对应任务 |
|---|---|---|---|
| `01_ddp_baseline/` | CPU 两进程/Gloo；GPU 扩展用 NCCL | 固定总 batch 对比单进程和多进程梯度/参数，说明均值归约和 loss 口径。 | D02–04 |
| `02_memory_ledger/` | CPU 手算；显存实测需 GPU | 对照复制/ZeRO 各阶段状态，补瞬时空间和激活；预测与实测分别记录。 | D01、D07–08 |
| `03_checkpoint_resume/` | CPU 或 GPU | 记录模型/优化器/RNG/数据位置，比较连续运行与中断恢复。 | D15 |
| `04_scaling/` | 至少两张 GPU | 固定全局工作量或每卡工作量，报告通信、计算、等待、吞吐和效率。 | D05–06、D18 |

每个案例附运行命令、固定依赖、正确性检查与限制；报告用 [Experiment 模板](../Templates/Experiment.md)。没有对应硬件时保留实机验收，不将推导或模拟记作实测。

## 面试追问

- 相同 global batch 为什么仍可能得到不同训练结果？
- ZeRO-3 省了多少常驻状态，为什么峰值不是简单除 N？
- TP 放跨机而 DP 放机内会有什么问题，依据是什么？

## 阅读与验收

- [PyTorch Distributed](https://docs.pytorch.org/docs/stable/distributed.html)：按安装版本阅读后端和进程组。
- [NCCL collective 语义](https://docs.nvidia.com/deeplearning/nccl/user-guide/docs/usage/collectives.html)：先手绘小数组。
- [ZeRO](https://arxiv.org/abs/1910.02054) 与 [Megatron-LM](https://arxiv.org/abs/1909.08053)：分别回答状态如何分片、矩阵如何切分。

每次阅读只为解决一个问题，最终留下自己的推导、例子或实验；源文档版本与日期写入记录。模块完成不靠“看完资料”判断，按统一清单逐项贴证据。
