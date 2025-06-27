# 🛠️ Assembler and Emulator in C++

> A complete implementation of an **Assembler and Emulator** for a custom instruction set architecture (ISA), built in **C++**.  
> Developed by **Venkata Bhuvan Kosuru (Roll No: 2301AI33)**.

---

## 📄 Description

This project simulates a low-level computing environment:
- The **Assembler** converts human-readable assembly code (`.asm`) into machine code (`.o`).
- The **Emulator** executes that machine code using a custom CPU simulation.

This tool is perfect for learning about:
- CPU instructions and registers  
- Stack and memory access  
- Error-checking in compilers  
- Binary-level program execution  

---

## 📁 Project Structure

/project
│
├── assembler.cpp # Assembler source code

├── emulator.cpp # Emulator source code

├── sample.asm # Sample assembly file (create your own)

├── *.log # Log file with errors/warnings

├── *.lst # Listing file with addresses and hex code

├── *.o # Binary machine code (output from assembler)

└── README.md

---

## ⚙️ Features

### ✅ Assembler
- Translates `.asm` files to:
  - `.log` file (error/warning messages)
  - `.lst` file (detailed listing with addresses)
  - `.o` file (machine code for emulator)
- Handles:
  - Labels and symbol/literal tables
  - Mnemonic classification (0, 1, and 2 operand types)
  - Error handling (unused/repeated labels, wrong formats)
  - Support for `data`, `SET`, and numeric literals

### 🖥️ Emulator
- Reads `.o` file and executes it
- Supports CLI flags:
  - `-trace`   → Step-by-step trace
  - `-read`    → Log memory read operations
  - `-write`   → Log memory write operations
  - `-before`  → Display memory before execution
  - `-after`   → Display memory after execution
  - `-wipe`    → Reset registers
  - `-isa`     → Show supported instruction set

---

## 🔢 Instruction Set Architecture (ISA)

| Opcode | Mnemonic | Operand Type |
|--------|----------|---------------|
| 00     | ldc      | value         |
| 01     | adc      | value         |
| 02     | ldl      | offset        |
| 03     | stl      | offset        |
| 04     | ldnl     | offset        |
| 05     | stnl     | offset        |
| 06     | add      | none          |
| 07     | sub      | none          |
| 08     | shl      | none          |
| 09     | shr      | none          |
| 0A     | adj      | value         |
| 0B     | a2sp     | none          |
| 0C     | sp2a     | none          |
| 0D     | call     | offset        |
| 0E     | return   | none          |
| 0F     | brz      | offset        |
| 10     | brlz     | offset        |
| 11     | br       | offset        |
| 12     | HALT     | none          |


---

## 🛠️ Build Instructions

### Compile Assembler
```bash
g++ -o asm assembler.cpp




