#include "../src/caracol.hpp"

using namespace caracol;

int main() {
  caracol::vm<int8_t, 64> vm;

  /* clang-format off */
  int8_t data[] = {
     LOAD,   3, 4 + 11, // LIMIT
     LOAD,   0, 1,      
     LOAD,   2, 4,
     STOREP, 0, 2,  
    PRINTC, 1, 
    INCR, 2, 
    RJLT, 2, 3, -7,
    PRINTS, 4,
    HALT
  };
  /* clang-format on */

  int index = 4;
  vm.write_mem(index, (char *)"hello world\0", 12);
  index += 13;
  vm.set_pc(index);
  vm.set_sp(63);
  vm.write_block_array(index, data, sizeof(data) / sizeof(int8_t));
  vm.start();
}