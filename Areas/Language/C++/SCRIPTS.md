# SCRIPTS.md — C++ 轨道脚本说明

> 适用范围：`Areas/Language/C++/`。列出当前**可直接使用**的全部脚本、用法与行为。
> 新增脚本时，必须同步更新本文档，并在 `DESIGN.md` 第 5 节追加记录。

## 概览

| 脚本 | 路径 | 作用 |
|------|------|------|
| `build.sh` | `Areas/Language/C++/build.sh` | 编译并运行单个案例；或批量编译全部案例 |
| `new_case.sh` | `Areas/Language/C++/scripts/new_case.sh` | 生成新案例骨架（目录 + `main.cpp` 模板） |

所有命令均在 `Areas/Language/C++/` 目录下执行。两个脚本都支持 `-h` / `--help`。

---

## 1. `build.sh`

**作用**：把一个案例（目录 / 单个 `.cpp` / 案例名）用 C++17 编译，然后运行。

### 语法

```bash
./build.sh [选项] <case-name | 目录 | 文件.cpp> [-- 传给程序的参数...]
```

### 目标解析规则

| 传入 | 解释 | 案例名 / 产物 |
|------|------|---------------|
| `04_optional` | 先当目录，再当 `CaseStudy/04_optional` | `04_optional` |
| `CaseStudy/04_optional` | 目录 | `04_optional`（取目录名） |
| `04_optional/main.cpp` | 单个源文件 | `main`（取文件名去扩展名） |

### 选项

| 选项 | 说明 |
|------|------|
| `--check` | 只编译，不运行 |
| `--all` | 编译 `CaseStudy/` 下**全部**案例（不运行），任一失败则退出码非 0 |
| `--list` | 列出全部案例名 |
| `--san` | 开启 AddressSanitizer + UBSan（`-fsanitize=address,undefined`） |
| `--std=<std>` | 覆盖 C++ 标准，默认 `c++17` |
| `--cxx=<cmd>` | 覆盖编译器，默认 `$CXX` 或 `g++` |
| `-h`, `--help` | 显示帮助 |
| `--` | 其后的参数原样传给被运行的程序 |

### 编译行为

- 编译选项：`-std=<std> -Wall -Wextra -Wpedantic -Wshadow -O2 -g`，并加 `-I<案例目录>`。
- 源文件：案例目录下**第一层**全部 `*.cpp`（多文件案例自动一起编译）。
- 产物：`build/<案例名>/app`（`build/` 已 git 忽略）。
- 运行前会 `cd` 到案例目录，因此案例可用相对路径读取同目录数据文件。
- 程序退出码经 `exec` 原样返回。

### 退出码

| 码 | 含义 |
|----|------|
| `0` | 成功 |
| `2` | 用法错误 / 目标不存在 / 目录内无 `.cpp` |
| 其它 | 编译失败或程序自身返回的退出码 |

### 示例

```bash
./build.sh --list                  # 看有哪些案例
./build.sh 04_optional             # 编译并运行
./build.sh --check 04_optional     # 只编译
./build.sh --san 04_optional       # 带 ASan/UBSan 运行
./build.sh --all                   # 全量编译（提交前必跑）
./build.sh --all --cxx=clang++     # 换 clang 全量编译
./build.sh 01_hello -- a b c       # 程序会收到 a b c 三个参数
./build.sh --std=c++20 --check 01_hello   # 临时用其它标准
```

### 注意

- `--all` **只编译不运行**；GUI/FLTK 类案例不应纳入（无 FLTK 环境会失败，见 `AGENT.md` 第 6 节）。
- 传**单个文件**时案例名会变成 `main`，产物在 `build/main/app`，容易与其它单文件混淆；日常建议传**目录**或**案例名**。

---

## 2. `scripts/new_case.sh`

**作用**：在 `CaseStudy/` 下生成一个新案例目录，并写入带元信息注释的 `main.cpp` 模板。

### 语法

```bash
./scripts/new_case.sh <NN_snake_name>
./scripts/new_case.sh -h
```

### 行为

- 目录已存在 → 报错并退出码 `1`（不覆盖）。
- 否则创建 `CaseStudy/<name>/main.cpp`，内容为：

```cpp
// Case:  <name>
// Topic: <describe the C++17 feature(s) demonstrated>
// RUN:   ./build.sh <name>
// CHECK: ./build.sh --check <name>
#include <iostream>

int main() {
    std::cout << "<name>\n";
    return 0;
}
```

### 示例

```bash
./scripts/new_case.sh 11_my_topic
# 编辑 CaseStudy/11_my_topic/main.cpp
./build.sh 11_my_topic
```

### 退出码

| 码 | 含义 |
|----|------|
| `0` | 创建成功 |
| `1` | 目标目录已存在 |
| `2` | 缺少参数 / 用法错误 |

---

## 3. 常见任务速查

| 任务 | 命令 |
|------|------|
| 新建并跑通一个案例 | `./scripts/new_case.sh 11_x && ./build.sh 11_x` |
| 提交前全量校验 | `./build.sh --all && ./build.sh --all --cxx=clang++` |
| 单例排查内存问题 | `./build.sh --san <case>` |
| 用 CMake 批量构建 | `cmake -S . -B build/cmake && cmake --build build/cmake -j` |
| 清理构建产物 | `rm -rf build` |
| 不用脚本、直连编译 | `g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o /tmp/app && /tmp/app` |

---

## 4. 维护约定

- 每个脚本顶部必须有注释块，并实现 `-h` / `--help`。
- 脚本行为变更后，同步更新本文档对应条目。
- 新增脚本需：加入本文档概览表 + 在 `DESIGN.md` 第 5 节登记。
