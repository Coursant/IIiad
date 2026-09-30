# 迭代器：C++17、Python、Rust 的设计与使用

> 范围：C++17、Python 3、Rust 稳定版的基础迭代接口。C++20 `ranges`/`concepts` 不属于本仓库的 C++17 案例范围。

## 先抓住共同问题

迭代器把“怎样依次取得元素”从“元素存在哪里”中分离出来。它可以遍历数组、链表、生成的数列或文件内容；调用方只按接口前进，不必知道底层结构。三种语言都能用于 `for`，但它们把**当前位置、结束信号、元素所有权与算法约束**放在不同位置。

| 问题 | C++17 | Python 3 | Rust |
|---|---|---|---|
| 取得遍历能力 | `begin()` 与 `end()` 给出一对位置 | `iter(obj)` 返回迭代器 | `IntoIterator::into_iter`；常用 `.iter()`、`.iter_mut()`、`.into_iter()` |
| 取当前/下一项 | `*it` 取当前项，`++it` 前进 | `next(it)` 同时前进并返回一项 | `it.next()` 同时前进并返回一项 |
| 结束 | `it == end`；`end` 不可解引用 | 抛出 `StopIteration` | 返回 `None`，有值时为 `Some(item)` |
| 元素类型与能力 | 静态类型；输入、前向、双向、随机访问等要求决定可用算法 | 动态协议；协议本身不表示随机访问能力 | `Iterator::Item` 是关联类型；更多能力由其他 trait 表示 |
| 修改/所有权 | `iterator` 与 `const_iterator` 区分可否写入；还要遵守容器失效规则 | 迭代通常给出对象引用；给循环变量重新赋值不会替换容器槽位 | `iter()` 产出 `&T`，`iter_mut()` 产出 `&mut T`，`into_iter()` 通常消费集合并产出 `T` |

**不要把三者当成同一个对象模型**：C++ 的迭代器通常表示区间里的一个位置；Python/Rust 的 `next` 迭代器通常自己保存推进状态。Rust 的 `Item` 也可以是引用，不总是拥有的值。[C++ 迭代器要求](https://eel.is/c++draft/iterator.requirements)、[Python 迭代器教程](https://docs.python.org/3/tutorial/classes.html#iterators)、[Rust `Iterator` trait](https://doc.rust-lang.org/std/iter/trait.Iterator.html)。

## C++17：设计与使用

STL 算法通常接收半开区间 `[first, last)`：`first` 指向首元素，`last` 指向尾后位置。空区间满足 `first == last`。尾后位置只能比较，不能 `*last`。指针也可充当迭代器，所以同一套算法可处理数组和容器。[C++ 迭代器要求](https://eel.is/c++draft/iterator.requirements)。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> values{3, 1, 2};
    sort(values.begin(), values.end());           // vector 迭代器支持随机访问
    auto it = find(values.begin(), values.end(), 2);
    if (it != values.end()) cout << *it << '\n';  // 先检查，再解引用
    for (const auto& x : values) cout << x << ' ';
}
```

迭代器能力会限制算法：输入迭代器适合单次读取；前向迭代器可多次遍历；双向迭代器还能 `--it`；随机访问迭代器可 `it + n`、`it2 - it1`，因此 `std::sort` 不能直接排序 `std::list`，应调用 `list.sort()`。C++17 使用传统 iterator category/要求描述这些能力；正式的 `contiguous_iterator` concept 属于 C++20 之后的接口，不要误写进 C++17 案例。[C++ 算法迭代器要求](https://eel.is/c++draft/algorithms.requirements)。

设计自定义可遍历对象时，至少要决定：当前位置如何表示，何时到尾，`*` 返回值还是引用，迭代器能否复制并多次遍历，以及修改容器后位置是否有效。下面是**仅供范围 `for` 使用**的最小例子；它未声明完整的标准迭代器关联类型，不能据此声称可用于所有 STL 算法。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct CountTo {
    int limit;
    struct Iterator {
        int current;
        int operator*() const { return current; }
        Iterator& operator++() { ++current; return *this; }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    Iterator begin() const { return {0}; }
    Iterator end() const { return {limit}; }
};

int main() {
    for (int x : CountTo{3}) cout << x << ' '; // 0 1 2
}
```

需要让自定义迭代器用于 `std::find`、`std::accumulate` 等算法时，继续补足相应 category 的语义、比较与自增运算，以及 `iterator_traits` 能读取的 `value_type`、`difference_type`、`reference`、`pointer`、`iterator_category`。类别声明必须与真实操作和多次遍历保证相符。[C++17 输入迭代器要求](https://eel.is/c++draft/input.iterators)。

**最容易出错的是失效**：`vector` 扩容会使已有迭代器、指针、引用失效；即使不扩容，插入/删除位置附近也可能失效。不要保存 `begin()` 后又随意 `push_back()` 再用旧迭代器。修改过程中需要继续遍历时，按容器规则使用 `erase` 的返回迭代器等。[`vector` 修改规则](https://eel.is/c++draft/vector.modifiers)。

## Python：设计与使用

**可迭代对象**负责 `__iter__()`；返回的**迭代器**负责 `__next__()`，耗尽时抛 `StopIteration`。`for` 会调用这套协议。生成器函数用 `yield` 自动保存状态并生成迭代器，通常比手写类简单。[Python 官方教程](https://docs.python.org/3/tutorial/classes.html#iterators)。

```python
class CountTo:
    def __init__(self, limit):
        self.limit = limit

    def __iter__(self):
        for n in range(self.limit):
            yield n

print(list(CountTo(3)))  # [0, 1, 2]
it = iter(CountTo(3))
print(next(it))           # 0
```

这里 `CountTo` 可重复取得新迭代器；`it` 本身有消耗进度。`for x in values` 中给 `x` 赋新值不会替换列表元素；若要修改列表槽位，需要索引赋值。生成器表达式与 `itertools` 可把筛选、映射串起来，并在取值时逐步计算。[Python 生成器教程](https://docs.python.org/3/tutorial/classes.html#generators)、[`itertools`](https://docs.python.org/3/library/itertools.html)。

## Rust：设计与使用

核心接口是 `trait Iterator { type Item; fn next(&mut self) -> Option<Self::Item>; }`。实现 `next` 后便可获得 `map`、`filter`、`sum` 等适配器/消费方法；`for` 通过 `IntoIterator` 取得迭代器。迭代适配器通常是惰性的，直到被 `for`、`collect`、`sum` 等消费。[Rust `Iterator`](https://doc.rust-lang.org/std/iter/trait.Iterator.html)、[Rust 迭代器教程](https://doc.rust-lang.org/book/ch13-02-iterators.html)。

```rust
struct CountTo { current: i32, limit: i32 }

impl Iterator for CountTo {
    type Item = i32;
    fn next(&mut self) -> Option<Self::Item> {
        if self.current >= self.limit { return None; }
        let value = self.current;
        self.current += 1;
        Some(value)
    }
}

fn main() {
    for x in (CountTo { current: 0, limit: 3 }) {
        print!("{x} "); // 0 1 2
    }
    let mut values = vec![1, 2, 3];
    for x in values.iter_mut() { *x *= 2; }
    assert_eq!(values, vec![2, 4, 6]);
}
```

对于 `Vec<T>`，`values.iter()` 借用并产出 `&T`，`values.iter_mut()` 可变借用并产出 `&mut T`，`values.into_iter()` 消费集合并产出 `T`；选择哪一种决定后续还能否使用原集合或同时修改它。`for x in &values` 和 `for x in &mut values` 是常见简写。[Rust 标准库迭代模块](https://doc.rust-lang.org/std/iter/#iterating-by-reference)。

## 用同一任务对照

任务：对整数序列“筛出偶数 → 平方 → 求和”，输入 `[1, 2, 3, 4]`，输出 `20`。

```cpp
// C++17：使用标准算法和迭代器区间
vector<int> values{1, 2, 3, 4};
vector<int> evens;
copy_if(values.begin(), values.end(), back_inserter(evens),
        [](int x) { return x % 2 == 0; });
int total = accumulate(evens.begin(), evens.end(), 0,
                       [](int sum, int x) { return sum + x * x; });
// total == 20
```

```python
# Python：生成器表达式逐项产生值
values = [1, 2, 3, 4]
total = sum(x * x for x in values if x % 2 == 0)  # 20
```

```rust
// Rust：借用集合并串联惰性适配器，最后 sum 消费迭代器
let values = vec![1, 2, 3, 4];
let total: i32 = values.iter().filter(|x| **x % 2 == 0)
    .map(|x| x * x).sum(); // 20
```

C++17 这里用了中间 `vector`，是为了展示标准算法如何通过输入/输出迭代器衔接；并非 C++17 只能这样写。三种语言也都能用普通循环完成任务。

## 迭代器、内存资源与所有权

先区分三件事：**谁拥有容器及其存储**、**迭代器取得的是元素的引用还是值**、**提前停止后谁负责释放尚未处理的资源**。迭代器只是遍历接口；它是否拥有数据由具体类型决定，不能仅凭“是迭代器”推断。

| 场景 | C++17 | Python 3 | Rust |
|---|---|---|---|
| 常见容器迭代器与容器的关系 | `vector<T>::iterator` 通常是不拥有容器的游标；容器销毁或发生规定的失效操作后不得再用 | `iter(obj)` 得到对象；它是否保留源对象、保留多久取决于具体迭代器实现，不能假设 `for` 退出就释放资源 | `values.iter()` / `.iter_mut()` 借用集合；编译器禁止借用仍被使用时移动或销毁集合。`values.into_iter()` 对 `Vec<T>` 转移集合所有权 |
| 单个元素如何取得 | `*it` 通常是引用；`auto x = *it` 可能复制，`auto& x = *it` 不复制；`std::move(*it)` 可把可移动元素的所有权转出 | `next(it)` 返回 Python 对象；给变量换绑不会自动复制对象，也不会自动修改原容器槽位 | `iter()` 得 `&T`，`iter_mut()` 得 `&mut T`，`Vec<T>::into_iter()` 得 `T`，即逐项移出 |
| 提前 `break` / 停止 | 迭代器本身不负责销毁容器；拥有资源的局部对象按 RAII 在作用域结束时析构 | 不保证任意迭代器持有的外部资源在 `break` 时立即释放；文件等应使用 `with` 或显式 `close()` | 借用迭代器结束使用后可再操作集合；消费型 `Vec::IntoIter` 被丢弃时清理未取出的元素及其分配 |
| 延迟计算与额外内存 | 普通算法是否生成中间容器取决于写法；输出到 `vector` 会存结果 | 生成器可逐项产生；`list(generator)` 才收集为列表 | `map`/`filter` 适配器惰性；`collect::<Vec<_>>()` 收集为新容器 |

### C++17：游标不等于所有者

`vector` 拥有其元素和存储，普通 `vector::iterator` 不延长它的生命周期。扩容会使旧迭代器失效；这与是否使用 `unique_ptr` 无关。`unique_ptr` 表示**元素拥有某项资源**，从迭代器解引用处 `move` 才会转移该元素的所有权。把 `std::move` 理解为“允许移动的转换”，实际转移发生在目标对象的移动构造/赋值中。[C++ 对象生命周期](https://eel.is/c++draft/basic.life)、[`vector` 失效规则](https://eel.is/c++draft/vector.modifiers)。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<unique_ptr<int>> values;
    values.push_back(make_unique<int>(7));
    auto it = values.begin();        // 借用位置，不拥有 vector
    unique_ptr<int> owner = move(*it); // 把第一个元素拥有的 int 转给 owner
    assert(*owner == 7);
    assert(values[0] == nullptr);   // 该槽位已被移走
} // owner 与 values 各自按作用域析构
```

不要返回指向局部 `vector` 元素的迭代器，也不要在可能导致重分配的 `push_back` 后继续使用旧迭代器。迭代器失效是生存期问题；RAII 不会自动替你检测悬空迭代器。

### Python：对象引用与外部资源分开管理

Python 变量绑定到对象。`next(it)` 交回一个对象引用；即使 `it` 随后结束，已保存在变量中的对象也可继续存在。列表迭代器、生成器和文件迭代器的持有关系各不相同，因此不能把 Python 的迭代协议当作所有权检查器。CPython 使用引用计数并处理引用环，但 Python 文档明确要求不要依赖对象变为不可达时立即完成清理；文件等外部资源用 `with` 明确划定生命周期。[Python 数据模型](https://docs.python.org/3/reference/datamodel.html#objects-values-and-types)、[垃圾回收接口](https://docs.python.org/3/library/gc.html)。

```python
from io import StringIO

with StringIO("first\nsecond\n") as stream:
    lines = iter(stream)
    first = next(lines).strip()  # 提前停止遍历
    assert first == "first"

assert stream.closed          # with 负责关闭，不靠遍历耗尽
```

生成器还可能保存暂停时的局部变量和资源；若生成器内部持有文件等资源，应设计明确的关闭路径，例如在生成器的 `finally` 中释放，并在调用侧使用 `close()` 或上下文管理。`break` 本身不等于对任意迭代器调用 `close()`。[Python 生成器 `close()`](https://docs.python.org/3/reference/expressions.html#generator.close)、[`contextlib.closing`](https://docs.python.org/3/library/contextlib.html#contextlib.closing)。

### Rust：借用遍历与消费遍历

对 `Vec<T>`，`.iter()` 和 `.iter_mut()` 的迭代器持有借用；集合仍是所有者，借用规则在编译期约束同时读写和生命周期。`.into_iter()` 消费 `Vec<T>`，得到持有其数据的迭代器；每次 `next()` 移出一个 `T`。若只取了一部分就丢弃这个迭代器，剩余元素会被丢弃，缓冲区由迭代器清理。[Rust 迭代模块](https://doc.rust-lang.org/std/iter/)、[`Vec::into_iter`](https://doc.rust-lang.org/std/vec/struct.Vec.html#impl-IntoIterator-for-Vec%3CT,+A%3E)、[Rust 所有权规则](https://doc.rust-lang.org/book/ch04-01-what-is-ownership.html)。

```rust
fn main() {
    let values = vec![String::from("a"), String::from("b")];
    {
        let mut borrowed = values.iter();
        assert_eq!(borrowed.next().map(String::as_str), Some("a"));
    } // 借用迭代器结束，values 仍可使用

    let mut owned = values.into_iter(); // values 已移动，不能再使用
    let first: String = owned.next().unwrap();
    assert_eq!(first, "a");
    drop(owned); // 未取出的 "b" 与迭代器持有的分配在此清理
}
```

`iter()` 的“零复制”只表示遍历时借用现有元素；后续 `.cloned()`、`collect()` 或生成新对象的 `map()` 仍可能复制、分配。类似地，C++ 的 `auto x = *it` 可能复制，而 Python 的生成器也可能每次新建对象。比较内存开销时要看整条处理链，而不只看迭代器接口。

## 何时选哪种写法

- **C++17**：只需逐项处理时先用范围 `for`；要复用通用算法、定位元素或操作子区间时用迭代器。写修改容器的循环前先查失效规则。
- **Python**：先用 `for`、生成器表达式；需要保存并手动推进状态时用 `iter()`/`next()`。自定义遍历优先考虑 `yield`。
- **Rust**：先判断是否需要所有权：只读用 `.iter()`，修改元素用 `.iter_mut()`，转移元素用 `.into_iter()`；再决定用 `for` 还是适配器链。

## 参考

- [C++ 迭代器要求（标准草案）](https://eel.is/c++draft/iterator.requirements)、[算法对迭代器的要求](https://eel.is/c++draft/algorithms.requirements)、[`vector` 失效规则](https://eel.is/c++draft/vector.modifiers)
- [Python 教程：迭代器与生成器](https://docs.python.org/3/tutorial/classes.html#iterators)、[`itertools` 官方文档](https://docs.python.org/3/library/itertools.html)
- [Rust `Iterator` trait](https://doc.rust-lang.org/std/iter/trait.Iterator.html)、[迭代模块与 `IntoIterator`](https://doc.rust-lang.org/std/iter/)、[The Rust Programming Language：迭代器](https://doc.rust-lang.org/book/ch13-02-iterators.html)
- 所有权与资源清理：[C++ 对象生命周期](https://eel.is/c++draft/basic.life)、[Python 数据模型](https://docs.python.org/3/reference/datamodel.html#objects-values-and-types)、[Rust 所有权](https://doc.rust-lang.org/book/ch04-01-what-is-ownership.html)
