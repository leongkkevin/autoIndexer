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

//void removeTrailPunc(char * charArr){
//    char temp[40];
//    for (int i = 39; i >= 0; --i) {
//        if(!isalpha(charArr[i])){
//            temp[i] = '0';
//        } else {
//            temp[i] = charArr[i];
//        }
//    }
//
//    for(int i = 0; i < 39; ++i){
//        if(temp[i] == '0'){
//            break;
//        } else {
//            charArr[i] = temp[i];
//        }
//    }
//}

void organizeData(ifstream &inFile,
                  DSList<WordEntry> &entryList){

    DSString bigString;
    while(!inFile.eof()){
        char inputChar[80];
        inFile.getline(inputChar, 160, '\n');
        DSString pageNumString(inputChar);
        bigString = bigString + pageNumString;
        bigString = bigString + " ";
    }

    stringstream ss;
    ss << bigString;

    char inputChar[80];
    while(ss.getline(inputChar, 80, '<')){
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

                //check parent
                bool isParent = false;
                if(entryArr[0] == '('){
                    removeFirstChar(entryArr);

                    charArrLower(entryArr);
                    newWord = entryArr;
                    newWord = newWord.substring(0, newWord.getLength() - 1);

                    isParent = true;
                } else

                //For phrases
                if(entryArr[0] == '[') {
                    char restChar[40];
                    pageStream.getline(restChar, 40, ']');

                    removeFirstChar(entryArr);

                    charArrLower(entryArr);
                    charArrLower(restChar);

                    DSString entryOne(entryArr);
                    DSString entryTwo(restChar);
                    newWord = entryOne + " ";
                    newWord = newWord + entryTwo;
                }else{
                    charArrLower(entryArr);
                    newWord = entryArr;
                }

                if(newWord.getCap() == 1){
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
        if(entrySet.count(testVect.getAt(i))){
        }
        entrySet.insert(testVect.getAt(i));
    }
}

void printIndex(set<WordEntry> &entrySet){
    set<WordEntry>::iterator itr;
    for(itr = entrySet.begin(); itr != entrySet.end(); ++itr){
        cout << *itr << endl;
    }
}

void runIndexer(ifstream &inFile){

    //map<int, DSVector<DSString>> pageAndwords;
    DSList<WordEntry> testList;

    organizeData(inFile, testList);

    set<WordEntry> entrySet;
    sortData(testList, entrySet);

    printIndex(entrySet);

}

//class autoIndexer {
//}


#endif //INC_20F_AUTO_IDX_AUTOINDEXER_H
