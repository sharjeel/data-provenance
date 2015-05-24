# _Adding provenance instrumentation during compilation_ #

Provenance instrumentation (at function call level) can be added automatically to a target application during its compilation using our LLVM-based tools. The LLVM framework [http://llvm.org](LLVM.md) allows compile-time optimization of any program written in a range of source languages, including C, C++, and Java. Using the LLVM toolchain, a program can be converted into an intermediate representation, referred to as _bitcode_. The LLVM optimizer is then used to transform the bitcode, to track the provenance of function calls in the program. Finally, the bitcode is converted into native code and linked to create an executable for the target hardware architecture.

**NOTE:** This tool is very limited. Each file of a program must be instrumented separately. Values of function call arguments are only reported for primitive types.

### Overview ###
  1. Ensure that LLVM is installed. See http://llvm.org/releases/
  1. The target application is converted to bitcode, using a frontend, such as the LLVM C/C++ compiler `clang`.
  1. Our LLVM Tracer module is compiled as a shared library (`llvmTracer.so`).
  1. The LLVM optimizer `opt` is run with the Tracer pass to add provenance instrumentation to the application bitcode.
  1. The LLVM bitcode compiler `llc` is used to convert the instrumented bitcode to assembly.
  1. To connect the output of the Tracer to the SPADE LLVM Reporter, another shared library (`llvmBridge.so`) is compiled to assembly.
  1. The native compiler `gcc` (and implicitly the linker `ld`) is used to compile and link the instrumented application and bridge assembly code into an executable binary that sends provenance metadata to the SPADE kernel.


---


### How to provenance-enable an application ###
  1. Set the `LLVM_PATH` variable in the Makefile to the top-level directory of the LLVM installation.
  1. Set the `LLVM_TARGET` variable in the Makefile to the source file that is to be instrumented. Do not add the file's extension. For example to instrument `/usr/local/src/nweb.c`, set `LLVM_TARGET=/usr/local/src/nweb` .
  1. Build the LLVM Reporter and instrumented application using `make llvm` in the top-level directory of the SPADE installation.
  1. Add the LLVM reporter to the SPADE kernel. (Use `add reporter LLVM` in the SPADE control client).
  1. Run the target application. Function call level provenance will silenty be reported to the SPADE kernel.