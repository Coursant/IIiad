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
11. **C++ 案例头文件**：现有 `CaseStudy` 全部改用 `<bits/stdc++.h>` 与 `using namespace std;`，优先满足学习与算法练习时的便利性。
12. **跨语言共同笔记**：C++ 迭代器的设计与使用要与 Python、Rust 比较，笔记放在 `Areas/Language/` 的共同部分，并把这类笔记的约定写入 `Areas/Language/AGENT.md`。
13. **迭代器的资源与所有权**：在三语言迭代器比较中进一步对照内存资源管理、所有权和提前结束遍历后的清理行为。
14. **返回值生命周期**：详细解释 Python 函数内部创建的值返回后为何不会悬空，并用例子与 Rust、C++17 的所有权、按值返回和返回局部引用进行比较，写成 Language 共同笔记。
15. **变量存储与生命周期**：分析 C++、Rust、Python 中变量/对象的类型、存储方式与生命周期，并整理成 Language 共同笔记。
16. **问题驱动的细粒度比较**：重写过于琐碎的三语言变量生命周期笔记，以一个具体的复杂程序内存管理问题为主线，逐时刻比较 C++、Rust、Python。
17. **降低示例复杂度**：将该笔记改成一个容器的程序例子，保留三语言对照，便于理解。
18. **变量完整生命周期主线**：按变量、初始化、类型/auto、存储/生命周期/作用域、创建 ref/ptr、赋值的顺序详细比较 Rust、C++、Python，解释 copy/move/ref 如何由类型定义与语言默认规则决定，并追踪引用和指针的有效性。

---

## 2. 系统设计总则

- **三层结构**：`Areas/领域 → 语言/主题轨道 → 案例（CaseStudy/<case>）`。
- **自包含**：每个案例不依赖其它案例，可单独编译运行。
- **可验证**：任何案例都能一条命令跑通且退出码为 0。
- **零告警**：编译必须通过严格告警集。
- **纯标准库优先**：能不引第三方依赖就不引；必须引时在案例内注明。
- **C++ 练习约定**：案例统一使用 GCC/libstdc++ 的 `<bits/stdc++.h>` 与 `using namespace std;`。
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
| `Areas/Language/AGENT.md` | Language 下跨语言共同笔记的放置与写作约定 |
| `Areas/Language/Common/Iterators.md` | C++17、Python、Rust 迭代器设计与使用对照 |
| `Areas/Language/Common/ReturnValueLifetime.md` | 三语言函数返回值生命周期、所有权和悬空引用对照 |
| `Areas/Language/Common/VariableStorageLifetime.md` | 沿容器变量的完整生命周期，详解三语言初始化、类型推导、ref/ptr、赋值、复制、移动与清理 |
| `DESIGN.md` | 本文档：设计指令 + 做法 + 变更日志 |

### 3.5 Linux 内存管理学习轨道（2026-09-29 起）

`Areas/Linux/` 是独立 Area，`MemoryManagement/` 是主题轨道。路线见该轨道 `README.md`：基础概念、用户态观察、内核实现、隔离环境中的控制实验依次推进。每个实验放在独立 `CaseStudy/<NN_topic>/`，以本机内核版本为准，不把教学模型等同于内核实现。

### 3.3 约定

- **案例命名**：特性示范用 `NN_topic`；书本案例用 `ppp2_ch<CC>_<kind><NN>_<slug>`。
- **案例元信息**：每个 `main.cpp` 顶部必须有 `// Case:` / `// Topic:` / `// RUN:` / `// CHECK:`，书本案例另加 `// BOOK:`。
- **构建产物**：统一在 `build/<案例名>/`（已 git 忽略）。
- **运行目录**：`build.sh` 运行前 `cd` 到案例目录，便于相对路径读取数据文件。
- **文档语言**：中文叙述 + 英文标识符/命令。
- **C++ 案例头文件**：统一使用 `<bits/stdc++.h>` 与 `using namespace std;`；依赖 GCC/libstdc++，不保证其他标准库实现支持。
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
| Linux 内存管理组织 | 放入语言区 / 独立 Area | **`Areas/Linux/MemoryManagement`** | 系统主题独立于语言轨道，便于按概念和实验推进 |
| C++ 练习头文件 | 按需包含标准头 / `<bits/stdc++.h>` | **`<bits/stdc++.h>`** | 用户选择便捷写法；接受对 GCC/libstdc++ 的依赖 |
| 跨语言笔记位置 | 各语言轨道重复 / Language 共同层 | **`Areas/Language/Common/`** | 同一主题集中比较，单语言可运行案例仍留在各自轨道 |

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

### 2026-09-29 · Codex (GPT-6) · 新增 Linux 内存管理学习轨道
- 指令：在 Areas 中添加 Linux，查找教学参考，支持逐步学习和实现 Linux 内存管理实验。
- 改动：新增 `Areas/Linux/AGENT.md`、`Areas/Linux/MemoryManagement/README.md` 与首个 `01_mmap_faults` 独立案例；更新根 `AGENT.md` 目录树和 `DESIGN.md` 第 3、4 节。
- 验证：核对 OSTEP、内核文档和 man-pages 参考链接；`01_mmap_faults/run.sh` 严格告警编译并运行成功（本机 4096 字节页、16 MiB 映射，触页后 minor faults 增量 4096）；`git diff --check`、`bash -n Areas/Linux/MemoryManagement/CaseStudy/01_mmap_faults/run.sh` 通过。
- 遗留：第 2–6 阶段案例待按学习进度逐步实现。

### 2026-09-29 · Codex (GPT-6) · 统一 C++ 案例便捷头文件
- 指令：将目前 `CaseStudy` 中全部替换为 `<bits/stdc++.h>` 与 `using namespace std;` 写法。
- 改动：10 个现有案例统一头文件及命名空间语句，去掉冗余的 `std::` 前缀；更新新案例脚手架、脚本文档、根与 C++ 轨道规范；保留 `01_hello` 已有的额外代码。
- 验证：`./build.sh --all` 与 `./build.sh --all --cxx=clang++` 均为 10/10 编译成功且零告警；逐个检查案例中便捷头文件及命名空间语句各一处；`git diff --check`、`bash -n Areas/Language/C++/scripts/new_case.sh` 通过。
- 遗留：`<bits/stdc++.h>` 依赖 GCC/libstdc++，其他标准库实现未验证。

### 2026-09-29 · Codex (GPT-6) · 建立跨语言共同笔记并比较迭代器
- 指令：将 C++ 迭代器设计与使用、与 Python/Rust 的比较写为 Language 共同笔记，并在 Language 下的 AGENT.md 记录此类要求。
- 改动：新增 `Areas/Language/AGENT.md` 和 `Areas/Language/Common/Iterators.md`；更新根 `AGENT.md` 目录树、`Areas/Language/C++/AGENT.md` 中过时的命名空间说明，以及 `DESIGN.md` 的设计指令、做法和决策。
- 验证：笔记中的两段完整 C++ 示例以 `g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Werror` 编译运行通过；Python 示例运行通过；Rust 示例以 `rustc --edition=2021 -D warnings` 编译运行通过；三语言同题对照均验证得到 `20`；`git diff --check` 通过。
- 遗留：无。

### 2026-09-29 · Codex (GPT-6) · 补充迭代器资源管理与所有权对照
- 指令：比较 C++、Python、Rust 迭代器在内存资源管理和所有权上的差异。
- 改动：在 `Areas/Language/Common/Iterators.md` 增加容器生命周期、元素取得方式、提前停止遍历、惰性处理与清理责任的对照及三语言示例；更新 `Areas/Language/AGENT.md` 索引与本文件指令记录。
- 验证：新增 C++ 示例以 `g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Werror` 编译运行通过；Python 示例运行通过；Rust 示例以 `rustc --edition=2021 -D warnings` 编译运行通过；官方文档核对；`git diff --check` 通过。
- 遗留：无。

### 2026-09-29 · Codex (GPT-6) · 比较三语言函数返回值生命周期
- 指令：详细举例说明 Python 函数内创建的值返回后为何不悬空，并与 Rust、C++17 比较，写成 Language 共同笔记。
- 改动：新增 `Areas/Language/Common/ReturnValueLifetime.md`；更新 `Areas/Language/AGENT.md` 索引、根 `AGENT.md` 目录树及本文件的指令和文件记录。
- 验证：笔记中 C++17 两段安全示例以 `g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Werror` 编译运行通过；Python 三段安全示例运行通过；Rust 两段安全示例以 `rustc --edition=2021 -D warnings` 编译运行通过；Rust 返回局部借用反例确实报 E0515；官方文档核对；`git diff --check` 和新笔记尾随空白检查通过。
- 遗留：C++ 悬空引用反例仅供阅读，不执行未定义行为。

### 2026-09-29 · Codex (GPT-6) · 比较三语言变量类型、存储与生命周期
- 指令：分析 C++、Rust、Python 对变量存储的类型以及其生命周期。
- 改动：新增 `Areas/Language/Common/VariableStorageLifetime.md`，区分类型、作用域、存储位置与对象生命周期，并比较 C++17 存储期、Rust 所有权与 Python 名字绑定；更新 Language 索引、根目录树和本文件指令/文件记录。
- 验证：笔记的两段 C++ 示例以 `g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Werror` 编译运行通过；两段 Rust 示例以 `rustc --edition=2021 -D warnings` 编译运行通过；两段 Python 示例运行通过；核对官方资料；`git diff --check` 与新笔记尾随空白检查通过。
- 遗留：无。

### 2026-09-29 · Codex (GPT-6) · 以热更新快照重写三语言内存管理笔记
- 指令：原笔记过于琐碎；围绕一个具体的复杂程序内存管理问题，在 C++、Rust、Python 中细粒度比较并重写。
- 改动：重写 `Areas/Language/Common/VariableStorageLifetime.md`，用工作线程持有旧快照、主线程发布新快照的同一场景，沿 T0–T4 比较类型、所有权、迭代器、清理时机与峰值内存；更新 Language 索引、写作约定和根目录树描述。
- 验证：笔记中的完整 C++17 程序以 `g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Werror -pthread` 编译运行通过；Rust 程序以 `rustc --edition=2021 -D warnings` 编译运行通过；Python 程序以 `python3` 运行通过；验证脚本分别报告 `cpp/rust/python hot-swap scenario: ok`。
- 遗留：无。

### 2026-09-29 · Codex (GPT-6) · 用单个容器替换复杂并发例子
- 指令：热更新示例太复杂，改用一个容器的代码解释三语言的内存管理。
- 改动：重写 `Areas/Language/Common/VariableStorageLifetime.md`，统一使用“函数创建容器、返回、查找、追加、求和”的例子；更新 Language 索引与根目录树描述。
- 验证：从笔记提取三段代码，C++17 用 `g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Werror` 编译运行，Rust 用 `rustc --edition=2021 -D warnings` 编译运行，Python 用 `python3` 运行；三者均成功。
- 遗留：无。

### 2026-09-29 · Codex (GPT-6) · 按变量完整生命周期详解三语言 ref/ptr 与赋值
- 指令：按变量、初始化、类型/auto、存储/生命周期/作用域、ref/ptr、赋值的提纲，写非常详细的三语言笔记，解释类型定义与默认语义如何决定 copy/move/ref。
- 改动：重写 `Areas/Language/Common/VariableStorageLifetime.md`，沿容器 `a` 及其引用、指针追踪初始化、修改、复制、移动、重新赋值和清理；加入类型定义对照、三段完整程序、关系图与来源链接；同步 Language 写作约定、索引和根目录树。
- 验证：提取全部 9 段三语言代码，片段补齐上下文和行为断言后通过；C++ 使用 `g++ -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Werror`，Rust 使用 `rustc --edition=2021 -D warnings`，Python 使用 `python3`。4 个 Rust 反例分别按预期报 E0505、E0382、E0204、E0382。仓库 `./build.sh --all` 与 `./build.sh --all --cxx=clang++` 均为 10/10 编译成功；Markdown 空白、代码围栏、本地链接与 `git diff --check` 检查通过。
- 遗留：无。

---

## 6. 对后续 Agent 的强制要求

1. **动手前**：依次阅读根 `AGENT.md`、相关轨道 `AGENT.md`、本 `DESIGN.md`。
2. **遵循指令**：本文件第 1 节是最高依据；与既有做法冲突时，先在此登记再改。
3. **改动后**：按第 5.1 节格式在日志追加条目，**不得省略验证**。
4. **不得**：删除/改写历史日志、未获明确要求就 commit、引入 C++20+ 特性、提交 `build/`。
5. **新增轨道/领域**：同步更新根 `AGENT.md` 的目录树，并在本文件第 3、4 节登记做法与决策。
6. **不确定时**：先问用户，不擅自扩展范围（例如填充 `PL/Python/Rust/Quant` 占位目录）。
