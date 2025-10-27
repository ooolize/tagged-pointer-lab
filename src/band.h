/*
 * @Description:
 * @Author: lize
 * @Date: 2025-10-25
 * @LastEditors: lize
 */
#pragma once

#include <fmt/core.h>

#include "taggedpointer.h"

namespace Taggedpointer {

class Mygo;
class Mujica;

class Band : public TaggedPointer<Mygo, Mujica> {
 public:
  using TaggedPointer::TaggedPointer;
  void Vocal() {
    auto func = [](auto ptr) { ptr->Vocal(); };
    Dispatch(func);
  }
};

class Mygo {
 public:
  static Mygo* Create() {
    return new Mygo();
  }
  // static void Destroy() {
  //   ~Mygo();
  // }
  void Vocal() {
    fmt::print("gugu gaga\n");
  };
};

class Mujica {
 public:
  static Mujica* Create() {
    return new Mujica();
  }
  void Vocal() {
    fmt::print("saki saki saki\n");
  };
};

}  // namespace Taggedpointer