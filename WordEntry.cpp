//
// Created by Kevin Leong on 9/22/20.
//

#include "WordEntry.h"

WordEntry::WordEntry(const WordEntry &copy){
    this->word = copy.word;
    this->pages = copy.pages;
    this->children = copy.children;
}

WordEntry:: WordEntry(const DSString &newWord){
    this->word = newWord;
}

void WordEntry::addChild(const WordEntry childWord){
    this->children.push_back(childWord);
}

void WordEntry::addPage(const DSString pageNumber) {
    this->pages.insert(pageNumber);
}

const DSString &WordEntry::getWord() const {
    return this->word;
}

const set<DSString> &WordEntry::getPages() const {
    return this->pages;
}

DSVector<WordEntry> WordEntry::getChildren() const {
    return this->children;
}

bool WordEntry::operator> (const WordEntry &compEntry) const{
    return strcmp(this->word.getData(), compEntry.getWord().getData()) > 0;
}

bool WordEntry::operator<(const WordEntry &compEntry) const{
    return strcmp(this->word.getData(), compEntry.getWord().getData()) < 0;
}

bool WordEntry::operator==(const WordEntry &compEntry) const{
    bool returnBool = false;
    if(this->word  == compEntry.word){
        returnBool = true;
    }

    return returnBool;
}

ostream &operator<<(ostream &out, const WordEntry &outEntry) {
    int counter = 0;

    out << outEntry.getWord() << ": ";

    counter = outEntry.getWord().getLength() + 2;

    set<DSString>::iterator it;
    for (it = outEntry.getPages().begin(); it != outEntry.getPages().end(); ++it){

        if(counter >= 45){
            out << endl << "    ";
            counter = 3;
        }

        if(next(it) == outEntry.getPages().end()){
            out << *it;
        } else {
            out << *it << ", ";
            counter += it->getLength() + 2;
        }
    }

    if(outEntry.getChildren().getSize() > 0){
        out << endl;
        for(int i = 0; i < outEntry.getChildren().getSize(); ++i){
            out << "    " << outEntry.getChildren().at(i);
        }
    } else{
        out << endl;
    }

    return out;
}


