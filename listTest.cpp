//
// Created by Kevin Leong on 9/16/20.
//

#include "DSVector.h"

#include "DSString.h"

#include "catch.hpp"
#include "DSList.h"

TEST_CASE("Linked List Class", "[LinkedList]"){
    DSList<int> intList;
    intList.push_back(1);
    intList.push_back(10);
    intList.push_back(100);

    DSList<char> charList;
    charList.push_back('a');
    charList.push_back('\n');
    charList.push_back(' ');

    DSList<DSString> stringList;
    stringList.push_back("test String");
    stringList.push_back("test");
    stringList.push_back(" ");

    SECTION("Copy Constructor"){
        DSList<int> intCopyList = DSList<int> (intList);
        REQUIRE(intCopyList.getSize() == intList.getSize());
        REQUIRE(intCopyList.getAt(0) == intList.getAt(0));

        DSList<char> charCopyList = DSList<char> (charList);
        REQUIRE(charCopyList.getSize() == charList.getSize());
        REQUIRE(charCopyList.getAt(1) == charList.getAt(1));

        DSList<DSString> stringCopyList = DSList<DSString> (stringList);
        REQUIRE(stringCopyList.getSize() == stringList.getSize());
        REQUIRE(stringCopyList.getAt(2) == stringList.getAt(2));
    }

    SECTION("Push_back"){
        intList.push_back(2);
        REQUIRE(intList.getAt(0) == 1);
        REQUIRE(intList.getAt(3) == 2);
        REQUIRE(intList.getSize() == 4);

        charList.push_back('b');
        REQUIRE(charList.getAt(0) == 'a');
        REQUIRE(charList.getAt(3) == 'b');
        REQUIRE(charList.getSize() == 4);

        stringList.push_back("a test sentence");
        REQUIRE(stringList.getAt(0) == "test String");
        REQUIRE(stringList.getAt(3) == "a test sentence");
        REQUIRE(stringList.getSize() == 4);
    }

    SECTION("Remove"){
        intList.remove(1);
        REQUIRE(intList.getSize() == 2);
        REQUIRE(intList.getAt(0) == 10);

        charList.remove('a');
        REQUIRE(charList.getSize() == 2);
        REQUIRE(charList.getAt(0) == '\n');

        stringList.remove("test String");
        REQUIRE(stringList.getSize() == 2);
        REQUIRE(stringList.getAt(0) == "test");
    }

    SECTION("Remove At"){
        intList.removeAt(1);
        REQUIRE(intList.getSize() == 2);
        REQUIRE(intList.getAt(1) == 100);

        charList.removeAt(0);
        REQUIRE(charList.getSize() == 2);
        REQUIRE(charList.getAt(0) == '\n');

        stringList.removeAt(3);
        REQUIRE(stringList.getSize() == 2);
        REQUIRE(stringList.getAt(stringList.getSize() - 1) == "test");
    }

    SECTION("Pop"){
        REQUIRE(intList.pop() == 1);
        REQUIRE(intList.getSize() == 2);
        REQUIRE(intList.getAt(0) == 10);

        REQUIRE(charList.pop() == 'a');
        REQUIRE(charList.getSize() == 2);
        REQUIRE(charList.getAt(0) == '\n');

        REQUIRE(stringList.pop() == "test String");
        REQUIRE(stringList.getSize() == 2);
        REQUIRE(stringList.getAt(0) == "test");
    }

    SECTION("Search"){
        REQUIRE(intList.search(1) == 0);
        REQUIRE(intList.search(10) == 1);
        REQUIRE(intList.search(100) == 2);

        REQUIRE(charList.search('a') == 0);
        REQUIRE(charList.search('\n') == 1);
        REQUIRE(charList.search(' ') == 2);

        REQUIRE(stringList.search("test String") == 0);
        REQUIRE(stringList.search("test") == 1);
        REQUIRE(stringList.search(" ") == 2);
    }


}