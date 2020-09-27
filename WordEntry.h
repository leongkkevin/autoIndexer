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
//    DSVector<WordEntry> children;

public:

    WordEntry()= default;
    ~WordEntry()= default;

    WordEntry(const WordEntry &copy){
        this->word = copy.word;
        this->pages = copy.pages;
//        this->children = copy.children;
    }
    WordEntry(const DSString &newWord){
        this->word = newWord;
    }

    void addChild(WordEntry childWord){
//        this->children.push_back(childWord);
    }
    void addPage(const DSString &pageNumber) {
        this->pages.insert(pageNumber);
    }

    DSString getWord() const {
        return this->word;
    }

    set<DSString> getPages() const {
        return this->pages;
    }

    void printPages() const {
        for (auto it=this->pages.begin(); it != this->pages.end(); ++it){
            if(next(it) == this->pages.end()){
                cout << *it;
            } else {
                cout << *it << ", ";
            }
        }
    }
    void print(){
        cout << this->word << ": ";
        //set<DSString>::iterator itr;

        for (auto it=this->pages.begin(); it != this->pages.end(); ++it){
            cout << ' ' << *it;
            cout << endl;
        }
    }

    bool operator>(WordEntry &compEntry) const{
        return strcmp(this->word.getData(), compEntry.getWord().getData()) > 0;
    }

    bool operator<(const WordEntry &compEntry) const{
        return strcmp(this->word.getData(), compEntry.getWord().getData()) < 0;
    }

    bool operator==(const WordEntry &compEntry) const{
        bool returnBool = false;
        if(this->word  == compEntry.word){
            returnBool = true;
        }

        return returnBool;
    }
};


#endif //INC_20F_AUTO_IDX_WORDENTRY_H
