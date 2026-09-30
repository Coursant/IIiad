# AGENT.md — C++ 学习轨道（参照《C++程序设计原理与实践》）

> 本文件是 `Areas/Language/C++/` 的专属说明，补充根目录 `AGENT.md`。
> 总原则：本轨道的练习与学习以 **Bjarne Stroustrup《C++程序设计原理与实践》** 为主线教材。

---

## 1. 学习主线

- 教材：**《C++程序设计原理与实践》**（原书名 *Programming: Principles and Practice Using C++*，作者 Bjarne Stroustrup，简称 **PPP**）。
- 目标：跟随书中章节（Try this / Drill / Exercise）循序渐进，把每段代码变成 `CaseStudy/` 下可独立运行、零告警的案例。
- 本仓库标准：**C++17**（见根 `AGENT.md` 第 3 节）。
- 为简化练习，案例统一使用 `#include <bits/stdc++.h>` 与 `using namespace std;`。这是 GCC/libstdc++ 提供的非标准头文件；本仓库当前 g++ 工具链支持。
- 编译/运行脚本用法见 **`SCRIPTS.md`**。

---

## 2. 版本与标准对照

| 版本 | 原书覆盖标准 | 与本仓库关系 |
|------|--------------|--------------|
| 第 2 版（PPP2，2014，中译本对应此版） | C++11 / C++14 | **主参照**，示例绝大多数可直接用于 C++17 |
| 第 3 版（PPP3，2024） | C++20 / C++23 + modules | **补充参照**，新特性示例需改写为 C++17 |

约定：

- 书中若使用 C++20+ 特性（`concepts`、`ranges`、`import std;`、`std::format` 等），在本仓库**改写为 C++17 等价写法**，并在案例顶部注释标注差异。
- 书中为教学而用的 `std_lib_facilities.h` 不直接进入本仓库正式案例；`using namespace std;` 按本仓库便捷写法保留（见第 6 节适配规则）。

---

## 3. 官方代码与支撑文件

- 官方下载页：<https://www.stroustrup.com/Programming/>（`PPP2code.zip`，含全部示例与头文件）
- 官方 GitHub 镜像（头文件，作者本人账号）：
  <https://github.com/BjarneStroustrup/Programming-_Principles_and_Practice_Using_Cpp>
  - 关键文件：`std_lib_facilities.h`、`PPP_support.h`、`PPPheaders.h`、`Graph.h/.cpp`、`GUI.h/.cpp`、`Simple_window.h`、`Point.h` 等
- 第 3 版支撑文件（`PPP_support.h` / `PPPheaders.h`）见下方 PPP3 解答仓库内的 `PPP_support/` 目录。
- `std_lib_facilities.h` 单文件备选镜像：<https://github.com/sunchaesk/std_lib_facilities.h>

> 说明：书中第 12–16 章的图形/GUI 代码依赖 **FLTK**；不装 FLTK 时这些案例只做阅读，不参与编译校验。

---

## 4. 习题解答参考仓库

### 4.1 第 2 版（PPP2，主参照）

| 仓库 | 说明 |
|------|------|
| <https://github.com/thelastpolaris/Programming-Principles-and-Practice-Using-C-> | 覆盖第 4–17 章练习，含 review/glossary 与 FLTK 安装说明（★最多，首选） |
| <https://github.com/Ziezi/Programming-Principles-and-Practice-Using-C-by-Bjarne-Stroustrup-> | 按章组织的练习解答 |
| <https://github.com/michaelkolesidis/programming-principles-and-practice-using-cpp-solutions> | 部分练习解答，结构清晰 |
| <https://github.com/starkingz/PPP-Projects> | drills + exercises + 项目 |
| <https://github.com/AthanasiosKitsanos/Principles_and_Practice_Using_Cpp> | drills 与练习解答 |
| <https://github.com/massmarines/Programming-Principles-and-Practice-using-Cpp> | 练习解答 |
| <https://github.com/vaibssingh/programming-principles-and-practice> | 练习解答 |
| <https://github.com/JordanJacobson1996/Programming-Practice-and-Principles-using-C-solutions> | 第 2 版练习解答 |

### 4.2 第 3 版（PPP3，补充参照）

| 仓库 | 说明 |
|------|------|
| <https://github.com/orlambda/PPP3> | 按章组织，含 `PPP_support/` 与笔记（★最多） |
| <https://github.com/MrPuppeteer/ppp3> | examples + try this + drills + exercises |
| <https://github.com/trapperdot00/PPP3_exercises> | 练习解答，标签 cpp20/cpp23 |
| <https://github.com/ramiomer94/Learning_Cpp_PPP_3rdEdition_Solutions> | 第 3 版练习解答 |
| <https://github.com/dungp-dsai/Programming-Principles-and-Practice-Using-C-3rd-Edition> | 笔记 + drills/exercises/try this |
| <https://github.com/jmerort/PPP3> | drills 与练习 |

### 4.3 GUI / 跨平台移植

| 仓库 | 说明 |
|------|------|
| <https://github.com/villevoutilainen/ProgrammingPrinciplesAndPracticeUsingQt> | 把书中 FLTK 图形章节移植到 Qt 的起步工程 |
| <https://github.com/thelastpolaris/Programming-Principles-and-Practice-Using-C->（`review_and_glossary/`） | FLTK 安装步骤与说明 |

> 使用解答仓库时：先自己写，再对照；采纳他人代码须在案例顶部用 `// SOURCE:` 注明来源仓库与路径。

---

## 5. 案例命名与书本章节的对应

`CaseStudy/` 下两种命名：

| 类型 | 命名 | 示例 |
|------|------|------|
| 语言特性示范（非书本绑定） | `NN_topic` | `04_optional`、`07_constexpr_if_fold` |
| 书本示例 / Drill / Exercise | `ppp2_ch<CC>_<kind><NN>_<slug>` | `ppp2_ch04_ex05_quadratic`、`ppp2_ch03_drill01_names` |

`<kind>` 取值：`try`（Try this）、`drill`（Drill）、`ex`（Exercise）、`demo`（书中示例）。

每个书本案例顶部必须标注：

```cpp
// Case:  ppp2_ch04_ex05_quadratic
// Topic: PPP2 Ch.4 Exercise 5 - 解一元二次方程
// BOOK:  PPP2 Ch.4 §4.6 / Exercise 5
// RUN:   ./build.sh ppp2_ch04_ex05_quadratic
// CHECK: ./build.sh --check ppp2_ch04_ex05_quadratic
```

`BOOK:` 行格式固定为 `PPP2|PPP3 Ch.<章> §<节> / <Try this|Drill|Exercise> <号>`，便于检索进度。

---

## 6. 书中代码 → 本仓库的适配规则

在根 `AGENT.md` 第 6 节基础上，针对本书追加：

1. **移除 `std_lib_facilities.h`**：使用 `<bits/stdc++.h>`。确需该头提供的教学辅助函数时，复制到案例目录并加 `// DEPS: std_lib_facilities.h (PPP2)`。
2. **命名空间**：统一在头文件后写 `using namespace std;`；案例中可直接使用标准库名称。
3. **错误处理**：把 `error("...")` 改为 `throw std::runtime_error("...")`；`keep_window_open()` 之类教学辅助函数删除。
4. **C++17 化**：C++20+ 写法改写为 C++17 等价物，并注释原写法。
5. **零告警 + 独立运行**：必须通过 `./build.sh <案例>`，退出码 0。
6. **GUI 章节（约 Ch.12–16）**：
   - 依赖 FLTK，单独成目录并写 `README.md` 记录安装步骤；
   - 顶部标 `// DEPS: FLTK`；
   - 默认**不纳入** `./build.sh --all` 的必过校验（无 FLTK 环境下会失败），由人工单独构建。
7. **数据文件**：书中用到的输入文件（如 `input.txt`）放进案例目录；`build.sh` 运行时已 `cd` 到案例目录，可直接相对路径访问。

---

## 7. 章节进度表（PPP2）

> 状态：`[ ]` 未开始 · `[~]` 进行中 · `[x]` 已完成。完成一章即更新此表。

| 章 | 主题 | 状态 |
|----|------|------|
| 1 | Computers, People, and Programming | [ ] |
| 2 | Hello, World! | [ ] |
| 3 | Objects, Types, and Values | [ ] |
| 4 | Computation | [ ] |
| 5 | Errors | [ ] |
| 6 | Writing a Program | [ ] |
| 7 | Completing a Program | [ ] |
| 8 | Technicalities: Functions, etc. | [ ] |
| 9 | Technicalities: Classes, etc. | [ ] |
| 10 | Input and Output Streams | [ ] |
| 11 | Customizing Input and Output | [ ] |
| 12 | A Display Model | [ ] |
| 13 | Graphics Classes | [ ] |
| 14 | Graphics Class Design | [ ] |
| 15 | Graphing Functions and Data | [ ] |
| 16 | Graphical User Interfaces | [ ] |
| 17 | Vector and Free Store | [ ] |
| 18 | Vectors and Arrays | [ ] |
| 19 | Vector, Templates, and Exceptions | [ ] |
| 20 | Containers and Iterators | [ ] |
| 21 | Algorithms and Maps | [ ] |
| 22 | Ideals and History | [ ] |
| 23 | Text Processing | [ ] |
| 24 | Numerics | [ ] |
| 25 | Embedded Systems Programming | [ ] |
| 26 | Testing | [ ] |
| 27 | The C Programming Language | [ ] |

---

## 8. 引用与版权

- 书中示例代码版权归 Bjarne Stroustrup 及出版社所有，本仓库仅作**个人学习**记录，不对外发布、不用于商业用途。
- 引用他人解答代码时，务必在案例顶部用 `// SOURCE: <仓库 URL / 路径>` 标注出处。
