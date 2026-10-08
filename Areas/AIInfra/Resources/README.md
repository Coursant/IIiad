# 参考资料与阅读任务

**优先入口：[知乎原文资料索引](Zhihu/README.md)**。已从用户指定的《AI infra学习汇总(持续更新中)》提取 143 个资料条目（141 个不同 URL），按原文 22 个一级分类及 PP/SP/CP 子分类保存。提取日期：2026-10-09；文章内链接的来源归属已核对，目标文章尚未逐篇阅读或验证。访问过程与映射见 [ArticleMapping](ArticleMapping.md)。

下表保留此前补充的官方文档和原始论文，不冒称全部出自知乎原文。官方入口核验日期：2026-10-08；访问核验只确认页面可读取和主题对应，不代表所有示例已在本机运行。

## 先用的资料

| 资料 | 用于哪些任务 | 阅读后必须回答 |
|---|---|---|
| [PyTorch Learn the Basics](https://docs.pytorch.org/tutorials/beginner/basics/intro.html) | F09–12 | tensor、autograd、训练循环如何连接？ |
| [CUDA Programming Guide](https://docs.nvidia.com/cuda/cuda-programming-guide/) | F13、K01–05、K13 | 线程如何映射，内存和同步由谁控制？ |
| [Triton Tutorials](https://triton-lang.org/main/getting-started/tutorials/index.html) | K12 | mask、block 和数据布局如何决定实现？ |
| [NCCL Collective Operations](https://docs.nvidia.com/deeplearning/nccl/user-guide/docs/usage/collectives.html) | F14、D05 | 四种常用 collective 的输入输出是什么？ |
| [PyTorch Distributed](https://docs.pytorch.org/docs/stable/distributed.html) | D02–04 | process group、rank、backend 有何关系？ |
| [PyTorch DDP design note](https://docs.pytorch.org/docs/stable/notes/ddp.html) | D02、D06 | 梯度如何进入通信，哪些步骤可能重叠？ |
| [Nsight Systems User Guide](https://docs.nvidia.com/nsight-systems/UserGuide/index.html) | P05 | CPU/GPU/传输/同步时间线如何关联？ |
| [Nsight Compute Profiling Guide](https://docs.nvidia.com/nsight-compute/ProfilingGuide/index.html) | P04、P06 | 如何用实际指标检验瓶颈假设？ |
| [vLLM 文档](https://docs.vllm.ai/en/stable/) | I05–13、P08 | 当前版本如何配置、运行和测量推理服务？ |
| [SGLang 文档](https://docs.sglang.io/) | I08、I10–11 | 作为另一个引擎选项，缓存和调度设计如何验证？ |
| [Kubernetes GPU 调度](https://kubernetes.io/docs/tasks/manage-gpus/scheduling-gpus/) | S07 | 设备插件和资源申请解决什么、没有解决什么？ |
| [PyTorch compiler](https://docs.pytorch.org/docs/stable/torch.compiler.html) | K17 | 编译链路和 graph break 如何影响运行？ |

PyTorch stable 链接访问时可能跳转版本页；实验时应保存实际安装版本对应的最终文档链接，不把此处入口当作锁定版本。vLLM 使用可读取的 stable 入口；SGLang 官方入口当前跳转到 docs.sglang.io。

## 五篇专项论文

| 原始论文 | 学习目标 | 留下的产物 |
|---|---|---|
| [Megatron-LM (2019)](https://arxiv.org/abs/1909.08053) | 理解模型并行切分与通信位置 | 自己画两层 MLP 的 TP 图 |
| [ZeRO (2019)](https://arxiv.org/abs/1910.02054) | 理解训练状态分片 | 按一个新参数量重算每 rank 显存 |
| [FlashAttention (2022)](https://arxiv.org/abs/2205.14135) | 理解 IO-aware attention | 手推在线 softmax 和数据搬运路径 |
| [PagedAttention / vLLM (2023)](https://arxiv.org/abs/2309.06180) | 理解 KV 分页与共享动机 | 两个变长请求的块表示例 |
| [Speculative Decoding (2022)](https://arxiv.org/abs/2211.17192) | 理解草稿、验证与分布保持条件 | 接受率/草稿成本变化的盈亏分析 |

不是先读完五篇再动手。先解决一个小问题，再读相关算法/实验部分；论文的测试硬件、版本和性能数字不能直接移植到自己的项目。

## 来源记录格式

每次实际使用资料，记标题、URL、作者/机构、年份、访问日期、适用版本、用到的章节与自己的结论。读源码额外固定 commit、文件和符号；摘录少量必要内容，主要保留自己的理解与实验，不把整篇外部文章搬入仓库。

## 版本策略

不在未知硬件上预设 CUDA、PyTorch 或推理引擎版本。先记录设备与驱动，再按官方兼容要求选一组可运行版本，在案例 README 固定下来。版本升级作为单独实验，不与性能优化同时更改。
