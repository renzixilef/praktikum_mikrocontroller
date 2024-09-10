# Installation
This repository should be usable in any IDE with DevContainer Support. The Dockerfile can also be run as a standalone Container. 
After building of the container the project may be compiled with the following commands:
```console
cmake -B /workspace/build -S /workspace
cmake --build /workspace/build
```
On Execution of those Commands the Container automatically builds the project in the `build/` subdirectory. A variety of different binary extensions will be compiled and are ready for use. In most cases the .elf file should be used as this is memory mapped by default.\
If used under Linux it should be possible to flash the binaries directly to the microcontroller from the DevContainer as USB-Drives are mounted and `openocd` is installed. Anyway if this doesn't work (I didn't really test this), the binary can just be pulled to the local machine and flashed from there.