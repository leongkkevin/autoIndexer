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

//function removes the first character of a character array
void removeFirstChar(char *charArr){
    for (int i = 0; i < 39; ++i) {
        charArr[i] = charArr[i + 1];
    }
}

//removes trailing punctuation
DSString removeTrailingPunct(DSString &newWord){
    int count = 0;
    for(int i = newWord.getLength(); i > 0; --i){
        if(ispunct(newWord.getData()[i - 1])){
            count++;
        } else{
            break;
        }
    }

    if(count > 0) {
        int index = newWord.getLength() - count;
        newWord = newWord.substring(0, index);
    }

    return newWord;

}

//organizes the data into a linked list
void organizeData(ifstream &inFile,
                  DSList<WordEntry> &entryList){

    //this portion creates a large string to parse through
    DSString bigString;
    while(!inFile.eof()){
        char inputChar[100];
        inFile.getline(inputChar, 160, '\n');
        DSString pageString(inputChar);

        //modifies the input for parent texts
        //specifically inserts a space between the child and parent words/phrases
        if(pageString.hasAt('(', 0) >= 0){
            int start = 1;
            while(pageString.hasAt('(', start) >= 0) {
                DSString ifParentString;
                ifParentString = pageString.substring(pageString.hasAt('(', start),
                                                      pageString.getLength());

                pageString = pageString.substring(0, pageString.hasAt('(', start))
                             + " ";
                pageString = pageString + ifParentString;

                start += pageString.hasAt('(', start);
            }
        }

            //creates a large string of a certain page's words and phrases
            bigString = bigString + pageString;
            bigString = bigString + " ";
    }

    cout << bigString << endl;

    stringstream ss;
    ss << bigString;

    //loops sorts the large string by page
    char inputChar[200];
    while(ss.getline(inputChar, 200, '<')){
        stringstream pageStream;
        pageStream << inputChar;

        //this pointer points to the last entry put into the List
        //for parent/child usage
        WordEntry *lastEntry = nullptr;

        //this  section sets the page number
        char pageNum[10];
        pageStream.getline(pageNum, 10, '>');

        //if statement stops the loop when a <-1> is read
        if(strcmp(pageNum, "-1") != 0){
            DSString pageNumStr(pageNum);

            //parse in each word by space
            char entryArr[40];
            while(pageStream.getline(entryArr, 40, ' ')){
                DSString newWord;
                bool isParent = false;
                bool isPhrase = false;

                //For phrases
                //Keeps the phrase together during the sorting process
                if(entryArr[0] =='[' || entryArr[1] == '[') {
                    isPhrase = true;
                    char restChar[40];

                    //finds the entry (which is seperated) and combines it
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

                    //combining the phrase back together
                    DSString entryOne(entryArr);
                    DSString entryTwo(restChar);
                    newWord = entryOne + " ";
                    newWord = newWord + entryTwo;
                }

                //checks to see if the word is a parent
                if(entryArr[0] == '('){
                    if(!isPhrase){
                        charArrLower(entryArr);
                        newWord = entryArr;
                        newWord = newWord.substring(1, newWord.getLength() - 1);
                    } else {
                        newWord = newWord.substring(1, newWord.getLength() - 1);
                    }
                    isParent = true;
                }

                //for standard words (not a phrase or parent)
                if(!isParent && !isPhrase){
                    charArrLower(entryArr);
                    newWord = entryArr;
                }

                //removes any trailing punctuation
                removeTrailingPunct(newWord);

                //this if statement skips any inputs that are blank or made of punctuation
                if(newWord.getCap() <= 1){
                    continue;
                } else{
                    //this searches through the list and adds the word if its found
                    if(entryList.search(newWord) >= 0){
                        entryList.getAt(entryList.search(newWord)).addPage(pageNumStr);
                        if(isParent){
                            entryList.getAt(entryList.search(newWord)).addChild(*lastEntry);
                        }
                        lastEntry = &entryList.getAt(entryList.search(newWord));

                        //if it is not found, it is added
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

//adds the data into a set to organize it
void sortData(DSList<WordEntry> &testVect, set<WordEntry> &entrySet){
    for(int i = 0; i < testVect.getSize(); ++i){
        entrySet.insert(testVect.getAt(i));
    }
}

//checks for the first letter of each word
//prints the first letter if changed
void printHeader(const WordEntry& word, char &currChar, ofstream &outFile){
    if(word.getWord().getData()[0] != currChar){
        currChar = word.getWord().getData()[0];
        char upperChar = toupper(currChar);
        outFile << "[" << upperChar << "]" << endl;
    }
}

//prints the index
void printIndex(const set<WordEntry> &entrySet, ofstream &outFile){
    set<WordEntry>::iterator itr;
    char currChar = '!';
    for(itr = entrySet.begin(); itr != entrySet.end(); ++itr){
        printHeader(*itr, currChar, outFile);
        outFile << *itr;
    }
}

//runs the program
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
