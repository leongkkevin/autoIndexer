//
// Created by Kevin Leong on 9/22/20.
//

#include "DSString.h"
#include "DSVector.h"
#include <set>

using namespace std;

#ifndef INC_20F_AUTO_IDX_WORDENTRY_H
#define INC_20F_AUTO_IDX_WORDENTRY_H

class WordEntry {
private:
    DSString word;
    set<DSString> pages;
    DSVector<WordEntry> children;

public:

    WordEntry()= default;
    ~WordEntry()= default;

    WordEntry(const WordEntry &copy){
        this->word = copy.word;
        this->pages = copy.pages;
    }
    WordEntry(DSString newWord){
        this->word = newWord;
    }

    void addChild(WordEntry childWord){
        this->children.push_back(childWord);
    }
    void addPage(DSString pageNumber){
        pages.insert(pageNumber);
    }

    DSString getWord(){
        return this->word;
    }

    set<DSString> getPages(){
        return this->pages;
    }
};


#endif //INC_20F_AUTO_IDX_WORDENTRY_H
