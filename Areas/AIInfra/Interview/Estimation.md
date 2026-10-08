# 面试公式与白板估算

先定义符号、单位与假设，再计算，最后说误差来源。以下是教学模型，实际值以固定框架和设备的测量为准。

## KV Cache

对于普通 decoder attention，假设各层 KV 形状相同、每个请求缓存长度相同、没有共享和压缩：

```text
KV bytes = 2 × L × B × T × H_kv × D_head × bytes_per_element
```

2 表示 K 和 V；L 为层数，B 为同时缓存的序列数，T 为每序列实际缓存 token 数，H_kv 为 KV heads。变长请求把 `B×T` 换成各序列缓存长度之和。MHA 中 KV heads 通常等于 query heads；GQA/MQA 应使用实际 KV heads。MLA 等改变缓存表示的结构不能直接套此公式。

练习：L=32、B=1、T=4096、H_kv=8、D=128、dtype=2 bytes。

```text
2 × 32 × 1 × 4096 × 8 × 128 × 2
= 536870912 bytes = 512 MiB = 0.5 GiB
并发 8 且长度相同时：4 GiB
```

尚未包含：权重、激活、allocator 预留、块内未使用容量、临时 workspace、通信缓冲和缓存元数据。prefix sharing、分页块大小、KV 分片/复制会改变实占；不能简单把多卡总 KV 除以卡数。

原理参考：[PagedAttention 原论文](https://arxiv.org/abs/2309.06180)。

## 权重与训练状态

```text
权重字节 ≈ 参数数 P × 每参数字节
训练峰值 = 参数 + 梯度 + 优化器状态 + 激活 + 临时/通信空间
```

例如一种混合精度 Adam 布局使用 FP16 参数 2P、FP16 梯度 2P、FP32 master weights 4P、两个 FP32 moments 8P，共约 16P bytes，**不含激活与临时空间**。这不是所有实现的固定常数；BF16/FP32 参数保留方式、梯度 dtype 和优化器实现会改变账本。

以“可分片的优化器相关状态”为 O、梯度为 G、参数为 W、数据并行度 N，忽略瞬时聚合、padding 和额外缓冲：

| 策略 | 每 rank 常驻近似值 |
|---|---|
| 复制 | W + G + O |
| ZeRO-1 | W + G + O/N |
| ZeRO-2 | W + (G + O)/N |
| ZeRO-3 | (W + G + O)/N |

FP32 master weights 若存在，应按具体实现归入对应分片状态。实际峰值还要计入参数 all-gather 等瞬时空间；激活不会自动按上表分片。参考：[ZeRO 原论文](https://arxiv.org/abs/1910.02054)。

## 计算、带宽与通信

```text
GEMM: [M,K] × [K,N] → [M,N]
FLOPs ≈ 2MNK（乘、加各算一次）
arithmetic intensity = FLOPs / 相关存储层实际搬运字节
理想下界时间 ≥ max(FLOPs/可用算力, bytes/可用带宽)
```

理想下界没有计入启动、同步、依赖、低利用率与额外复制，不是预计实测时间。参考：[Nsight Compute Profiling Guide](https://docs.nvidia.com/nsight-compute/ProfilingGuide/index.html)。

Ring AllReduce 的简化模型：N 个 rank，每个输入大小 S bytes，每步启动延迟 α，有效链路带宽 β bytes/s：

```text
T ≈ 2(N−1)α + 2(N−1)/N × S/β
```

假设等速环、均匀切块、没有额外拥塞；不等于所有 NCCL 算法的实际性能。小消息、分层拓扑、归约计算和通信重叠均可能改变主导项。集合语义参考：[NCCL collectives](https://docs.nvidia.com/deeplearning/nccl/user-guide/docs/usage/collectives.html)。

## 服务指标与容量

- TTFT：从定义好的客户端发起时刻到第一个输出 token；说明是否含网络、tokenize 和排队。
- ITL：相邻输出 token 到达的时间间隔分布。若 transport 一次 flush 多个 token，注明观测粒度限制。
- TPOT：单请求 `(最后 token 时间 − 首 token 时间)/(输出 token 数 − 1)`；输出不足 2 个 token 时应记未定义，不填 0。
- 输出吞吐：测量窗口内输出 token 总数 / 窗口时长；不能混用总输入+输出 token。
- Goodput：满足事先约定质量与延迟 SLO 的有效请求/秒，或有效输出 token/秒；先写清计数单位。

稳定系统中 Little 定律 `平均在系统请求数 = 平均到达率 × 平均停留时间`，三者边界必须一致。不能把 p99 延迟代入当成平均容量，也不能用它直接推导非稳态峰值容量。

若设备每小时成本 C、达到质量和 SLO 的输出吞吐为 Q tokens/s：

```text
每百万输出 token 的设备成本 ≈ C × 1000000 / (3600 × Q)
```

注明是否包含空闲时段、CPU、网络、存储、重试及平台开销。用 [vLLM 文档](https://docs.vllm.ai/en/stable/) 中实际所用版本的 benchmark 指标定义核对工具输出，不能只对照名称。
