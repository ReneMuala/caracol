#include "../src/caracol.hpp"

using namespace caracol;

int main() {
  int64_t number = 10;
  caracol::vm<int64_t, 32> vm;
  /* clang-format off */
  int64_t data[] = {
    LOAD, 0, number, 
    LOAD, 1, 1, 
    LOAD, 2, 1, 
    MUL, 2, 0,
    SUB,  0, 1,
    RJGT, 0, 1, -6,
    PRINT, 2,
    HALT
  };
  /* clang-format on */
  vm.set_pc(3);
  vm.write_block_array(3, data, sizeof(data) / sizeof(int64_t));
  vm.start();
}