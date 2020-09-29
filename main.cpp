//For edit config (no tests): ../input01.txt

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "autoIndexer.h"

#include <string>

using namespace std;

int runCatchTest(int argc, char* const argv[]){
    return Catch::Session().run(argc, argv);
}

int main(int argc, char** argv) {

    if(argc == 1){
        return runCatchTest(argc, argv);
    }

    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);

    runIndexer(inFile, outFile);


        return 0;
}
