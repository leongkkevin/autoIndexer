//
// Created by Kevin Leong on 9/18/20.
//

#include <iostream>
#include <fstream>
#include <map>

#include "DSVector.h"
#include "DSString.h"
#include "DSList.h"

#include "WordEntry.h"

#ifndef INC_20F_AUTO_IDX_AUTOINDEXER_H
#define INC_20F_AUTO_IDX_AUTOINDEXER_H

//function takes in a character array and
void charArrLower(char *charArr){
    for(int i = 0; i < 40; ++i){
        charArr[i] = tolower(charArr[i]);
    }
}

void removeFirstChar(char *charArr){
    for (int i = 0; i < 39; ++i) {
        charArr[i] = charArr[i + 1];
    }
}

void organizeData(ifstream &inFile,
                  DSList<WordEntry> &entryList){

    DSString bigString;
    while(!inFile.eof()){
        char inputChar[100];
        inFile.getline(inputChar, 160, '\n');
        DSString pageString(inputChar);

        if(pageString.hasAt('(') >= 0){
            DSString ifParentString;
            ifParentString = pageString.substring(pageString.hasAt('('),
                    pageString.getLength());

            pageString = pageString.substring(0, pageString.hasAt('('))
                    + " ";
            pageString = pageString + ifParentString;
        }

        bigString = bigString + pageString;
        bigString = bigString + " ";
    }

    stringstream ss;
    ss << bigString;

    char inputChar[200];
    while(ss.getline(inputChar, 200, '<')){
        stringstream pageStream;
        pageStream << inputChar;

        WordEntry *lastEntry = nullptr;

        char pageNum[10];
        pageStream.getline(pageNum, 10, '>');

        if(strcmp(pageNum, "-1") != 0){
            DSString pageNumStr(pageNum);

            char entryArr[40];
            while(pageStream.getline(entryArr, 40, ' ')){
                DSString newWord;
                bool isParent = false;
                bool isPhrase = false;

                //For phrases
                if(entryArr[0] =='[' || entryArr[1] == '[') {
                    isPhrase = true;
                    char restChar[40];
                    if (entryArr[0] == '[') {
                        pageStream.getline(restChar, 40, ']');
                        removeFirstChar(entryArr);
                    } else if (entryArr[1] == '[') {
                        pageStream.getline(restChar, 40, ']');
                        removeFirstChar(entryArr);
                        entryArr[0] = '(';
                    }

                    charArrLower(entryArr);
                    charArrLower(restChar);

                    DSString entryOne(entryArr);
                    DSString entryTwo(restChar);
                    newWord = entryOne + " ";
                    newWord = newWord + entryTwo;
                }

                //check parent
                if(entryArr[0] == '('){
                    if(!isPhrase){
                        charArrLower(entryArr);
                        newWord = entryArr;
                        newWord = newWord.substring(1, newWord.getLength() - 2);
                    } else {
                        newWord = newWord.substring(1, newWord.getLength() - 2);
                    }
                    isParent = true;
                }

                //for standard words
                if(!isParent && !isPhrase){
                    charArrLower(entryArr);
                    newWord = entryArr;
                }

                if(newWord.getCap() <= 1){
                    continue;
                } else{
                    if(entryList.search(newWord) >= 0){
                        entryList.getAt(entryList.search(newWord)).addPage(pageNumStr);
                        if(isParent){
                            entryList.getAt(entryList.search(newWord)).addChild(*lastEntry);
                        }
                        lastEntry = &entryList.getAt(entryList.search(newWord));
                    } else {
                        WordEntry word(newWord);
                        word.addPage(pageNumStr);
                        entryList.push_back(word);
                        if(isParent){
                            entryList.getAt(entryList.search(newWord)).addChild(*lastEntry);
                        }
                        lastEntry = &entryList.getAt(entryList.getSize() - 1);
                    }
                }
            }
        }
    }
}

void sortData(DSList<WordEntry> &testVect, set<WordEntry> &entrySet){
    for(int i = 0; i < testVect.getSize(); ++i){
        entrySet.insert(testVect.getAt(i));
    }

    entrySet.erase(entrySet.begin());
}

void printHeader(const WordEntry& word, char &currChar, ofstream &outFile){
    if(word.getWord().getData()[0] != currChar){
        currChar = word.getWord().getData()[0];
        char upperChar = toupper(currChar);
        outFile << "[" << upperChar << "]" << endl;
    }
}

void printIndex(const set<WordEntry> &entrySet, ofstream &outFile){
    set<WordEntry>::iterator itr;
    char currChar = '!';
    for(itr = entrySet.begin(); itr != entrySet.end(); ++itr){
        printHeader(*itr, currChar, outFile);
        outFile << *itr;
    }
}

void runIndexer(ifstream &inFile, ofstream &outFile){

    DSList<WordEntry> testList;

    organizeData(inFile, testList);

    set<WordEntry> entrySet;
    sortData(testList, entrySet);

    printIndex(entrySet, outFile);

}

//class autoIndexer {
//}


#endif //INC_20F_AUTO_IDX_AUTOINDEXER_H
