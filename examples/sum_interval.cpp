#include "../src/caracol.hpp"

using namespace caracol;

int main() {
  int32_t begin = 1;
  int32_t end = 100;

  caracol::vm<int32_t, 16, int32_t> vm;
  /* clang-format off */

  int32_t data[] = {
    LOAD, 0, begin, 
    LOAD, 1, end, 
    ADD, 0, 1, 
    PRINT, 0, 
    HALT
  };

  /* clang-format on */
  vm.set_pc(2);
  vm.write_block_array(2, data, sizeof(data) / sizeof(int32_t));
  vm.start();
}