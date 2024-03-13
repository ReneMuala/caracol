#include "../src/caracol.hpp"

using namespace caracol;

int main() {
  int32_t begin = 1;
  int32_t end = 100;

  caracol::vm<int32_t, 24, int32_t> vm;
  /* clang-format off */

  int32_t data[] = {
    LOAD, 0, 0,
    LOAD, 1, begin, 
    LOAD, 2, end, 
    ADD, 0, 1,
    INCR, 1,
    RJLE, 1, 2, -5,
    PRINT, 0, 
    HALT
  };

  /* clang-format on */
  vm.set_pc(3);
  vm.write_block_array(3, data, sizeof(data) / sizeof(int32_t));
  vm.start();
}