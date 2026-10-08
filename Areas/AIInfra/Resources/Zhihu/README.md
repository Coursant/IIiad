# 知乎原文资料索引

来源：[AI infra学习汇总(持续更新中)](https://zhuanlan.zhihu.com/p/2075514689602187333)，作者：[陌丶一叶知秋](https://www.zhihu.com/people/mo-zhu-yixie-zhi-qiu)。原页面标注编辑于 2026-08-27 02:00；本次提取于 2026-10-09，经 [Jina Reader 文本入口](https://r.jina.ai/https://zhuanlan.zhihu.com/p/2075514689602187333) 取得内容。记录的是本次可读快照，原文持续更新时可能变化。

按原文顺序建立 **22 个一级分类**，保留 **5D并行下 PP / SP / CP 三个二级分类**。正文共有 **143 个资料条目、141 个不同目标 URL**。点击下面分类即可打开文中资料；此前补充的官方文档仍在 [上级资料区](../README.md)。

## 按原文分类浏览

| 原文分类 | 条目数（含子分类） | 本仓库任务映射 / 用途 |
|---|---|---|
| [系统总览](01_Overview/README.md) | 8 | J01、路线选择 |
| [torch](02_PyTorch/README.md) | 6 | F09–10、D02–06 |
| [CUDA](03_CUDA/README.md) | 11 | K01–08、K13–16 |
| [cuda graph](04_CUDAGraph/README.md) | 3 | K16 |
| [cuTile](05_cuTile/README.md) | 2 | 算子方向选读 |
| [Tilelang](06_TileLang/README.md) | 3 | 算子方向选读 |
| [triton](07_Triton/README.md) | 3 | K12 |
| [推理](08_Inference/README.md) | 10 | I01–13 |
| [训练](09_Training/README.md) | 11 | F10–12、D01–18 |
| [RL](10_RL/README.md) | 3 | RL 方向选读 |
| [微调](11_FineTuning/README.md) | 1 | 微调方向选读 |
| [算子](12_Operators/README.md) | 3 | K06–15 |
| [5D并行](13_5DParallelism/README.md) | 10 | D09–12、D16 |
| [megatron-lm](14_MegatronLM/README.md) | 5 | D09–12、D17–18 |
| [显存](15_GPUMemory/README.md) | 16 | D01、D07–08、D14、P07 |
| [通信](16_Communication/README.md) | 22 | F14、D05–06、D16、D18 |
| [框架](17_Frameworks/README.md) | 8 | 训练 / RL 框架选读 |
| [模型结构](18_ModelArchitecture/README.md) | 7 | F11、F15、D16、I20–21 |
| [FA](19_FlashAttention/README.md) | 6 | K11 |
| [量化](20_Quantization/README.md) | 1 | 保留原分类，见分类说明 |
| [加速](21_Acceleration/README.md) | 2 | P04、S11 |
| [数学](22_Mathematics/README.md) | 2 | F07–08 |

## 使用方式

按当前任务进入对应分类，一次选一篇，阅读后把自己的笔记或实验放回学习模块，在 Session 中记录原始资料 URL 和任务 ID。这里是资料索引，不是新增的一套必须全部读完的任务；收录不代表已读或掌握。

面试主线可先从 torch、模型结构、推理、显存、CUDA、通信中选择当前薄弱项；RL、cuTile、TileLang 等按目标岗位选读。该阅读建议由本仓库补充，并非原文的必读顺序。

## 提取与核验边界

- 只收录正文“系统总览”至“数学”的资源链接；排除作者资料、图片、评论、热榜和站点自动推荐。
- 原文 `link.zhihu.com/?target=...` 外链已解码为目标地址；有意义的参数和论文版本保留。标题中因排版出现的 URL 空格不写入目标链接。
- 原文已有文章标题保持其标题；纯 URL 条目使用仓库名、文章 ID 或 URL 路径标识，不猜测缺失标题。
- 两个重复 URL 保留各自分类：序列并行文章同时位于 5D并行/SP 与 FA；Online-Softmax/FlashAttention 文章同时位于 FA 与量化。
- “量化”分类的条目主题与分类不一致，已在分类页注明；不静默改写原作者归类。
- 本次完成的是来源和链接提取核验，没有逐篇打开 141 个目标页面，也未验证其技术结论。后续引用具体结论时再读原文并用官方资料/实验交叉核对。

详细访问记录与学习模块映射见 [ArticleMapping](../ArticleMapping.md)。
