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

int getOnlyNum(DSString specCharWord){
    int returnNum;
    char pageNum[4];

    int j = 0;
    for(int i = 0; i < specCharWord.getLength(); i++){
        if(isdigit(specCharWord.getData()[i])){
            pageNum[j] = specCharWord.getData()[i];
            j++;
        } else {
            if(specCharWord.getData()[i] == '-'){
                return -1;
            }
        }
    }

    returnNum = atoi(pageNum);
    return returnNum;
}

void seperateWords(DSVector<DSString> &pageWords ,DSString pageWordString){
    stringstream ss;
    ss << pageWordString;

    char wordArray[30];
    while(ss.getline(wordArray, 30, ' ')){
        DSString wordString(wordArray);
        pageWords.push_back(wordString);
    }


}

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

        char pageNum[5];
        pageStream.getline(pageNum, 5, '>');

        if(strcmp(pageNum, "-1") != 0){

            DSString pageNumStr(pageNum);
            char entryArr[20];

            while(pageStream.getline(entryArr, 20, ' ')){
                for(char & i : entryArr){
                    i = tolower(i);
                }
                DSString newWord(entryArr);
                if(newWord.getCap() == 1){
                    continue;
                } else{
                    if(entryList.search(newWord) >= 0){
                        entryList.getAt(entryList.search(newWord)).addPage(pageNumStr);
                    } else {
                        WordEntry word(newWord);
                        word.addPage(pageNumStr);
                        entryList.push_back(word);
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

void runIndexer(ifstream &inFile){

    //map<int, DSVector<DSString>> pageAndwords;
    DSList<WordEntry> testList;

    organizeData(inFile, testList);

    set<WordEntry> entrySet;
    sortData(testList, entrySet);


    for(int i = 0; i < testList.getSize(); ++i){
        cout << testList.getAt(i).getWord() << ": ";
        testList.getAt(i).printPages();
        cout << endl;
    }

//    set<WordEntry>::iterator itr;
//    for (itr=testVect.begin(); itr != testVect.end(); ++itr){
//            cout << itr->getWord() << ": ";
//            itr->printPages();
//    }

}

//class autoIndexer {
//}


#endif //INC_20F_AUTO_IDX_AUTOINDEXER_H
