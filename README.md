# GameCubeResources
Resources on the Nintendo GameCube's Hardware

### Links:
 - Most extensive resource I have found so far: https://www.gc-forever.com/yagcd/index.html
 - Some German wiki that seems to have a bit of info: https://wiki.wiidatabase.de/wiki/Hauptseite
 - Homebrew: https://wiibrew.org/wiki/Libogc
 - IPL decryption algorithm: https://github.com/FIX94/Nintendont/blob/master/loader/source/ipl.c (based on http://msierks.github.io/rustcube/src/rustcube/gamecube.rs.html)

### Base info:
CPU:
  - Customized PowerPC 750CXe core
  - Clockrate – 486 MHz
  - Superscalar Out-of-order execution
  - 4 stages long two-integer ALUs (IU1 and IU2) – 32 bit
  - 7 stages long Floating Point Unit – 64-bit double-precision FPU, usable as 2 × 32-bit SIMD for 1.9 single-precision GFLOPS performance using the Multiply–accumulate operation.   The SIMD is often found under the denomination "paired singles."
  - Branch Prediction Unit (BPU)
  - Load-Store Unit (LSU)
  - System Register Unit (SRU)
  - Memory Management Unit (MMU)
  - Branch Target Instruction Cache (BTIC)
  - SIMD Instructions – PowerPC750 + roughly 50 new SIMD instructions, geared toward 3D graphics
  - Front-side Bus – 64-bit enhanced 60x bus to GPU/chipset at 162 MHz clock with 1.3 GB/s peak bandwidth
  - On-chip Cache – 64 KB 8-way associative L1 cache (32/32 KB instruction/data). 256 KB on-die, 2-way associative L2 cache
  - DMIPS – 1125 (dhrystone 2.1)
  - 180 nm IBM six-layer, copper-wire process. 43 mm² die
  - 1.8 V for logic and I/O. 4.9 W dissipation
  - 27 × 27 mm PBGA package with 256 contacts
  - 6.35 million logic transistors and 18.6 million transistors total
