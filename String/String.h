#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <vector>

using std::istream; using std::ostream;

class String {
public:
    //constructor
    String():length(0),p_str(nullptr) {}
    String(String const&);
    String(char const*);
    String(const int, const char);

    //destructor
    ~String() { delete[]p_str; }

    //friend funs

    //read writer operations
    friend ostream& operator<<(ostream&, String const&);
    friend istream& operator>>(istream&, String&);

    //add operation
    friend String operator+(String const&, String const&);

    //compare operations
    friend inline bool operator==(String const&, String const&);
    friend inline bool operator!=(String const&, String const&);
    friend inline bool operator>(String const&, String const&);
    friend inline bool operator<(String const&, String const&);
    friend inline bool operator>=(String const&, String const&);
    friend inline bool operator<=(String const&, String const&);

    //index operation
    char& operator[](const int);
    char const& operator[](const int)const;

    //assignment operation
    String operator=(const String&);
    String operator+=(const String&);

    //成员操作函数
    int Length() const{ return length; }
    String subString(int, int);
    String& insert(int, String const&);
    String& assign(String const&,int,int);
    String& erase(int, int);
    String& append(String const&);
    int find(String const&);
private:
    int length;
    char* p_str;

    void get_nextval(String, int*);
};

#endif
