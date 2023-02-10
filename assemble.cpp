#include <iostream>

void assemble() {
    int result = std::system("nasm -f win64 -o p.obj compiled.asm");
    if (result == 0) {
        std::cout << "Assembly successful!" << std::endl;
    }
    else {
        std::cout << "Assembly failed!" << std::endl;
    }
}