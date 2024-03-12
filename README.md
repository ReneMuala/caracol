![Snail](images/caracol.jpeg)

# Caracol

A lightweight and flexible template library for creating purpose-specific virtual machines.

## Use Cases

- Platform emulation
- Cryptography
- Low-level programming
- Sandboxed execution environments
- Domain-specific language interpreters

## Why Caracol?

Caracol is designed to be simple to use and develop, while maintaining a robust structure. The machine runtime is memory-safe, and it will terminate the program if any unsafe operation is performed internally.

Key features:

- **Lightweight**: Caracol has a small footprint and minimal dependencies, making it suitable for embedded systems and resource-constrained environments.
- **Flexible**: With its template-based design, Caracol allows you to customize the virtual machine's architecture, instruction set, and memory layout to suit your specific needs.
- **Sandboxed**: Caracol provides a secure execution environment, isolating the guest code from the host system and preventing unauthorized access or modification.
- **Extensible**: Easily add custom instructions, opcodes, and functionality by inheriting from the base classes and overriding the necessary methods.

## Getting Started

To get started with Caracol, follow these steps:

1. Clone the repository: `git clone https://github.com/renemuala/caracol.git`
2. Include the `caracol.hpp` header file in your C++ project.
3. Create a new instance of the `caracol::vm` template class, specifying the desired instruction and memory sizes.
4. Write your custom instructions or opcodes, and load them into the virtual machine's memory.
5. Execute the virtual machine and observe the results.

## Example: Hello World

```cpp
#include "caracol.hpp"

using namespace caracol;

int main() {
    // Create a virtual machine with 8-bit instructions and 20 bytes of memory
    caracol::vm<int8_t, 20> vm;

    // Define the program instructions
    int8_t code[] = {
        PRINT_S, 0,  // Print the string at memory address 0
        HALT         // Terminate the program
    };

    // Write the "hello world" string to memory
    vm.write_mem(0, (char*)"hello world\0", 12);

    // Load the program instructions into memory
    vm.write_block_array(13, code, sizeof(code) / sizeof(int8_t));

    // Set the program counter to the start of the instructions
    vm.set_pc(13);

    // Start executing the virtual machine
    vm.start();

    return 0;
}
```

This example demonstrates how to create a simple virtual machine, load a program that prints "hello world", and execute it using Caracol.

## Contributing

Contributions to Caracol are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request on the project's GitHub repository.

## License

Caracol is released under the [MIT License](LICENSE).