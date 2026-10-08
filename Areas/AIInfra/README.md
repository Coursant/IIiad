# AI Infra 面试学习区

目标：形成能够在面试中解释、推导、实现和验证的 AI Infra 能力，并把学习、实验、错题和面试复盘长期保存在本仓库。

**当前状态：学习系统已建立，能力尚未测评，所有任务未验收。** 默认计划为 12 周 × 每周 10 小时，优先准备推理服务岗位；这是假设，待根据目标 JD、基础、面试日期和硬件调整。12 周是第一轮准备周期，不代表掌握整个领域或保证通过面试。

**原文资料已收录**：2026-10-09 成功读取用户指定的 [AI infra学习汇总(持续更新中)](https://zhuanlan.zhihu.com/p/2075514689602187333)。[知乎资料索引](Resources/Zhihu/README.md) 按原文 22 个一级分类及 PP/SP/CP 子分类保存 143 个资料条目（141 个不同 URL）。按用户补充要求，重点将文中的文章作为资料链接；下方知识模块继续用于学习和验收，原文分类在资料区完整保留。详见 [来源映射](Resources/ArticleMapping.md)。

## 从这里开始

1. 填写 [个人目标与约束](Learning/Profile.md)，用 [起点测评](Interview/Diagnostic.md) 确定薄弱环节。
2. 按 [第一周任务](Learning/FirstWeek.md) 开始；今天只做其中第一天，不必先读完所有资料。
3. 用 [完整清单](CHECKLIST.md) 选择任务，用 [12 周路线](ROADMAP.md) 控制范围。
4. 每次学习按 [记录规则](Learning/README.md) 留下证据；下次直接说“根据 AIInfra 进度继续今天的学习”。

## 知识目录

| 模块 | 面试中要证明什么 | 入口 |
|---|---|---|
| 01 基础 | 能解释张量、模型、内存、并发和通信 | [Foundations](01_Foundations/README.md) |
| 02 CUDA 与算子 | 能正确实现小算子并用测量指导优化 | [CUDAAndOperators](02_CUDAAndOperators/README.md) |
| 03 分布式训练 | 能推导显存和通信代价，选择并行方案 | [DistributedTraining](03_DistributedTraining/README.md) |
| 04 推理优化 | 能分析 KV Cache、调度及吞吐与延迟取舍 | [InferenceOptimization](04_InferenceOptimization/README.md) |
| 05 性能分析（补充） | 能建立可复现基线并定位瓶颈 | [Profiling](05_Profiling/README.md) |
| 06 系统工程（补充） | 能设计可靠服务、容量和故障处理 | [Systems](06_Systems/README.md) |

## 面试与积累

| 入口 | 用法 |
|---|---|
| [学习进度](Learning/Progress.md) | 当前任务、阶段验收和下一步 |
| [题库](Interview/QuestionBank.md) | 按题号闭卷回答、追问、复测 |
| [模拟面试](Interview/MockInterview.md) | 60 分钟面试流程及评分 |
| [公式与估算](Interview/Estimation.md) | 显存、通信、吞吐和容量手算 |
| [项目任务书](Projects/README.md) | 小实验串成可展示的项目证据 |
| [学习日志](Learning/Sessions/README.md) | 每课原始回答、代码、反馈和下一步 |
| [错题本](Learning/Mistakes.md) / [复习队列](Learning/Reviews.md) | 追踪同类错误与到期复测 |
| [投递与岗位](Interview/Applications.md) | JD → 清单 → 项目证据 |
| [简历与项目表达](Interview/Portfolio.md) | 只写有证据的贡献和结果 |
| [知乎原文资料](Resources/Zhihu/README.md) / [补充参考](Resources/README.md) | 原文分类文章链接、官方文档与原始论文 |
| [协作规范](AGENTS.md) | 后续 AI 教学、验证与记录规则 |

## 每次学习的最小闭环

先闭卷回答一个问题，再读与问题相关的一小段资料；预测实验结果，自己实现或推导，记录实际结果与偏差，最后回答一个变式。每次结束保存日志，更新清单证据和复习日期。Agent 生成的讲解或代码不能直接算作你的掌握。

本 Area 自包含；CPU、单 GPU、多 GPU 是不同验证条件。实验放在对应模块的 `CaseStudy/<NN_topic>/`，目录随实际学习创建；组合项目放在 `Projects/`。大型权重、数据集和二进制 trace 不直接入 Git，保留版本、获取方式、校验信息与必要结果摘要。
