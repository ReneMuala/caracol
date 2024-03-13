#pragma once

#include <cstring>
#include <iostream>

namespace caracol {
/// @brief Enumeration of instructions supported by the virtual machine
enum Instruction {
  ADD,
  SUB,
  MUL,
  DIV,
  JLT,
  JLE,
  JGE,
  JGT,
  JMP,
  RJLT,
  RJLE,
  RJGE,
  RJGT,
  RJMP,

  MOVE,
  STORE,
  STOREP,
  LOAD,
  PRINT,
  PRINTC,
  PRINTS,

  PUSH,
  PUSHP,
  POP,
  POPP,

  INCR,
  DECR,

  MODE,
  HALT,
};

/**
 * @brief Template class representing a virtual machine
 *
 * @tparam block_type The data type for the memory blocks and instructions
 * @tparam memory_size The size of the memory in terms of the number of
 * `block_type` elements
 * @tparam integer_type The data type for integer operations (default is
 * `block_type`)
 */
template <typename block_type, block_type memory_size,
          typename integer_type = block_type>
class vm {
private:
  block_type memory[memory_size];
  block_type $PC{0}, $SP{0}, SP_LIMIT{0}, MODE{1};

public:
  /**
   * @brief Set the program counter
   *
   * @param pc The new value for the program counter
   */
  inline void set_pc(int pc) { $PC = pc; }

  /**
   * @brief Set the stack pointer
   *
   * @param sp The new value for the stack pointer
   */
  inline void set_sp(int sp) { $SP = sp; }

  /**
   * @brief Verify if there is enough space on the stack for a push operation
   *
   * @param size The size of the data to be pushed (default is
   * `sizeof(block_type)`)
   */
  inline void verify_sp_for_push(const int &size = sizeof(block_type)) {
    if ($SP < SP_LIMIT) {
      std::cerr
          << "[stack overflow]:\n- descr: the process exceed the upper stack "
             "limit, this means that there is no memory available to push (L = "
          << SP_LIMIT << ")\nMachine registers:\n- $PC = " << $PC
          << "\n- $SP = " << $SP << "\n";
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Verify if there is enough data on the stack for a pop operation
   *
   * @param size The size of the data to be popped (default is
   * `sizeof(block_type)`)
   */
  inline void verify_sp_for_pop(const int &size = sizeof(block_type)) {
    if ($SP >= memory_size) {
      std::cerr
          << "[stack underflow]:\n- descr: the process exceed the lower stack "
             "limit (L = "
          << memory_size
          << "), this means that more pops than pushes where "
             "done\nMachine registers:\n- $PC = "
          << $PC << "\n- $SP = " << $SP << "\n";
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Get a pointer to the memory location at the given address
   *
   * @param addr The memory address
   * @return block_type* A pointer to the memory location
   */
  inline constexpr block_type *memory_at(block_type addr) {
    if (addr >= 0 and addr < memory_size) {
      return &memory[addr * MODE];
    } else {
      std::cerr << "[invalid address]:\n- descr: the process tried to access "
                   "an invalid "
                   "memory address "
                << addr << "\nMachine registers:\n- $PC = " << $PC
                << "\n- $SP = " << $SP << "\n";
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Write a block of data to the memory
   *
   * @param index The starting index in the memory
   * @param val The value to be written
   */
  inline void write_block(int index, block_type val) {
    if (index + sizeof(block_type) <= memory_size) {
      if (index + 1 > SP_LIMIT)
        SP_LIMIT = index;
      *memory_at(index) = val;
    } else {
      perror("No enough memory to write_block");
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Write an array of blocks to the memory
   *
   * @param index The starting index in the memory
   * @param data A pointer to the array of blocks
   * @param size The size of the array
   */
  inline void constexpr write_block_array(int index, block_type *data,
                                          int size) {
    if (index + size <= memory_size) {
      if (index + size > SP_LIMIT)
        SP_LIMIT = index + size;
      memcpy(memory + index, data, size * sizeof(block_type));
    } else {
      perror("No enough memory to write");
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Write raw data to the memory
   *
   * @param index The starting index in the memory
   * @param data A pointer to the raw data
   * @param size The size of the data
   */
  inline void constexpr write_mem(int index, void *data, int size) {
    if (index + size <= memory_size) {
      if (index + size > SP_LIMIT)
        SP_LIMIT = index + size;
      memcpy(memory + index, data, size);
    } else {
      perror("No enough memory to write");
      exit(EXIT_FAILURE);
    }
  }

  /**
   * @brief Start executing the instructions in the memory
   */
  inline constexpr void start() {
    constexpr int memblock_size = sizeof(block_type);
    while (true) {
      switch ((Instruction)*memory_at($PC)) {
      case HALT:
        return;
      case ADD:
        *memory_at(*memory_at($PC + 1)) += *memory_at(*memory_at($PC + 2));
        $PC += 3;
        break;
      case SUB:
        *memory_at(*memory_at($PC + 1)) -= *memory_at(*memory_at($PC + 2));
        $PC += 3;
        break;
      case MUL:
        *memory_at(*memory_at($PC + 1)) *= *memory_at(*memory_at($PC + 2));
        $PC += 3;
        break;
      case DIV:
        *memory_at(*memory_at($PC + 1)) /= *memory_at(*memory_at($PC + 2));
        $PC += 3;
        break;
      case MOVE:
        *memory_at(*memory_at($PC + 1)) = *memory_at(*memory_at($PC + 2));
        $PC += 3;
        break;
      case STORE:
        *memory_at(*memory_at(*memory_at($PC + 1))) =
            *memory_at(*memory_at($PC + 2));
        $PC += 3;
        break;
      case STOREP:
        *memory_at(*memory_at(*memory_at($PC + 1))) =
            *memory_at(*memory_at(*memory_at($PC + 2)));
        $PC += 3;
        break;
      case LOAD:
        *memory_at(*memory_at($PC + 1)) = *memory_at($PC + 2);
        $PC += 3;
        break;
      case PRINT:
        std::cout << "[" << int(*memory_at($PC + 1)) << "] "
                  << (int)*memory_at(*memory_at($PC + 1)) << std::endl;
        $PC += 2;
        break;
      case JLT:
        if (*memory_at(*memory_at($PC + 1)) < *memory_at(*memory_at($PC + 2)))
          $PC = (block_type)*memory_at($PC + 3);
        else
          $PC += 4;
        break;
      case JLE:
        if (*memory_at(*memory_at($PC + 1)) <= *memory_at(*memory_at($PC + 2)))
          $PC = (block_type)*memory_at($PC + 3);
        else
          $PC += 4;
        break;
      case JGE:
        if (*memory_at(*memory_at($PC + 1)) >= *memory_at(*memory_at($PC + 2)))
          $PC = (block_type)*memory_at($PC + 3);
        else
          $PC += 4;
        break;
      case JGT:
        if (*memory_at(*memory_at($PC + 1)) > *memory_at(*memory_at($PC + 2)))
          $PC = (block_type)*memory_at($PC + 3);
        else
          $PC += 4;
        break;
      case JMP:
        $PC = (block_type)*memory_at($PC + 3);
        break;
      case RJLT:
        if (*memory_at(*memory_at($PC + 1)) < *memory_at(*memory_at($PC + 2)))
          $PC += (block_type)*memory_at($PC + 3);
        else
          $PC += 4;
        break;
      case RJLE:
        if (*memory_at(*memory_at($PC + 1)) <= *memory_at(*memory_at($PC + 2)))
          $PC += (block_type)*memory_at($PC + 3);
        else
          $PC += 4;
        break;
      case RJGE:
        if (*memory_at(*memory_at($PC + 1)) >= *memory_at(*memory_at($PC + 2)))
          $PC += (block_type)*memory_at($PC + 3);
        else
          $PC += 4;
        break;
      case RJGT:
        if (*memory_at(*memory_at($PC + 1)) > *memory_at(*memory_at($PC + 2)))
          $PC += (block_type)*memory_at($PC + 3);
        else
          $PC += 4;
        break;
      case RJMP:
        $PC += (block_type)*memory_at($PC + 3);
        break;
      case PRINTS:
        std::cout << "[" << int(*memory_at($PC + 1)) << "] "
                  << ((block_type *)&*memory_at(*memory_at($PC + 1)))
                  << std::endl;
        $PC += 2;
        break;
      case PRINTC:
        std::cout << "[" << int(*memory_at($PC + 1)) << "] "
                  << (*(block_type *)&*memory_at(*memory_at($PC + 1)))
                  << std::endl;
        $PC += 2;
        break;
      case INCR:
        *memory_at(*memory_at($PC + 1)) += 1;
        $PC += 2;
        break;
      case DECR:
        *memory_at(*memory_at($PC + 1)) -= 1;
        $PC += 2;
        break;
      case PUSH:
        verify_sp_for_push();
        *memory_at($SP) = *memory_at(*memory_at($PC + 1));
        $SP -= memblock_size;
        $PC += 2;
        break;
      case PUSHP:
        verify_sp_for_push();
        *memory_at($SP) = *memory_at(*memory_at(*memory_at($PC + 1)));
        $SP -= memblock_size;
        $PC += 2;
        break;
      case POP:
        verify_sp_for_pop();
        $SP += memblock_size;
        *memory_at(*memory_at($PC + 1)) = *memory_at($SP);
        $PC += 2;
        break;
      case POPP:
        verify_sp_for_pop();
        $SP += memblock_size;
        *memory_at(*memory_at(*memory_at($PC + 1))) = *memory_at($SP);
        $PC += 2;
        break;
      case Instruction::MODE:
        this->MODE = *memory_at($PC + 1);
        $PC += 2;
        break;
      default:
        std::cerr << "[illegal instruction at: " << $PC << " ]" << std::endl;
        return;
      }
    }
  }
};

} // namespace caracol
