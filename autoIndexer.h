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
        map<int, DSVector<DSString>> &pageAndwords){

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

    DSVector<WordEntry> testVect;

    char inputChar[80];
    while(ss.getline(inputChar, 80, '<')){
        stringstream pageStream;
        pageStream << inputChar;

        char pageNum[5];
        pageStream.getline(pageNum, 5, '>');
        DSString pageNumStr(pageNum);

        char entryArr[20];
        while(pageStream.getline(entryArr, 20, ' ')){
            DSString newWord(entryArr);
            WordEntry word(newWord);
            word.addPage(pageNumStr);
            word.print();
            testVect.push_back(word);
        }
    }

}

void runIndexer(ifstream &inFile){

    map<int, DSVector<DSString>> pageAndwords;

    organizeData(inFile, pageAndwords);

}

//class autoIndexer {
//}


#endif //INC_20F_AUTO_IDX_AUTOINDEXER_H
