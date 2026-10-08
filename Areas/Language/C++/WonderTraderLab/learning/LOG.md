# 学习日志

历史记录仅追加，纠错可另加更正说明。使用 [课次模板](SESSION_TEMPLATE.md)，区分工程准备与用户学习。

## 2026-09-30 · S000 · 项目准备

- 用户目标：按指定 C++ 语法从 WonderTrader 找真实片段，指导亲手实现，持续跟踪，逐步复刻核心功能。
- 本轮产出：独立 C++17 项目入口、构建文件、教学规则、实现路线、源码索引和学习记录模板。
- 源码出处：仅核实官方仓库及 C++ 目录入口，详见 [SOURCES.md](../docs/SOURCES.md)；未摘录代码。
- 实现者：Agent（脚手架与文档）；用户尚未开展实现练习。
- 用户尝试、语法讲解与掌握证据：无。
- 验证：在仓库根目录执行 `cmake -S Areas/Language/C++/WonderTraderLab -B Areas/Language/C++/WonderTraderLab/build`、`cmake --build Areas/Language/C++/WonderTraderLab/build`、`Areas/Language/C++/WonderTraderLab/build/wondertrader_lab`，GCC 11.4 编译零告警，程序输出准备状态并以 0 退出。只验证工程入口，未验证任何交易功能。
- 待复习项：无。
- 下一步：由用户指定首个语法，开始 S001；必要时先补齐参考提交和源码读取。

## 2026-09-30 · S001 · 从零推导 CTA 核心类设计

- 用户目标：从 WT 最核心的类设计开始，按从零开发的思路学习。
- 模块：M3 策略接口与上下文设计，使用最小 Tick 支撑后续实践。
- 上游出处：提交 `08b230dd05facf6d650d949bfe51054115a2ecb1`；文件、符号、行号和固定链接详见 [SOURCES.md](../docs/SOURCES.md) 的 S001 映射。
- 讲解：从最小行情处理需求推导 Tick、Strategy、Context、Engine；读取构造初始化、上游可选虚回调、上下文服务接口和具体回调转发；解释 this 的接口转换、借用与封装。
- 本地任务：用户创建 `src/strategy.hpp`，补构造与 getter；在 `src/main.cpp` 写 EchoStrategy，通过 Strategy& 传入两条行情。
- Agent 范围：编写 [课件](../docs/S001_core_class_design.md)、待实现骨架和验收条件；未代写正式 C++ 实现。
- 用户尝试与掌握证据：尚无，相关语法标为“已讲解”，M3 设计阶段进行中，核心完成数仍为 0/7。
- 简化差异：上游空 on_tick 改为教学纯虚接口；本轮省去 ctx 参数、工厂、完整 Tick 字段；后续逐步接入。
- 验证：GitHub 连接器已读取固定版本源码及许可证。网页工具读取固定文件缓存失败，采用连接器实际返回内容。没有用户实现可编译，本轮未运行 C++ 测试。
- 待复习：构造初始化列表、getter 两个 const、纯虚与空回调的差异、借用引用的生命周期。
- 停点：等待用户实现第一个策略类；验收需出现 `demo TEST 99` 与 `demo TEST 101`，并能说明基类引用为何调用派生实现。
