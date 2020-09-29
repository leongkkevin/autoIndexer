//
// Created by Kevin Leong on 9/16/20.
//
#include <iostream>

using namespace std;

#include "catch.hpp"

#include "DSVector.h"
#include "DSString.h"

#include <string>

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
        DSVector<int> copyIntVect(intVect);
        REQUIRE(copyIntVect.getSize() == intVect.getSize());
        REQUIRE(copyIntVect.at(0) == intVect.at(0));

        DSVector<char> copyCharVect(charVect);
        REQUIRE(copyCharVect.getSize() == charVect.getSize());
        REQUIRE(copyCharVect.at(0) == charVect.at(0));

        DSVector<DSString> copyStringVector (stringVect);
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

    SECTION("Begin and End"){
        REQUIRE(intVect.begin() == 1);
        REQUIRE(charVect.begin() == 'a');
        REQUIRE(stringVect.begin() == "test");

        REQUIRE(intVect.end() == 100);
        REQUIRE(charVect.end() == '$');
        REQUIRE(stringVect.end() == " ");
    }

    SECTION("Pop Back"){
        intVect.pop_back();
        REQUIRE(intVect.getSize() == 2);
        REQUIRE(intVect.end() == 10);

        charVect.pop_back();
        REQUIRE(charVect.getSize() == 2);
        REQUIRE(charVect.end() == '\n');

        stringVect.pop_back();
        REQUIRE(stringVect.getSize() == 2);
        REQUIRE(stringVect.end() == "test String");
    }

    SECTION("Remove"){
        intVect.remove(1);
        REQUIRE(intVect.at(1) == 100);
        intVect.remove(0);
        REQUIRE(intVect.at(0) == 100);

        charVect.remove(1);
        REQUIRE(charVect.at(1) == '$');
        charVect.remove(0);
        REQUIRE(charVect.at(0) == '$');

        stringVect.remove(1);
        REQUIRE(stringVect.at(1) == " ");
        stringVect.remove(0);
        REQUIRE(stringVect.at(0) == " ");
    }

    SECTION("[] Operator"){
        REQUIRE(intVect[0] == 1);
        REQUIRE(intVect[1] == 10);
        REQUIRE(intVect[2] == 100);

        REQUIRE(charVect[0] == 'a');
        REQUIRE(charVect[1] == '\n');
        REQUIRE(charVect[2] == '$');

        REQUIRE(stringVect[0] == "test");
        REQUIRE(stringVect[1] == "test String");
        REQUIRE(stringVect[2] == " ");
    }
};
