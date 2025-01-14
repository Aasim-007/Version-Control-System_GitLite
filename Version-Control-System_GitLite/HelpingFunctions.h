#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "CustomString.h"
#include "CustomList.h"
using namespace std;
using namespace filesystem;

char* time_appending()
{
    time_t timestamp;
    time(&timestamp);
    static char tt[100];  // Buffer for storing the result of ctime_s
    errno_t err = ctime_s(tt, sizeof(tt), &timestamp);

    for (int i = 0; i < 100; i += 1)
    {
        if (tt[i] == '\n')
        {
            tt[i] = '-';
            break;
        }

        if (tt[i] == ':')
        {
            tt[i] = ';';
        }

    }

    return tt;
}

struct ColSelect
{
    CustomString str;
    int index = -1;
};

void DisplayFisrtRow(ColSelect& key_tree, filesystem::path CSVFilePath)
{
    ifstream dataset(CSVFilePath);
    CustomList<char> char_store;
    CustomList<CustomString> word_store;
    int total_cols = 1;
    char ch = '-';
    while (ch != '\n')
    {
        dataset.get(ch);
        char_store.insert_object(ch);
    }

    dataset.close();

    int ind = 0;
    CustomString word_current(0);
    while (ind < char_store.getSize())
    {
        if (char_store.getElement(ind) != ',')
        {
            concatenate(word_current, char_store.getElement(ind));
        }
        else
        {
            word_store.insert_object(word_current);
            word_current.setSize(0);
        }

        ind += 1;
    }

    bool b1 = 0;
    int choice = -1;

    while (choice < 1 || choice > word_store.getSize())
    {
        cout << "Select your column for creating a key!\n";
        for (int i = 0; i < word_store.getSize(); i += 1)
        {
            cout << i + 1 << ")  "; word_store.getElement(i).print();
            cout << '\n';
        }
        cout << "Choice(index) --> ";
        cin >> choice;
        if (choice >= 1 && choice <= word_store.getSize())
            b1 = 1;

        system("cls");
        if (!b1)
            cout << "\nplease re-enter a valid column index!!\n\n\n";
    }
    CustomString tempStr = word_store.getElement(choice - 1);
    key_tree.str = tempStr;
    key_tree.index = choice - 1;
    system("cls");

}

void TakeDataInput(CustomString& str, filesystem::path CSVFilePath)
{
    ifstream dataset(CSVFilePath);
    CustomList<char> char_store;
    CustomList<CustomString> word_store;
    int total_cols = 1;
    char ch = '-';
    while (ch != '\n')
    {
        dataset.get(ch);
        char_store.insert_object(ch);
    }

    dataset.close();

    int ind = 0;
    CustomString word_current(0);
    while (ind < char_store.getSize())
    {
        if (char_store.getElement(ind) != ',')
        {
            concatenate(word_current, char_store.getElement(ind));
        }
        else
        {
            word_store.insert_object(word_current);
            word_current.setSize(0);
        }

        ind += 1;
    }

    bool b1 = 0;
    int choice = -1;
    cin.ignore();

    while (choice < 1 || choice > word_store.getSize())
    {
        cout << "Please enter data for each column!\n";
        for (int i = 0; i < word_store.getSize(); i += 1)
        {
            char sto[1000];
            cout << i + 1 << ")  "; word_store.getElement(i).print();
            cout << ": ";
            cin.getline(sto, 1000);
            str + sto;
            if (i + 1 < word_store.getSize())
                str + ',';
        }
        choice = 1;
        if (choice >= 1 && choice <= word_store.getSize())
            b1 = 1;

        system("cls");
    }
}

void random64Generator(path& filename) {
    char _64[69];
    for (int i = 0; i < 64; i++) {
        int tempNum = rand() % 3;
        if (tempNum == 0) _64[i] = 'a' + rand() % 26;
        else if (tempNum == 1) _64[i] = 'A' + rand() % 26;
        else if (tempNum == 2) _64[i] = '0' + rand() % 10;
    }
    _64[64] = '.';
    _64[65] = 't';
    _64[66] = 'x';
    _64[67] = 't';
    _64[68] = '\0';
    filename = _64;
}

CustomString extractColumn(ColSelect& ColS, CustomString& str) {
    int index = 0;
    for (int i = 0; i < ColS.index; i++) {
        while (str[index] != ',') index++;
        index++;
    }
    CustomString column;
    while (!(str[index] == ',' || index > str.getSize())) { //one more condition needed for last entity<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        column + str[index];
        index++;
    }
    return column;
}

char* extractColumnChar(ColSelect& ColS, CustomString& str) {
    char data[1000];
    int index = 0;
    for (int i = 0; i < ColS.index; i++) {
        while (str[index] != ',') index++;
        index++;
    }
    int size = 0;
    while (!(str[index] == ',' || index > str.getSize())) { //one more condition needed for last entity<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
        data[size] = str[index];
        index++;
        size++;
    }
    char* toReturn = new char[size + 1];
    for (int i = 0; i < size; i++) {
        toReturn[i] = data[i];
    }
    toReturn[size] = '\0';
    return toReturn;
    // return column;
}