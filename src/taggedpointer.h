/*
 * @Description:
 * @Author: lize
 * @Date: 2025-10-25
 * @LastEditors: lize
 */

#pragma once
#include <cassert>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <type_traits>
namespace Taggedpointer {

// template <typename, typename...>
// struct dump;

// 跨平台的函数签名宏
#ifdef _MSC_VER
#define FUNC_SIG __FUNCSIG__
#elif defined(__GNUC__) || defined(__clang__)
#define FUNC_SIG __PRETTY_FUNCTION__
#else
#define FUNC_SIG __func__
#endif

template <typename... Ts>
void dump() {
  std::cout << FUNC_SIG << std::endl;
}

template <typename T, typename... Ts>
constexpr int64_t IndexOf() {
  int64_t index = 0, cur = 0;
  (((std::is_same_v<T, Ts>) ? (index = cur), true : (++cur), false) || ...);
  return cur >= sizeof...(Ts) ? -1 : index;
}

template <typename... Ts>
class TaggedPointer {
 public:
  template <typename T>
  TaggedPointer(T* ptr) {
    auto index = IndexOf<T, Ts...>();
    // dump<T, Ts...>();
    assert(index >= 0);
    int64_t mask = index == 0 ? 0LL : 1LL << (index - 1 + 63 - 7);
    _ptr = reinterpret_cast<uint64_t>(ptr) | mask;
  }

  template <typename Func>
  void Dispatch(Func func) {
    int64_t index = _ptr >> (63 - 7);
    dispatch_imp(func, index, std::index_sequence_for<Ts...>{});
  }

 private:
  template <typename Func, std::size_t... Is>
  auto dispatch_imp(Func func, int64_t index, std::index_sequence<Is...>) {
    (((index == Is)
        ? (func(reinterpret_cast<std::tuple_element_t<Is, std::tuple<Ts...>>*>(
             _ptr & 0x00FFFFFFFFFFFFFF)),
           true)
        : false) ||
     ...);
  }

  uint64_t _ptr{0};
};

}  // namespace Taggedpointer