# AGENT.md — IIiad 知识库架构与协作规范

> 本文件既是仓库的架构说明，也是 AI Agent / 协作者的作业手册。
> 修改任何内容前先读完本文件。
>
> **用户设计指令与变更日志见 `DESIGN.md`；任何改动后必须在其中追加记录。**

---

## 1. 项目定位

IIiad 是个人学习与研究知识库，按 **领域 → 语言/主题 → 案例** 三层组织。
当前主线：**重新学习 C++，标准锁定 C++17**，通过可独立运行的小案例（CaseStudy）积累。

设计原则：

- **自包含**：每个案例不依赖其它案例，能单独编译运行。
- **可验证**：任何案例都能用一条命令跑通，退出码为 0。
- **零告警**：编译必须通过 `-Wall -Wextra -Wpedantic -Wshadow`。
- **练习便捷优先**：C++ 案例统一使用 GCC 的 `<bits/stdc++.h>`；仍尽量不引第三方依赖。

---

## 2. 目录架构

```
IIiad/
├── AGENT.md                       # 本文件
├── DESIGN.md                      # 用户设计指令 + Agent 做法 + 变更日志
├── .gitignore                     # 忽略 build/ 与编辑器产物
└── Areas/                         # 顶层：按大领域划分
    ├── Language/                  # 语言学习区
    │   ├── AGENT.md               # 跨语言共同笔记约定
    │   ├── Common/                # 跨语言概念与比较笔记
    │   │   ├── Iterators.md       # C++ / Python / Rust 迭代器
    │   │   ├── ReturnValueLifetime.md # 函数返回值生命周期与所有权
    │   │   └── VariableStorageLifetime.md # 变量完整生命周期、ref/ptr 与赋值语义
    │   ├── C++/                   # C++ 学习轨道（当前主线）
    │   │   ├── AGENT.md           # 本轨道专属说明（PPP 教材与参考仓库）
    │   │   ├── SCRIPTS.md         # build.sh / new_case.sh 用法说明
    │   │   ├── build.sh           # 单案例：编译 + 运行（核心工具）
    │   │   ├── CMakeLists.txt     # 批量构建全部案例
    │   │   ├── WonderTraderLab/   # 独立 C++17 项目：源码教学、学习跟踪与核心功能复刻
    │   │   │   ├── AGENTS.md      # 项目教学与协作规则（AGENT.md 为兼容入口）
    │   │   │   └── README.md      # 独立构建入口、路线与进度索引
    │   │   ├── scripts/
    │   │   │   └── new_case.sh    # 脚手架：新建案例
    │   │   ├── CaseStudy/         # 每个子目录 = 一个独立案例
    │   │   │   ├── 01_hello/
    │   │   │   │   └── main.cpp
    │   │   │   ├── 02_structured_bindings/
    │   │   │   └── ...
    │   │   └── build/             # 构建产物（git 忽略）
    │   ├── PL/                    # 编程语言理论（占位）
    │   ├── Python/                # 占位
    │   └── Rust/                  # 占位
    ├── Linux/                     # Linux 系统学习区
    │   ├── AGENT.md               # Linux 学习轨道约定
    │   └── MemoryManagement/      # 内存管理：路线、资料、实验
    │       ├── README.md
    │       └── CaseStudy/
    ├── AIInfra/                   # AI Infra 面试准备与长期学习记录
    │   ├── AGENTS.md              # 教学、验收、实验与学习记录规则
    │   ├── AGENT.md               # 兼容入口
    │   ├── README.md              # 导航与开始方式
    │   ├── CHECKLIST.md           # 带优先级和验收条件的完整清单
    │   ├── ROADMAP.md             # 12 周目标与冲刺分支
    │   ├── 01_Foundations/        # 基础学习与验收
    │   ├── 02_CUDAAndOperators/   # CUDA 与算子
    │   ├── 03_DistributedTraining/ # 分布式训练
    │   ├── 04_InferenceOptimization/ # 推理优化
    │   ├── 05_Profiling/          # 性能分析补充
    │   ├── 06_Systems/            # 系统工程补充
    │   ├── Interview/             # 测评、题库、模拟、岗位和简历证据
    │   ├── Projects/              # 实践项目任务书与后续实现
    │   ├── Learning/              # 目标、进度、日志、错题和复习
    │   ├── Resources/             # 官方参考与来源映射
    │   │   └── Zhihu/             # 原文 22 类资料链接，含 PP/SP/CP 子分类
    │   └── Templates/             # 笔记、实验、课次和复盘模板
    └── Quant/                     # 量化研究（占位）
```

**层级约定**

- `Areas/<领域>` 之间彼此独立，不互相引用。
- 语言轨道下，`CaseStudy/<NN_topic>/` 是最小可运行单元。
- 一个案例 = 一个目录，目录内自带源文件（通常一个 `main.cpp`，也可多个 `.cpp` + 本地 `.hpp`）。

---

## 3. C++ 轨道规范

| 项目 | 规定 |
|------|------|
| 标准 | **C++17**（`-std=c++17`），不使用 GNU 语言扩展；便捷头文件约定见下 |
| 编译器 | 默认 `g++` 11.4；`clang++` 14 用于交叉验证 |
| 告警 | `-Wall -Wextra -Wpedantic -Wshadow`，要求零告警 |
| 优化/调试 | `-O2 -g` |
| 头文件 | 练习案例统一 `#include <bits/stdc++.h>` 与 `using namespace std;`；依赖 GCC/libstdc++，并非 ISO C++ 标准写法 |
| 语言特性 | 不引入 C++20/23 特性（除非案例显式标注并单独说明） |

C++17 已覆盖的常用特性见 `CaseStudy/` 现有案例（结构化绑定、`if/switch` 初始化、`optional`、`variant`、`string_view`、`if constexpr`、折叠表达式、`filesystem`、lambda init-capture、`template <auto>`）。

学习主线与参考仓库：本轨道以《C++程序设计原理与实践》（PPP）为主线教材，详见 **`Areas/Language/C++/AGENT.md`**（含官方代码仓库与各版习题解答仓库清单、书本章节命名与适配规则）。

---

## 4. 运行与构建

### 4.1 单案例独立运行（主要方式）

所有命令在 `Areas/Language/C++/` 下执行：

```bash
./build.sh 04_optional            # 编译并运行
./build.sh --check 04_optional    # 只编译，不运行
./build.sh CaseStudy/04_optional  # 传目录也可以
./build.sh 04_optional/main.cpp   # 传文件也可以
./build.sh 04_optional -- a b c   # -- 之后的参数传给程序
./build.sh --san 04_optional      # 开启 ASan + UBSan
./build.sh --list                 # 列出全部案例
./build.sh --all                  # 编译全部案例（不运行）
./build.sh --std=c++20 04_optional  # 临时覆盖标准（调试用）
```

产物在 `build/<案例名>/app`，运行时会 `cd` 到案例目录，方便读取相对路径数据文件。

### 4.2 批量 CMake 构建

```bash
cmake -S Areas/Language/C++ -B Areas/Language/C++/build/cmake
cmake --build Areas/Language/C++/build/cmake -j
```

每个案例生成一个同名可执行文件。`CMakeLists.txt` 用 `CONFIGURE_DEPENDS` 通配 `CaseStudy/*/`，新增目录后无需手改。

### 4.3 不依赖脚本的直连方式

方便把案例复制到任何环境：

```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o /tmp/app && /tmp/app
```

---

## 5. 新增案例

```bash
cd Areas/Language/C++
./scripts/new_case.sh 11_my_topic     # 生成 CaseStudy/11_my_topic/main.cpp
$EDITOR CaseStudy/11_my_topic/main.cpp
./build.sh 11_my_topic
```

命名：`NN_snake_case`，`NN` 为两位序号，保持字典序 = 学习顺序。

每个 `main.cpp` 顶部必须包含元信息注释：

```cpp
// Case:  <案例名>
// Topic: <一句话说明演示的 C++17 特性>
// RUN:   ./build.sh <案例名>
// CHECK: ./build.sh --check <案例名>
```

---

## 6. 收集外部例子的适配规则

把从各种渠道收集的 C++ 片段变成正式案例时：

1. 放进独立的 `CaseStudy/<NN_topic>/` 目录。
2. 补齐 `int main()` 与所需标准 `#include`。
3. 将普通标准库头文件整理为一行 `#include <bits/stdc++.h>`，并加 `using namespace std;`；特殊第三方依赖另行注明。
4. 修正到 C++17 语义，消除全部编译告警。
5. 必须通过 `./build.sh <案例>` 且退出码为 0。
6. 需要第三方库时，在案例目录放 `README.md` 说明依赖，或在顶部加 `// DEPS: <库>`；优先改写为纯标准库。
7. 保留出处可在顶部注释加 `// SOURCE: <链接/书名>`。

---

## 7. 质量校验（提交前必跑）

```bash
cd Areas/Language/C++
./build.sh --all                  # g++ 全量编译，要求零告警
./build.sh --all --cxx=clang++    # clang 交叉验证
```

可选工具（当前未安装）：

```bash
sudo apt install -y clang-format clang-tidy
```

---

## 8. 开发环境

- 平台：WSL2 · Ubuntu 22.04 LTS
- 工具链：`g++ 11.4`、`clang++ 14`、`cmake 3.22`、`make 4.3`、`gdb 12.1`
- 一次性安装：

```bash
sudo apt update && sudo apt install -y build-essential clang cmake gdb
```

---

## 9. Git 约定

- `build/`、`*.o`、`*.out` 等产物不入库（见 `.gitignore`）。
- 提交信息风格：`cpp: add <案例>` / `cpp: fix <案例>` / `docs: ...`。
- **只有用户明确要求时才 commit**，不要自动提交。

---

## 10. 给 AI Agent 的硬性规则

- 改动任何 C++ 代码后，必须运行 `./build.sh --all`（必要时加 `--cxx=clang++`）确认零告警。
- 新增案例必须自包含、可独立运行、零告警。
- 保持 C++17；不要擅自升级标准或引入 C++20 特性。
- C++ 案例按本轨道约定使用 `<bits/stdc++.h>` 与 `using namespace std;`。
- 遵循既有命名与目录结构；`PL/`、`Python/`、`Rust/`、`Quant/` 目前为占位，未经确认不要填充。
