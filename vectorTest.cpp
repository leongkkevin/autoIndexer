//
// Created by Kevin Leong on 9/16/20.
//
#include <iostream>

using namespace std;

#include "catch.hpp"

#include "DSVector.h"
#include "DSString.h"

TEST_CASE("Vector Class", "[Vector]"){

    DSVector<int> intVect;
    intVect.push_back(1);
    intVect.push_back(10);
    intVect.push_back(100);

    DSVector<char> charVect;
    charVect.push_back('a');
    charVect.push_back('\n');
    charVect.push_back('$');

    DSVector<DSString> stringVect;
    stringVect.push_back("test");
    stringVect.push_back("test String");
    stringVect.push_back(" ");

    SECTION("Copy Constructor"){
        DSVector<int> copyIntVect = DSVector<int>(intVect);
        REQUIRE(copyIntVect.getSize() == intVect.getSize());
        REQUIRE(copyIntVect.at(0) == intVect.at(0));

        DSVector<char> copyCharVect = DSVector<char>(charVect);
        REQUIRE(copyCharVect.getSize() == charVect.getSize());
        REQUIRE(copyCharVect.at(0) == charVect.at(0));

        DSVector<DSString> copyStringVector = DSVector<DSString>(stringVect);
        REQUIRE(copyStringVector.getSize() == stringVect.getSize());
        REQUIRE(copyStringVector.at(0) == stringVect.at(0));
    }

    SECTION("Insert"){
        intVect.insert(0, 200);
        REQUIRE(intVect.at(0) == 200);

        charVect.insert(1, 'v');
        REQUIRE(charVect.at(1) == 'v');

        stringVect.insert(2, "does it work?");
        REQUIRE(stringVect.at(2) == "does it work?");
    }

};
