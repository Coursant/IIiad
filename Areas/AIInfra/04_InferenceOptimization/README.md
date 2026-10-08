# 推理优化：以服务指标验证机制

[返回总览](../README.md) · [统一清单](../CHECKLIST.md)

原文资料：[推理](../Resources/Zhihu/08_Inference/README.md) · [模型结构](../Resources/Zhihu/18_ModelArchitecture/README.md) · [显存](../Resources/Zhihu/15_GPUMemory/README.md) · [FA](../Resources/Zhihu/19_FlashAttention/README.md) · [量化分类及其条目说明](../Resources/Zhihu/20_Quantization/README.md)。

任务范围：I01–I22。目标：在给定质量和 SLO 下建立服务基线，解释 KV、调度与系统瓶颈，完成两个有证据的优化实验。

## 学习顺序

请求路径/指标 → KV/分页 → batching → 服务基线 → 源码 → 按岗位选进阶。先在清单中选择 P0，每次只推进一个可验证任务。以下案例是待实现任务书，尚无代码或实测结果；学习到对应任务时再创建目录。

## 独立案例任务书

| 计划目录（本模块 CaseStudy 下） | 条件 | 交付与验证 | 对应任务 |
|---|---|---|---|
| `01_kv_budget/` | CPU / 手算或小脚本 | 按模型配置预测 KV，覆盖 GQA、变长请求和并发；区分理论值与 allocator 实占。 | I03–04 |
| `02_batch_scheduler/` | CPU / 离散事件模拟 | 固定请求到达/长度与成本模型，对比 static/continuous batching，检查请求完成和公平性。 | I06、I13 |
| `03_serving_baseline/` | 兼容设备与固定版本引擎 | 跑通小模型服务，验证响应，再测工作负载矩阵；保存精确命令。 | I09–12 |
| `04_optimization_ab/` | 同一设备/模型/负载 | 在 batching budget、prefix cache、chunked prefill 等支持项中选两个做独立对照。 | I07–08、I22 |

每个案例附运行命令、固定依赖、正确性检查与限制；报告用 [Experiment 模板](../Templates/Experiment.md)。没有对应硬件时保留实机验收，不将推导或模拟记作实测。

## 面试追问

- 长 prompt 到来后已有请求的 ITL 为什么可能恶化？
- prefix cache 的高命中率怎样被不公平的 benchmark 制造出来？
- 吞吐变高但 p99 TTFT 变差时，如何决定是否上线？

## 阅读与验收

- [PagedAttention](https://arxiv.org/abs/2309.06180)：理解 KV 内存管理动机，画块表例子。
- [vLLM](https://docs.vllm.ai/en/stable/) 或 [SGLang](https://docs.sglang.io/)：先选一个框架，按固定版本建立实验。
- [Speculative Decoding](https://arxiv.org/abs/2211.17192)：进阶阅读，区分接受校正机制与实际开销。

每次阅读只为解决一个问题，最终留下自己的推导、例子或实验；源文档版本与日期写入记录。模块完成不靠“看完资料”判断，按统一清单逐项贴证据。
