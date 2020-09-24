//For edit config (no tests): ../input01.txt

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "autoIndexer.h"

#include <string>

using namespace std;

#define TEST true
int runCatchTest(int argc, char* const argv[]){
    return Catch::Session().run(argc, argv);
}


int main(int argc, char** argv) {

    if(TEST){
        return runCatchTest(argc, argv);
    }

    ifstream inFile(argv[1]);
    runIndexer(inFile);

//    std::ofstream outputstream(argv[2]);
//    outputstream << "Hello, World!" << std::endl;
//    outputstream.close();

    return 0;
}
