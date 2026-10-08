# WonderTraderLab

通过阅读 WonderTrader 的 C++ 源码学习 C++17，并亲手逐步复刻其核心功能。每次语法练习都为同一个项目增加一个可验证的功能。

当前为可独立构建的项目脚手架，交易核心功能尚未开始实现。

## 开始学习

可以直接说：“我想练习虚函数”“从 WonderTrader 找一个 lambda 的用法”“继续上次的行情模块”，或提交自己的代码让我审阅。Agent 会按 [学习规则](AGENTS.md) 查找真实源码、解释语法、拆解任务并记录进度。

- [实现路线与验收条件](docs/ROADMAP.md)
- [第一课：从零推导核心类设计](docs/S001_core_class_design.md)
- [参考源码与映射](docs/SOURCES.md)
- [当前进度](learning/PROGRESS.md)
- [学习日志](learning/LOG.md)

## 构建运行

在本目录执行，需要 CMake 3.16+ 与支持 C++17 的 GCC/libstdc++：

```bash
cmake -S . -B build
cmake --build build
./build/wondertrader_lab
```

当前程序仅输出项目准备状态并以 0 退出。后续课程逐步扩展 `src/` 和 CMake 目标。构建产物保存在已被仓库忽略的 `build/` 中。

## 最终目标

离线行情输入 → 行情缓存与事件分发 → 策略和上下文 → 目标仓位与订单 → 风控与模拟成交 → 持仓、资金及回测报告。

这是学习项目的核心范围；与上游的覆盖差异持续记入路线和源码映射。上游入口：[WonderTrader C++ 源码](https://github.com/wondertrader/wondertrader/tree/master/src)。
