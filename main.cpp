#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
    std::ofstream outputstream(argv[2]);
    outputstream << "Hello, World!" << std::endl;
    outputstream.close();
    std::cout << "Hello and wrote sample output file." << std::endl;
    return 0;
}
