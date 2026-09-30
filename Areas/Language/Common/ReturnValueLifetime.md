# 函数返回值为什么不会悬空：Python、Rust、C++17 对照

> 范围：Python 3 的普通对象语义、Rust 的安全代码、C++17 的值与引用。讨论的是对象与资源的生命周期，不把“函数作用域结束”误读为“所有在函数内创建的值必须立刻消失”。

## 先给结论

三种语言都可以安全返回函数内创建的**值**。函数结束时退出的是局部作用域；如果结果已经交给调用者，结果可以在调用者处继续存活。真正需要区分的是返回的究竟是**对象/值本身**，还是**指向局部对象的非拥有引用**。

| 问题 | Python 3 | Rust | C++17 |
|---|---|---|---|
| 返回局部创建的值 | `return obj` 返回对象，调用者的名字可绑定到同一对象 | `return value` / 尾表达式把所有权移给调用者 | 按值返回构造调用结果；可能移动或进行返回值优化 |
| 函数退出时局部名字/变量 | 局部名字解除绑定；仍可达的对象保留 | 尚未移走且仍由函数拥有的值被 `drop`；已移走的值由调用者管理 | 局部对象析构；按值返回的结果对象独立存在 |
| 能否返回指向局部对象的引用 | 普通对象引用可返回：它让对象继续可达 | 借用 `&T` 不能指向即将被丢弃的局部值；编译器拒绝 | `T&`/指针可以写出来，但局部对象销毁后会悬空，使用是错误的 |
| 通常何时清理返回的资源 | 对象不可达后由实现回收；外部资源应显式 `close()` / `with` | 调用者拥有的值在其作用域结束时 `Drop` | 调用者的结果对象在其生命周期结束时析构（RAII） |

**这里的“Python 返回引用”只是口语说法**：Python 源码层没有与 C++ `T&` 或 Rust `&T` 等价的普通变量声明。Python 的名字绑定到对象，函数返回的是对象；新的名字可以绑定到同一对象。函数形参也是独立名字，因此 Python 不是 C++ 意义上的“按引用传参”。[Python 名字与对象](https://docs.python.org/3/tutorial/classes.html#python-scopes-and-namespaces)、[Python 参数 FAQ](https://docs.python.org/3/faq/programming.html#how-do-i-write-a-function-with-output-parameters-call-by-reference)。

## 按时间线看一次调用

假设 `make()` 创建一个容器并把它作为结果返回：

| 时刻 | Python | Rust | C++17 |
|---|---|---|---|
| ① 函数内部创建 | 局部名字 `data` 绑定容器对象 | 局部变量 `data` 拥有容器 | 局部对象 `data` 拥有容器存储 |
| ② 执行返回 | 返回对象，外部可以取得新的绑定 | 容器所有权移出函数 | 按值初始化调用结果；可能直接构造、消除复制或移动 |
| ③ 函数退出 | 删除局部绑定；对象仍被返回结果引用，所以可达 | 不再拥有已移出的容器；其他未移出的局部值会被 `drop` | 析构仍存在的局部对象；调用结果不是悬空局部引用 |
| ④ 调用者结束使用 | 没有可达引用后可被回收，时机依实现 | 调用者拥有的值被 `Drop` | 调用者结果对象析构 |

Rust 的“函数结束会销毁局部变量”和 C++ 的“局部对象在作用域结束时析构”都**不意味着按值返回会悬空**。返回值在局部清理前已被交付或构造为结果。[Rust 所有权规则](https://doc.rust-lang.org/book/ch04-01-what-is-ownership.html)、[C++ `return` 顺序](https://eel.is/c++draft/stmt.return)。

## 同一个安全例子：返回新建的列表/向量

### Python

```python
def make():
    data = [1, 2, 3]
    return data

result = make()
alias = result
del result                 # 只移除一个名字
assert alias == [1, 2, 3] # 对象仍由 alias 引用
```

`data` 是局部名字，不是给列表划定寿命的盒子。列表对象在 `make()` 返回后仍可由调用者找到，因而不能被回收。`return` 不自动复制列表；`alias` 与先前的 `result` 指向同一对象。Python 语言保证仍可达的对象不被回收，**不保证对象一旦不可达便立即回收**；CPython 的引用计数只是常见实现方式。[Python 数据模型](https://docs.python.org/3/reference/datamodel.html#objects-values-and-types)。

### Rust

```rust
fn make() -> Vec<i32> {
    let data = vec![1, 2, 3];
    data // 移出函数，交给调用者；此处不 drop 这个 Vec
}

fn main() {
    let result = make();
    assert_eq!(result, vec![1, 2, 3]);
} // result 在这里 drop
```

`Vec` 的所有权从 `data` 移到 `result`。这是 Rust 的值/所有权语义；不要把它理解为“函数返回了一个借用 `&Vec`”。若对象实现 `Drop`，释放责任也跟着所有权转移。[Rust 所有权](https://doc.rust-lang.org/book/ch04-01-what-is-ownership.html)。

### C++17

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> make() {
    vector<int> data{1, 2, 3};
    return data; // 按值返回；可进行 NRVO，否则可移动
}

int main() {
    vector<int> result = make();
    assert((result == vector<int>{1, 2, 3}));
} // result 析构并释放自己拥有的存储
```

返回类型是 `vector<int>`，所以调用者得到的是**值**，不是 `data` 的引用。对于命名局部变量 `return data`，NRVO 是允许但非强制的；若写 `return vector<int>{1, 2, 3};`，C++17 的同类型纯右值结果可直接构造到目标对象。不要把这两种情况都笼统称为“必定复制”或“必定移动”。[C++ 返回语句](https://eel.is/c++draft/stmt.return)、[复制消除规则](https://eel.is/c++draft/class.copy.elision)。

## 真正危险的是返回局部对象的非拥有引用

### Rust：安全代码在编译时拒绝

```rust,compile_fail
fn bad<'a>() -> &'a Vec<i32> {
    let data = vec![1, 2, 3];
    &data // 错误：data 将在函数结束时被丢弃
}
```

`&data` 不取得 `Vec` 的所有权；它只能借用一个仍活着的值。若允许返回，调用者拿到的将是悬空借用，所以 Rust 报 E0515。可改成返回 `Vec<i32>`；如果要返回借用，它必须来自比返回值活得更久的输入或其他有效所有者。[Rust E0515](https://doc.rust-lang.org/stable/error_codes/E0515.html)、[生命周期教程](https://doc.rust-lang.org/book/ch10-03-lifetime-syntax.html)。

### C++17：代码可能编译，但返回的引用悬空

```cpp
// 不要调用这个函数，也不要解引用它的返回值。
const vector<int>& bad() {
    vector<int> data{1, 2, 3};
    return data; // data 随函数退出析构；返回引用不会延长寿命
}
```

返回类型 `const vector<int>&` 没有创建独立的结果容器。函数退出后，`data` 已销毁；使用其返回引用是未定义行为。编译器可能告警，但不能把“没有告警”当作安全证明。改成按值返回 `vector<int>`。[C++ 对象生命周期](https://eel.is/c++draft/basic.life)、[返回值与返回引用](https://eel.is/c++draft/stmt.return)。

### Python：普通返回对象没有这个局部悬空问题

```python
def make_child():
    parent = [[42]]
    return parent[0]

child = make_child()
assert child == [42]
```

局部名字 `parent` 解除绑定后，外层列表可以变为不可达；但内层列表已经作为结果返回，仍由 `child` 引用，所以不会跟着外层列表一起失效。这里依然是**返回对象**，不是返回某个局部变量槽位的地址。[Python 数据模型](https://docs.python.org/3/reference/datamodel.html#objects-values-and-types)。

若刻意使用 `weakref`，它**不**让目标对象继续存活；目标消失后，调用弱引用通常得到 `None`，访问弱代理则会得到 `ReferenceError`。这是受检查的弱引用语义，不是普通返回对象的悬空指针。[Python `weakref`](https://docs.python.org/3/library/weakref.html)。

## 返回调用者提供的数据：三者又有什么不同？

“不能返回对**自己局部对象**的非拥有引用”不等于“不能返回任何引用”。若对象原本由调用者持有，Rust 和 C++ 都能返回指向其中元素的借用/引用；调用者仍须保证源对象及该元素有效。Python 返回元素时，外部名字直接绑定到那个元素对象，不需要让原容器继续活着。

```rust
fn first<'a>(items: &'a [i32]) -> &'a i32 {
    &items[0] // 返回借用，寿命不能超过 items
}

fn main() {
    let values = vec![10, 20];
    let item = first(&values);
    assert_eq!(*item, 10);
}
```

```cpp
#include <bits/stdc++.h>
using namespace std;

const int& first(const vector<int>& items) {
    return items.front(); // 返回调用者容器中元素的引用
}

int main() {
    vector<int> values{10, 20};
    const int& item = first(values);
    assert(item == 10); // values 此时仍活着，且未让引用失效
}
```

```python
def first(items):
    return items[0]

values = [[10], [20]]
item = first(values)
del values
assert item == [10]  # 元素对象仍由 item 引用
```

Rust 的生命周期把返回借用与输入借用关联起来；C++ 的引用没有同等强度的编译期生命周期检查。Python 的 `item` 绑定的是返回的元素对象，而非容器内部槽位。[Rust 生命周期教程](https://doc.rust-lang.org/book/ch10-03-lifetime-syntax.html)、[C++ 引用](https://eel.is/c++draft/dcl.init.ref)、[Python 名字与对象](https://docs.python.org/3/tutorial/classes.html#python-scopes-and-namespaces)。

## 内存仍有效，不代表外部资源该等到回收

对象有效和资源应何时关闭是两个问题。Python 返回打开的文件对象也能让它继续存在，但应由调用者明确关闭，最好使用 `with`；不要把垃圾回收时机当作文件关闭协议。Rust 可把 `File` 的所有权返回给调用者，随后由调用者作用域的 `Drop` 处理。C++17 可按值返回可移动的文件流，随后由结果对象的析构函数关闭资源。[Python 数据模型的资源说明](https://docs.python.org/3/reference/datamodel.html#objects-values-and-types)、[Rust 所有权](https://doc.rust-lang.org/book/ch04-01-what-is-ownership.html)、[C++ 析构](https://eel.is/c++draft/class.dtor)。

## 记忆方式

1. **返回值**：Python 让返回对象继续可达；Rust 转移所有权；C++17 按值构造结果。三者都不会因为函数结束而把合法的返回值变成悬空对象。
2. **返回借用/引用**：Rust 在安全代码中拒绝借用将消失的局部值；C++17 允许写出悬空引用并由程序员负责避免；Python 的普通 `return` 返回对象，不是借用局部变量槽位。
3. **清理时机**：Rust `Drop` 和 C++ RAII 由所有者生命周期决定；Python 对普通内存用可达性管理，但外部资源要显式关闭。

相关笔记：[迭代器中的所有权与资源管理](Iterators.md#迭代器内存资源与所有权)。
