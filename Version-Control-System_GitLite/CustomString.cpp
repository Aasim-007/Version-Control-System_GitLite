#include <iostream>
#include <fstream>
#include "CustomString.h"
using namespace std;

CustomString::CustomString() {}

CustomString::CustomString(int s)
{
    size = s;
    data = new char[size + 1] {'\0'};
}

CustomString::CustomString(const string s)
{
    size = s.size();
    if (data != NULL)
        delete data;
    data = new char[size + 1] {'\0'};
    for (int i = 0; i < size; i += 1)
    {
        data[i] = s.at(i);
    }
}

CustomString::CustomString(char s)
{
    size = 1;
    data = new char[2] {'\0'};
    data[0] = s;
}

CustomString::CustomString(CustomString& str) {
    size = str.size;
    data = new char[size];
    for (int i = 0; i < size; i++) {
        data[i] = str.data[i];
    }
}

void CustomString::setSize(int s)
{
    size = s;
    if (data != NULL)
        delete data;
    data = new char[size + 1] {'\0'};
}

void CustomString::setString(const string s)
{
    size = s.size();
    if (data != NULL)
        delete data;
    data = new char[size + 1] {'\0'};
    for (int i = 0; i < size; i += 1)
    {
        data[i] = s.at(i);
    }
}

void CustomString::setString(CustomString s)
{
    size = s.size;
    if (data != NULL)
        delete data;
    data = new char[size + 1] {'\0'};
    for (int i = 0; i < size; i += 1)
    {
        data[i] = s.data[i];
    }
}

void CustomString::setString(char* s)
{
    size = 0;
    while (s[size] != '\0')
    {
        size += 1;
    }

    if (data != NULL)
        delete data;
    data = new char[size + 1] {'\0'};
    for (int i = 0; i < size; i += 1)
    {
        data[i] = s[i];
    }
}

void CustomString::setString(char s)
{
    size = 1;

    if (data != NULL)
        delete data;
    data = new char[2] {'\0'};
    data[0] = s;
}

char CustomString::CustomGetAt(int s)
{
    if (s < size)
    {
        return data[s];
    }
    cout << "\tError! Index " << s << " out of range.\n";
    return '\0';
}

void CustomString::CustomSetAt(int s, char c)
{
    if (s < size)
        data[s] = c;
    else cout << "\tError! Index " << s << " out of range.\n";
}

char* CustomString::get_String()
{
    return data;
}

int CustomString::getSize()
{
    return size;
}

void CustomString::print()
{
    for (int i = 0; i < size; i += 1)
    {
        cout << data[i];
    }
}

bool CustomString::operator == (CustomString s)
{
    if (size != s.getSize())return false;
    for (int i = 0; i < size; i += 1)
    {
        if (data[i] != s.data[i])return false;
    }
    return true;
}

bool CustomString::operator == (string s)
{
    if (size != s.size())return false;
    for (int i = 0; i < size; i += 1)
    {
        if (data[i] != s.at(i))return false;
    }
    return true;
}

bool CustomString::operator != (CustomString s)
{
    if (size != s.getSize())return true;
    for (int i = 0; i < size; i += 1)
    {
        if (data[i] != s.data[i])return true;
    }
    return false;
}

bool CustomString::operator != (string s)
{
    if (size != s.size())return true;
    for (int i = 0; i < size; i += 1)
    {
        if (data[i] != s.at(i))return true;
    }
    return false;
}

void CustomString::operator = (string s)
{
    size = s.size();
    if (data != NULL)
        delete data;
    data = new char[size + 1] {'\0'};
    for (int i = 0; i < size; i += 1)
    {
        data[i] = s.at(i);
    }
}

void CustomString::operator = (CustomString s)
{
    size = s.size;
    if (data != NULL)
        delete data;
    data = new char[size + 1] {'\0'};
    for (int i = 0; i < size; i += 1)
    {
        data[i] = s.data[i];
    }
}

void CustomString::operator = (char* s)
{
    size = 0;
    while (s[size] != '\0')
    {
        size += 1;
    }

    if (data != NULL)
        delete data;
    data = new char[size + 1] {'\0'};
    for (int i = 0; i < size; i += 1)
    {
        data[i] = s[i];
    }
}

bool CustomString::operator > (CustomString s)
{
    int standard = 0;
    this->size > s.getSize() ? standard = s.getSize() : standard = this->size;

    for (int i = 0; i < standard; i += 1)
    {
        if (this->CustomGetAt(i) > s.CustomGetAt(i))
        {
            return true;
        }

        else if (this->CustomGetAt(i) < s.CustomGetAt(i))
        {
            return false;
        }
    }
    if (this->size > s.getSize())
        return true;

    return false;
}

bool CustomString::operator < (CustomString s)
{
    if (*this == s)return 0;
    return !(*this > s);
}

bool CustomString::operator <= (CustomString s)
{
    return ((*this < s) || (*this == s));
}

bool CustomString::operator >= (CustomString s)
{
    return ((*this > s) || (*this == s));
}

CustomString CustomString::operator+(const char& str) {
    if (data == NULL) size = 0;//for safity; if given string is null it will make it size 0 so that new size is calculated correctly
    int newSize;
    newSize = size + 1; //calculating new size
    char* newString = new char[newSize];//making new memory of new size
    //coping the previous string into newString --
    for (int i = 0; i < size; i++) {
        newString[i] = data[i];
    }
    // -------------------------------------------
    //adding the new str data into newString -----
    newString[size] = str;
    //--------------------------------------------
    if (data != NULL) delete[] data; //deleting the previous data
    data = newString; //pointing string to new data
    newString = NULL; //making new data null to avoid any danglling pointer
    size = newSize; // sizving the new size
    return *this;
}

CustomString CustomString::operator+(const char* str) {
    if (data == NULL) size = 1; //for stafity; if given data is null it will make it size 1 so that new size is calculated correctly
    if (*str == '\0') return *this; //for stafity; if given data is null it will not add any thing
    //calculating size of str ------------------
    int sizeOfStr = 0;
    while (1) {
        if (str[sizeOfStr] == '\0') break;
        else sizeOfStr++;
    }
    sizeOfStr++;
    //--------------------------------------------
    int newSize;
    newSize = size + sizeOfStr - 1; //calculating new size
    char* newdata = new char[newSize]; //making new memory of new size
    //coping the previous data into newdata --
    for (int i = 0; i < size - 1; i++) {
        newdata[i] = data[i];
    }
    // -------------------------------------------
    //adding the new str data into newdata -----
    for (int i = 0; i < sizeOfStr; i++) {
        newdata[size - 1 + i] = str[i];
    }
    //--------------------------------------------
    if (data != NULL) delete[] data; //deleting the previous data
    data = newdata; //pointing data to new data
    newdata = NULL; //making new data null to avoid any danglling pointer
    size = newSize; // sizving the new size
    return *this;
}

const char CustomString::operator[](int i) const {
    if ((i > 0 ? i : -i) >= size) return 0;//checking if the integer is valid for cstring
    if (i >= 0) return data[i]; //if integer is positive it will directly return the index
    else return data[size + i - 1]; //if integer is negaitive it will return the index from end of csting
}

void CustomString::clear() {
    delete[] data;
    data = nullptr;
    size = 0;
}

CustomString::~CustomString() {
    if (data) delete[] data;
}

void CustomString::changetoComa() {
    for (int i = 0; i < size; i++) {
        if (data[i] == '\0') data[i] = ',';
    }
}

istream& operator>>(istream& input, CustomString& s) {

    char* bufferEmpty = new char[1000] {'-'};
    input >> bufferEmpty;
    s.setString(bufferEmpty);
    return input;
}

fstream& operator<<(fstream& output, CustomString& str) {

    if (str.getSize() == 0) return output; //checking if str is null meaning it does not contain any vaue then it will return output without doing anything
    //this function will first calculate size of strung in str the it will copy each char element present in string of str to stt and then it will save it in output
    //const int size = str.getSize();// +1;
    //char* stt = new char[size];
    //for (int i = 0; i < size - 1; i++) {
    //	stt[i] = str[i];
    //}
    //stt[size - 1] = '\0';

    output.write(str.data, str.size);
    return output;

    //output << s.get_String();
}

fstream& operator>>(fstream& input, CustomString& str) {
    str.clear();
    char temp;
    temp = input.get(); //taking each character 
    //int i = 0;
    while (1) {
        //cout << i++ << endl;
        if (temp == '\n' || temp == '\0') { //if end of string is reached loop will be breaked
            break;
        }
        if (temp == '\r') { // Skip carriage return (Windows-style line endings)
            break;
        }
        else str + temp; //adding character to str
        temp = input.get(); //saving character from input to temporary variable
    }
    return input;

}

void concatenate(CustomString& s1, CustomString s2)
{
    CustomString str_ret(s1.getSize() + s2.getSize());

    for (int i = 0; i < s1.getSize(); i += 1)
    {
        str_ret.CustomSetAt(i, s1.CustomGetAt(i));
    }

    for (int i = s1.getSize(), j = 0; i < str_ret.getSize(); i += 1, j += 1)
    {
        str_ret.CustomSetAt(i, s2.CustomGetAt(j));
    }

    s1.setString(str_ret);
}

void concatenate_flip(CustomString s1, CustomString& s2)
{
    CustomString str_ret(s1.getSize() + s2.getSize());

    for (int i = 0; i < s1.getSize(); i += 1)
    {
        str_ret.CustomSetAt(i, s1.CustomGetAt(i));
    }

    for (int i = s1.getSize(), j = 0; i < str_ret.getSize(); i += 1, j += 1)
    {
        str_ret.CustomSetAt(i, s2.CustomGetAt(j));
    }

    s2.setString(str_ret);
}

void concatenate(CustomString& s1, const string s)
{
    CustomString s2(s);
    CustomString str_ret(s1.getSize() + s2.getSize());

    for (int i = 0; i < s1.getSize(); i += 1)
    {
        str_ret.CustomSetAt(i, s1.CustomGetAt(i));
    }

    for (int i = s1.getSize(), j = 0; i < str_ret.getSize(); i += 1, j += 1)
    {
        str_ret.CustomSetAt(i, s2.CustomGetAt(j));
    }

    s1.setString(str_ret);
}

void concatenate(string s, CustomString& s1)
{
    CustomString s2(s);
    CustomString str_ret(s1.getSize() + s2.getSize());

    for (int i = 0; i < s2.getSize(); i += 1)
    {
        str_ret.CustomSetAt(i, s2.CustomGetAt(i));
    }

    for (int i = s2.getSize(), j = 0; i < str_ret.getSize(); i += 1, j += 1)
    {
        str_ret.CustomSetAt(i, s1.CustomGetAt(j));
    }

    s1.setString(str_ret);
}

void concatenate(CustomString& s1, char s)
{
    CustomString s2;
    s2.setString(s);
    CustomString str_ret(s1.getSize() + s2.getSize());

    for (int i = 0; i < s1.getSize(); i += 1)
    {
        str_ret.CustomSetAt(i, s1.CustomGetAt(i));
    }

    for (int i = s1.getSize(), j = 0; i < str_ret.getSize(); i += 1, j += 1)
    {
        str_ret.CustomSetAt(i, s2.CustomGetAt(j));
    }

    s1.setString(str_ret);
}
