# 用户指定文章与资料映射

## 当前状态（2026-10-09）

已通过公开文本阅读入口取得 [AI infra学习汇总(持续更新中)](https://zhuanlan.zhihu.com/p/2075514689602187333)，作者 [陌丶一叶知秋](https://www.zhihu.com/people/mo-zhu-yixie-zhi-qiu)，页面标注编辑于 2026-08-27 02:00。

用户本次明确：主要将文中的文章作为资料链接。因此在 [Resources/Zhihu](Zhihu/README.md) 按原文分类建立资料目录，保留已有知识模块、清单 ID 和学习计划，用映射连接资料与任务。资料分类与学习顺序分别服务于查找和验收。

## 访问记录

| 日期 | 入口 / 结果 | 结论 |
|---|---|---|
| 2026-10-08 | 网页超时，直接 HTTP 403，分享及公开阅读入口未取得正文 | 当时未核实标题和目录，使用临时知识组织 |
| 2026-10-09 | 再试网页、分享、公开文章 API：仍受阻；移动阅读入口 HTTP 200 但未提供可用正文 | HTTP 200 本身不代表拿到文章 |
| 2026-10-09 | [Jina Reader](https://r.jina.ai/https://zhuanlan.zhihu.com/p/2075514689602187333)：HTTP 200，返回标题、作者、正文分类和链接 | 以此可读快照提取资料，不能保证与未来原文完全相同 |

## 分类映射

原文 22 个一级分类共 143 个条目、141 个不同目标 URL；5D并行下有 PP / SP / CP 三个二级分类。标题顺序与分类归属按原文保留；下列学习模块映射由本仓库补充。

| 原文标题 / 本地资料目录 | 条目数 | 学习模块 |
|---|---|---|
| [系统总览](Zhihu/01_Overview/README.md) | 8 | 总路线 / Interview |
| [torch](Zhihu/02_PyTorch/README.md) | 6 | 01_Foundations、03_DistributedTraining |
| [CUDA](Zhihu/03_CUDA/README.md) | 11 | 02_CUDAAndOperators |
| [cuda graph](Zhihu/04_CUDAGraph/README.md) | 3 | 02_CUDAAndOperators |
| [cuTile](Zhihu/05_cuTile/README.md) | 2 | 02_CUDAAndOperators（选读） |
| [Tilelang](Zhihu/06_TileLang/README.md) | 3 | 02_CUDAAndOperators（选读） |
| [triton](Zhihu/07_Triton/README.md) | 3 | 02_CUDAAndOperators |
| [推理](Zhihu/08_Inference/README.md) | 10 | 04_InferenceOptimization |
| [训练](Zhihu/09_Training/README.md) | 11 | 03_DistributedTraining |
| [RL](Zhihu/10_RL/README.md) | 3 | 训练 / RL 岗位选读 |
| [微调](Zhihu/11_FineTuning/README.md) | 1 | 训练 / 微调岗位选读 |
| [算子](Zhihu/12_Operators/README.md) | 3 | 02_CUDAAndOperators |
| [5D并行](Zhihu/13_5DParallelism/README.md) | 10 | 03_DistributedTraining；保留 PP/SP/CP 子分类 |
| [megatron-lm](Zhihu/14_MegatronLM/README.md) | 5 | 03_DistributedTraining |
| [显存](Zhihu/15_GPUMemory/README.md) | 16 | 01_Foundations、03_DistributedTraining、05_Profiling |
| [通信](Zhihu/16_Communication/README.md) | 22 | 03_DistributedTraining、06_Systems |
| [框架](Zhihu/17_Frameworks/README.md) | 8 | 03_DistributedTraining；RL 框架选读 |
| [模型结构](Zhihu/18_ModelArchitecture/README.md) | 7 | 01_Foundations、04_InferenceOptimization |
| [FA](Zhihu/19_FlashAttention/README.md) | 6 | 02_CUDAAndOperators、04_InferenceOptimization |
| [量化](Zhihu/20_Quantization/README.md) | 1 | 04_InferenceOptimization；原文条目主题不符已注释 |
| [加速](Zhihu/21_Acceleration/README.md) | 2 | 05_Profiling、06_Systems |
| [数学](Zhihu/22_Mathematics/README.md) | 2 | 01_Foundations |

## 提取边界与维护

只提取正文“系统总览”至“数学”的文章、问答、代码仓库、文档和论文链接；没有收录站点评论、作者社交链接、自动推荐、热榜、图片或标题上的实体搜索。知乎跳转链接解码为真实目标，保留论文版本等有效参数。原文纯 URL 条目不猜标题。

重复 URL 按原分类保留：`707204903` 位于 5D并行/SP 与 FA；`668888063` 位于 FA 与量化。“量化”条目主题不符原分类的情况已标注。未逐篇打开或验证这些目标资料，不能把索引当作技术结论背书。

后续更新先获取新快照，按规范化 URL 比较增删；记录提取日期与变化，并保持已经引用的资料与学习日志可追溯。原始整页、评论及页面噪声不存入仓库，只保存链接索引和来源记录。
