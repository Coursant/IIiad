# WonderTrader 源码参考

- 官方仓库：<https://github.com/wondertrader/wondertrader>
- C++ 入口：<https://github.com/wondertrader/wondertrader/tree/master/src>
- 许可入口：<https://github.com/wondertrader/wondertrader/blob/master/LICENSE>；实际摘录代码前读取对应提交的许可证。
- 2026-09-30：已通过官方仓库页面核实下列目录存在。本轮未摘录具体代码，未固定提交，也未建立本地上游副本；首次源码练习时补齐 SHA 与符号引用。

## 查找入口

这些是检索候选范围，具体语法及调用关系必须在练习时读取源码核实。

| 候选目录（相对上游根） | 用于查找的主题 |
|---|---|
| `src/Includes`、`src/Common` | 类型、公共接口与基础设施 |
| `src/WtCore` | 核心引擎、上下文与执行流程 |
| `src/WtCtaStraFact` | C++ 策略实现与工厂 |
| `src/WtBtCore`、`src/WtBtRunner` | 历史回放、回测与启动流程 |
| `src/WtDtCore`、`src/WtDataStorage` | 数据处理与存储 |
| `src/TraderMocker`、`src/WtExeFact`、`src/WtRiskMonFact` | 模拟通道、执行与风控 |

## 已验证的学习映射

已核实的源码课见后文；用户实现及掌握状态另见学习记录。新增映射按以下格式逐条追加，不把候选目录当作已验证片段：

```text
课次 / 日期：
语法与业务问题：
仓库 / 提交 SHA：
上游文件 / 符号 / 行号范围：
固定提交链接：
本地上游副本位置及修改状态（若有）：
片段性质：原文 / 标记省略 / 教学改写
本地实现路径 / 符号：
相对上游的简化与差异：
验证记录链接：
```

## S001 / 2026-09-30：从零推导 CTA 核心类

- 仓库：wondertrader/wondertrader；固定提交：`08b230dd05facf6d650d949bfe51054115a2ecb1`，通过 GitHub 提交 API 取得。
- 知识点：职责分离、成员初始化、封装、const 引用、虚函数与接口、上下文回调。
- 官方固定提交文件已通过 GitHub 连接器读取，行号按文件换行计数。无本地上游工作副本或修改。
- 课程：[S001_core_class_design.md](S001_core_class_design.md)；其中明确标注原文片段与教学骨架。上游 MIT 许可已读取并保存为 [WONDERTRADER_LICENSE.txt](WONDERTRADER_LICENSE.txt)。

| 上游文件（固定链接） | 行号范围 | 符号与用途 | 本地对应 |
|---|---|---|---|
| [src/Includes/CtaStrategyDefs.h](https://github.com/wondertrader/wondertrader/blob/08b230dd05facf6d650d949bfe51054115a2ecb1/src/Includes/CtaStrategyDefs.h#L26) | 26–92 | CtaStrategy、构造函数、id、on_tick | Strategy / EchoStrategy（待用户编写） |
| [src/Includes/ICtaStraCtx.h](https://github.com/wondertrader/wondertrader/blob/08b230dd05facf6d650d949bfe51054115a2ecb1/src/Includes/ICtaStraCtx.h#L26) | 26–82 | ICtaStraCtx、stra_get_position、stra_set_position | IStrategyContext（后续任务） |
| [src/WtCore/CtaStraBaseCtx.h](https://github.com/wondertrader/wondertrader/blob/08b230dd05facf6d650d949bfe51054115a2ecb1/src/WtCore/CtaStraBaseCtx.h#L58) | 58–62 | CtaStraBaseCtx : public ICtaStraCtx | 上下文继承设计 |
| [src/WtCore/CtaStraContext.h](https://github.com/wondertrader/wondertrader/blob/08b230dd05facf6d650d949bfe51054115a2ecb1/src/WtCore/CtaStraContext.h#L23) | 23–44 | CtaStraContext、set_strategy、_strategy | StrategyContext（后续任务） |
| [src/WtCore/CtaStraContext.cpp](https://github.com/wondertrader/wondertrader/blob/08b230dd05facf6d650d949bfe51054115a2ecb1/src/WtCore/CtaStraContext.cpp#L63) | 63–71 | CtaStraContext::on_tick_updated | 回调与 this 参数教学 |
| [src/WtCore/WtCtaEngine.h](https://github.com/wondertrader/wondertrader/blob/08b230dd05facf6d650d949bfe51054115a2ecb1/src/WtCore/WtCtaEngine.h#L18) | 18–22、62–64、83–88 | CtaContextPtr、WtCtaEngine、addContext、_ctx_map | Engine（后续任务） |
| [src/Includes/WTSStruct.h](https://github.com/wondertrader/wondertrader/blob/08b230dd05facf6d650d949bfe51054115a2ecb1/src/Includes/WTSStruct.h#L146) | 146–183 | WTSTickStruct | 最小 Tick 值模型（待用户编写） |

- 教学差异：Tick 简化为合约和价格；Strategy 的 id 设为 private，以 const 引用返回；on_tick 改为必须实现的纯虚函数，本轮尚不加入上下文参数、策略工厂和引擎。上游 on_tick 是可选空回调。
- 本地代码状态：计划新增 `src/strategy.hpp` 并扩展 `src/main.cpp`，本轮只布置任务，未创建或代写实现；验证状态见 [S001 学习日志](../learning/LOG.md)。
