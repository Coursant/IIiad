# 基础：把模型、张量和系统串起来

[返回总览](../README.md) · [统一清单](../CHECKLIST.md)

原文资料：[torch](../Resources/Zhihu/02_PyTorch/README.md) · [模型结构](../Resources/Zhihu/18_ModelArchitecture/README.md) · [数学](../Resources/Zhihu/22_Mathematics/README.md) · [显存](../Resources/Zhihu/15_GPUMemory/README.md)。

任务范围：F01–F16。目标：能从一段程序的对象/张量生命周期解释内存和计算，不依赖背诵名词。

## 学习顺序

语言与系统 → 矩阵/数值 → 张量/autograd → Transformer → GPU/通信。先在清单中选择 P0，每次只推进一个可验证任务。以下案例是待实现任务书，尚无代码或实测结果；学习到对应任务时再创建目录。

## 独立案例任务书

| 计划目录（本模块 CaseStudy 下） | 条件 | 交付与验证 | 对应任务 |
|---|---|---|---|
| `01_stable_softmax/` | CPU / Python 标准库或 C++17 | 实现稳定 softmax，验证平移不变性和极端输入；说明不支持输入的约定。 | F07–08 |
| `02_tensor_layout/` | CPU / 固定版本 PyTorch | 比较 transpose/view/reshape/contiguous 的 shape、stride 和存储共享；用修改观察验证预测。 | F09 |
| `03_tiny_training/` | CPU / PyTorch | 生成小型合成数据，训练、评估、保存恢复；验证 loss、参数变化和复现边界。 | F10–12 |
| `04_attention_reference/` | CPU / PyTorch | 实现小型 causal attention 参考，验证 mask、shape 和逐 token KV 缓存结果。 | F11、I03 |

每个案例附运行命令、固定依赖、正确性检查与限制；报告用 [Experiment 模板](../Templates/Experiment.md)。没有对应硬件时保留实机验收，不将推导或模拟记作实测。

## 面试追问

- 为什么 reshape 有时会复制？
- 为什么训练显存不能只按模型文件大小估计？
- 并发请求持有 KV 时，谁负责释放？取消请求如何处理？

## 阅读与验收

- [PyTorch 基础教程](https://docs.pytorch.org/tutorials/beginner/basics/intro.html)：先做张量、autograd 和训练流程对应章节。
- [CUDA Programming Guide](https://docs.nvidia.com/cuda/cuda-programming-guide/)：只先读 programming model，建立硬件抽象。

每次阅读只为解决一个问题，最终留下自己的推导、例子或实验；源文档版本与日期写入记录。模块完成不靠“看完资料”判断，按统一清单逐项贴证据。
