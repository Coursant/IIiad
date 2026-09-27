# DESIGN.md — IIiad 系统设计指令与 Agent 记录

> 本文档记录**用户对 IIiad 的全部设计指令**、**Agent 的既定做法**，以及**变更日志**。
> **后续任何 Agent 在改动本仓库前必须先读本文档，改动后必须在本文件第 5 节追加记录。**
> 本文件是 append-only 的历史：**不得删除或改写他人已登记的条目**，只能新增。

配套文档：根 `AGENT.md`（架构与协作规范）、`Areas/Language/C++/AGENT.md`（C++ 轨道 / PPP 教材）。

---

## 1. 用户的设计指令（原始意图）

按提出顺序完整记录，作为系统演进的最高依据：

1. **整体结构**：以 `Areas/` 为顶层，按大领域组织。已有 `Areas/Language/{C++, PL, Python, Rust}` 与 `Areas/Quant`。
2. **学习目标**：用户要**重新学习 C++**，标准锁定 **C++17**。
3. **案例收集**：`CaseStudy` 用于收集用户从各种来源获取的 cpp 例子；每个例子必须**可独立运行**。
4. **环境配置**：需要把运行环境配置好（编译器、构建工具）。
5. **架构文档**：用 `AGENT.md` 说明整个仓库的组织架构。
6. **构建方式**：每个例子**独立脚本编译运行**，同时提供**顶层 CMake** 批量构建。（三选一，用户选定此方案）
7. **初始内容**：先搭骨架 + 放少量**样板示例**，其余由用户陆续收集补充。
8. **目录修复**：把误建的 `Areas/Language `（尾随空格）重命名为 `Areas/Language`。
9. **教材主线**：C++ 的学习与练习**参照《C++程序设计原理与实践》**（Stroustrup, PPP）；需**找到该书全部代码及习题解答的仓库**作为参考，并写入 `Areas/Language/C++/AGENT.md`。
10. **本文档**：创建一份文档，描述用户对整个系统的全部设计指令与 Agent 的做法，并**要求后续 Agent 在上面记录**。

---

## 2. 系统设计总则

- **三层结构**：`Areas/领域 → 语言/主题轨道 → 案例（CaseStudy/<case>）`。
- **自包含**：每个案例不依赖其它案例，可单独编译运行。
- **可验证**：任何案例都能一条命令跑通且退出码为 0。
- **零告警**：编译必须通过严格告警集。
- **纯标准库优先**：能不引第三方依赖就不引；必须引时在案例内注明。
- **双通道构建**：单案例独立脚本（日常） + 顶层 CMake（全量）。
- **文档随代码**：每个 Area/轨道有对应 `AGENT.md`；全局决策记入本文件。

---

## 3. Agent 的既定做法（当前实现）

### 3.1 工具链

| 项 | 值 |
|----|----|
| 平台 | WSL2 · Ubuntu 22.04 LTS |
| 默认编译器 | `g++` 11.4（`CXX` 可覆盖） |
| 交叉验证编译器 | `clang++` 14 |
| 标准 | `-std=c++17`，禁用 GNU 扩展 |
| 告警 | `-Wall -Wextra -Wpedantic -Wshadow`，要求零告警 |
| 优化/调试 | `-O2 -g` |
| 构建工具 | cmake 3.22、make 4.3；调试 gdb 12.1 |

### 3.2 关键文件与职责

| 路径 | 职责 |
|------|------|
| `Areas/Language/C++/build.sh` | 单案例编译+运行；支持 `--check/--all/--list/--san/--std=/--cxx=` |
| `Areas/Language/C++/CMakeLists.txt` | 通配 `CaseStudy/*`，每案例一个可执行文件 |
| `Areas/Language/C++/scripts/new_case.sh` | 生成带元信息注释的案例骨架 |
| `Areas/Language/C++/SCRIPTS.md` | 脚本用法说明（build.sh / new_case.sh） |
| `.gitignore` | 忽略 `build/`、目标文件、编辑器产物 |
| 根 `AGENT.md` | 全仓库架构与协作规范 |
| `Areas/Language/C++/AGENT.md` | C++ 轨道：PPP 教材、官方代码、解答仓库、适配规则 |
| `DESIGN.md` | 本文档：设计指令 + 做法 + 变更日志 |

### 3.3 约定

- **案例命名**：特性示范用 `NN_topic`；书本案例用 `ppp2_ch<CC>_<kind><NN>_<slug>`。
- **案例元信息**：每个 `main.cpp` 顶部必须有 `// Case:` / `// Topic:` / `// RUN:` / `// CHECK:`，书本案例另加 `// BOOK:`。
- **构建产物**：统一在 `build/<案例名>/`（已 git 忽略）。
- **运行目录**：`build.sh` 运行前 `cd` 到案例目录，便于相对路径读取数据文件。
- **文档语言**：中文叙述 + 英文标识符/命令。
- **Git 策略**：**只有用户明确要求才 commit**；不提交构建产物。

### 3.4 质量门禁

改动 C++ 后必跑：

```bash
cd Areas/Language/C++
./build.sh --all                  # g++ 全量，零告警
./build.sh --all --cxx=clang++    # clang 交叉验证
```

---

## 4. 决策记录

| 决策 | 备选 | 选择 | 理由 |
|------|------|------|------|
| 构建方式 | 纯脚本 / 纯 CMake / 脚本+CMake | **脚本 + 顶层 CMake** | 兼顾单例独立运行与整体管理 |
| 初始内容 | 只搭骨架 / 骨架+样板 | **骨架 + 样板** | 提供可复制的模板 |
| 目录名 | 保留尾随空格 / 重命名 | **重命名为 `Language`** | 避免脚本与命令行反复出错 |
| C++ 标准 | C++11/14/17/20 | **C++17** | 用户指定，且与 PPP2 兼容度高 |
| 教材 | 无 / PPP | **PPP** | 用户指定 |
| 案例元信息位置 | 独立 README / 源码顶部注释 | **源码顶部注释** | 与代码同处，随文件复制不丢失 |

---

## 5. 变更日志（append-only）

### 5.1 记录协议

**每个 Agent 完成一次有文件改动的任务后，必须在本节末尾追加一条记录**，格式：

```
### YYYY-MM-DD · <agent/模型标识> · <一句话标题>
- 指令：<本次对应的用户指令/背景>
- 改动：<文件/目录清单>
- 验证：<执行过的命令与结果>
- 遗留：<未完成项或待用户确认项；无则写“无”>
```

规则：

- 只能**追加**，不得修改或删除既有条目。
- 日期用实际当天日期；同日多条按时间顺序排列。
- 验证必须写**真实执行过**的命令，不写预期结果。

### 5.2 记录

### 2026-09-26 · opencode (deepseek-v4-flash) · 仓库初始化与 C++17 学习轨道搭建
- 指令：对应第 1 节指令 1–9（搭建目录、C++17 学习、案例可独立运行、AGENT.md、PPP 参考仓库）。
- 改动：
  - 重命名 `Areas/Language ` → `Areas/Language`（去尾随空格）
  - 新增根 `AGENT.md`、`.gitignore`
  - 新增 `Areas/Language/C++/{build.sh, CMakeLists.txt, scripts/new_case.sh, AGENT.md}`
  - 新增 10 个 C++17 样板案例 `CaseStudy/01_hello` … `10_template_auto`
- 验证：
  - `./build.sh --all` → g++ 11.4 全量编译，零告警
  - `./build.sh --all --cxx=clang++` → clang 14 全量编译，零告警
  - 10 个案例逐个 `./build.sh <case>` → 全部退出码 0
  - `cmake -S . -B build/cmake && cmake --build build/cmake -j` → 10 个 target 构建成功
  - `./scripts/new_case.sh 99_tmp_probe` → 生成并跑通后清理
- 遗留：`Areas/Language/{PL,Python,Rust}`、`Areas/Quant` 仍为占位；PPP 章节进度表尚未开始；仓库尚未 commit（等用户指示）。

### 2026-09-26 · opencode (deepseek-v4-flash) · 建立系统设计指令与 Agent 记录文档
- 指令：对应第 1 节指令 10（记录全部设计指令与 Agent 做法，并要求后续 Agent 在此登记）。
- 改动：
  - 新增 `DESIGN.md`（本文档）
  - 根 `AGENT.md`：目录树加入 `DESIGN.md`，顶部加“改动后必须追加记录”的指引
- 验证：文档为纯 Markdown，无需编译；`ls DESIGN.md` 存在，已与 `AGENT.md` 交叉引用。
- 遗留：无。

### 2026-09-26 · opencode (deepseek-v4-flash) · 为现有脚本添加说明文档
- 指令：对目前可用的脚本（`build.sh`、`scripts/new_case.sh`）添加说明。
- 改动：
  - 新增 `Areas/Language/C++/SCRIPTS.md`（概览、语法、选项、解析规则、退出码、示例、速查、维护约定）
  - `build.sh`：修正 `usage()` 行范围，`--help` 不再多打印脚本正文
  - `scripts/new_case.sh`：新增 `-h/--help`
  - `Areas/Language/C++/AGENT.md`、根 `AGENT.md`：加入 `SCRIPTS.md` 引用与目录树条目
- 验证：
  - `./build.sh --help`、`./scripts/new_case.sh --help` 输出正确
  - `./build.sh --san 01_hello`、`./build.sh 01_hello -- foo bar`、`./build.sh CaseStudy/01_hello/main.cpp`、`./build.sh --check --std=c++20 01_hello`、`./build.sh nope`（退出码 2）均符合文档描述
- 遗留：无。

---

## 6. 对后续 Agent 的强制要求

1. **动手前**：依次阅读根 `AGENT.md`、相关轨道 `AGENT.md`、本 `DESIGN.md`。
2. **遵循指令**：本文件第 1 节是最高依据；与既有做法冲突时，先在此登记再改。
3. **改动后**：按第 5.1 节格式在日志追加条目，**不得省略验证**。
4. **不得**：删除/改写历史日志、未获明确要求就 commit、引入 C++20+ 特性、使用 `bits/stdc++.h`、提交 `build/`。
5. **新增轨道/领域**：同步更新根 `AGENT.md` 的目录树，并在本文件第 3、4 节登记做法与决策。
6. **不确定时**：先问用户，不擅自扩展范围（例如填充 `PL/Python/Rust/Quant` 占位目录）。
