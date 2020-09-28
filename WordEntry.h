//
// Created by Kevin Leong on 9/22/20.
//


#ifndef INC_20F_AUTO_IDX_WORDENTRY_H
#define INC_20F_AUTO_IDX_WORDENTRY_H

#include "DSString.h"
#include "DSVector.h"
#include <set>

class WordEntry {
private:
    DSString word;
    set<DSString> pages;
    DSVector<WordEntry> children;

public:

    WordEntry()= default;
    ~WordEntry() = default;

    WordEntry(const WordEntry &copy){
        this->word = copy.word;
        this->pages = copy.pages;
//        for(int  i = 0; i < this->children.getSize(); ++i){
//            this->children.at(i)  = copy.children.at(i);
//        }

    }
    WordEntry(const DSString &newWord){
        this->word = newWord;
    }

    void addChild(const WordEntry childWord){
        this->children.push_back(childWord);
    }

    void addPage(const DSString pageNumber) {
        this->pages.insert(pageNumber);
    }

    const DSString &getWord() const {
        return this->word;
    }

    const set<DSString> &getPages() const {
        return this->pages;
    }

    const DSVector<WordEntry> getChildren() const {
        return this->children;
    }

    bool operator> (const WordEntry &compEntry) const{
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

    friend ostream &operator<<(ostream &out, const WordEntry &outEntry) {
        out << outEntry.getWord() << ": ";

        set<DSString>::iterator it;
        for (it = outEntry.getPages().begin(); it != outEntry.getPages().end(); ++it){
            if(next(it) == outEntry.getPages().end()){
                out << *it;
            } else {
                out << *it << ", ";
            }
        }

        if(outEntry.getChildren().getSize() > 0){
            out << endl;
            for(int i = 0; i < outEntry.getChildren().getSize(); ++i){
                out << "    " << outEntry.getChildren().at(i) << endl;
            }
        }

        return out;
    }
};


#endif //INC_20F_AUTO_IDX_WORDENTRY_H
