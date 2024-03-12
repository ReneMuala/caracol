#include "../src/caracol.hpp"

using namespace caracol;

int main() {
  int32_t end = 100;

  caracol::vm<int32_t, 17> vm;
  /* clang-format off */

  int32_t insn[] = {
      LOAD, 0, 0, 
      LOAD, 1, end, 
      PRINT, 0, 
      INCR, 0, 
     RJLE, 0, 1, -4, 
     HALT,
  };
  /* clang-format on */
  vm.set_pc(2);
  vm.write_block_array(2, insn, sizeof(insn) / sizeof(int32_t));
  vm.start();
}