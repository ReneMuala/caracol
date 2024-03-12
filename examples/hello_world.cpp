#include "../src/caracol.hpp"

using namespace caracol;

int main() {
  caracol::vm<int8_t, 20> vm;

  /* clang-format off */
  int8_t data[] = {
    PRINTS, 0,
    HALT
  };
  /* clang-format on */
  vm.write_mem(0, (char *)"hello world\0", 12);
  vm.set_pc(13);
  vm.write_block_array(13, data, sizeof(data) / sizeof(int8_t));
  vm.start();
}