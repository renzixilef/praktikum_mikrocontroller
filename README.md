# Installation
This repository should be usable in any IDE with DevContainer Support. The Dockerfile can also be run as a standalone Container. On Execution the Container automatically builds the project in the `build/` subdirectory. A variety of different binary extensions will be compiled and are ready for use.
If used under Linux it should be possible to flash the binaries directly to the microcontroller from the DevContainer as USB-Drives are mounted and `openocd` is installed. Anyway if this doesn't work (I didn't really test this), the binary can just be pulled to the local machine and flashed from there.