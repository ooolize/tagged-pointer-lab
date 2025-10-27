/*
 * @Description:
 * @Author: lize
 * @Date: 2024-09-23
 * @LastEditors: lize
 */
#include <fmt/core.h>

#include "band.h"

using namespace Taggedpointer;

int main() {
  fmt::print("Hello, World!\n");

  Band mygo = Mygo::Create();
  mygo.Vocal();

  Band mujica = Mujica::Create();
  mujica.Vocal();

  // TODO 如何清理？
  // band1.Delete();
  return 0;
}