//
// Created by Kevin Leong on 9/16/20.
//

#ifndef INC_20F_AUTO_IDX_DSSTRING_H
#define INC_20F_AUTO_IDX_DSSTRING_H


#include <iostream>
#include <cstring>

class DSString{

private:

    int size;
    int capacity;
    char* data;



public:
    DSString();
    DSString(const char*);
    DSString(const DSString&);
    ~DSString();

    DSString& operator= (const char*);
    DSString& operator= (const DSString&);
    DSString operator+ (const DSString&);
    bool operator== (const char*) const;
    bool operator== (const DSString&) const;
    bool operator> (const DSString&)  const;
    bool operator< (const DSString&)  const;
    char& operator[] (const int);
    friend std::ostream& operator<< (std::ostream&, const DSString&);

    void resize(int newLength);
    int createLength(const char *newData);

    int getLength() const;
    int getCap();
    char * getData() const;

    void append(char addData);
    DSString substring(int start, int numChars);
    char* c_str();

    int hasAt(char checkChar, int start);
};


#endif //INC_20F_AUTO_IDX_DSSTRING_H
