# How to compile this software
- clone this repository
- checkout the submodules using command `git submodule update --depth 1 --init --recursive` (don't use `--depth 1` if you want to clone the whole history)
- configure cmake through your ide or using the following commands:
    ```shell
    mkdir build
    cd build 
    cmake -S .. -B .
    ```
- build the project using your ide or using the following commands:
    ```shell
    cmake --build .
    ```
The binary `example_lwip_linux_unix` will now be in the `build/example_lwip_linux_unix` folder