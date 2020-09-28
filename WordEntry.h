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
    WordEntry(const WordEntry &copy);
    WordEntry(const DSString &newWord);

    void addChild(const WordEntry childWord);

    void addPage(const DSString pageNumber);

    const DSString &getWord() const;

    const set<DSString> &getPages() const;

    DSVector<struct WordEntry> getChildren() const;

    bool operator> (const WordEntry &compEntry) const;

    bool operator<(const WordEntry &compEntry) const;

    bool operator==(const WordEntry &compEntry) const;

    friend ostream &operator<<(ostream &out, const WordEntry &outEntry);
};


#endif //INC_20F_AUTO_IDX_WORDENTRY_H
