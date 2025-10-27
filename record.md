<!--
 * @Description: 
 * @Author: lize
 * @Date: 2025-01-21
 * @LastEditors: lize
-->
### 问题

+ 返回类型不正确
```c++
auto DecodePtr() const -> uint64_t  // ❌ 应该返回指针类型
```
+ 表达式的结果不是常数

这里index是运行时才能确定的值，不能用于static_assert。

```c++
    int8_t index = _ptr >> (63 - 7);
    static_assert(index >= 0, "Type T is not in the type list Ts...");
    using Type = std::tuple_element_t<index, std::tuple<Ts...>>;
    return reinterpret_cast<Type*>(_ptr & 0x00FFFFFFFFFFFFFF);
```
+ 向一个函数传递类型以解参数包

+  error C2227: “->Vocal”的左边必须指向类/结构/联合/泛型类型

+ 错误的使用模板

```c++
constexpr int8_t IndexOf() {
  if (sizeof...(Ts) == 0) {
    return -1;  // Not found
  }
  if (std::is_same_v<T, Ts>) {
    return 0;
  } else {
    auto ret = IndexOf<T, Ts...>();
    return ret < 0 ? -1 : ret + 1;
  }
  // TODO 折叠表达式
}
```

+ sizeof...(Ts) 参数包的大小

+ ((index == Is ? (result = ...), true : false) || ...);

+ 逗号表达式不能含有 return 语句

+ 1LL << (index + 63 - 7)

