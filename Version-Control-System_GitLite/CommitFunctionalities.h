#pragma once
#include <iostream>
#include <filesystem>
#include "CustomString.h"
#include "CustomList.h"
#include "HelpingFunctions.h"
#include "Stack.h"
using namespace std;
using namespace filesystem;

path mainDir;
class commitClass
{

    path folderPath;

public:

    commitClass()
    {
        folderPath = "AliSher/MASTER/COMMIT";
    }

    void setFolderPath(path pathToFolder)
    {
        folderPath = pathToFolder;
    }

    void commitChanges(CustomString str)
    {
        CustomString newname;
        CustomString sv;

        if (!exists(folderPath))
        {
            create_directories(folderPath);
        }
        current_path(folderPath);

        sv.setString(str);
        concatenate(sv, " ");
        newname.setString(str);

        concatenate(sv, time_appending());
        newname.setString(sv);
        concatenate(newname, ".txt");

        char temp[] = "tempCommit.txt";
        char* final_ = new char[newname.getSize() + 1] {'\0'};
        for (int i = 0; i < newname.getSize(); i += 1)
        {
            final_[i] = newname.CustomGetAt(i);
        }

        int status = rename(temp, final_);

        //append here

        ofstream File("metadata.txt", ios::app); // ios::app is to append stuff

        for (int i = 0; i < sv.getSize(); i += 1)
        {
            File << sv.CustomGetAt(i);
        }

        File << '\n';
        File.close();

        current_path(mainDir);

    }

    void displayLog()
    {

        if (!exists(folderPath))
        {
            create_directories(folderPath);
        }
        current_path(folderPath);

        CustomList<CustomString> files;
        ifstream File("metadata.txt");
        char b[1000];
        while (File.getline(b, 1000))
        {
            CustomString t(b);
            concatenate(t, ".txt");
            files.insert_object(t);
        }
        File.close();

        for (int i = 0; i < files.getSize(); i += 1)
        {
            cout << "\nLog " << " " << i + 1 << " : ";
            files.getElement(i).print();
            cout << '\n';

            char* b2 = new char[files.getElement(i).getSize() + 1] {'\0'};

            for (int j = 0; j < files.getElement(i).getSize(); j += 1)
            {
                b2[j] = files.getElement(i).CustomGetAt(j);
            }

            ifstream File2(b2);
            while (File2.getline(b, 1000))
            {
                CustomString t(b);
                cout << '\t';
                t.print();
                cout << '\n';
            }
            File2.close();

        }

        current_path(mainDir);
    }

    void saveChanges(CustomString str)
    {
        if (!exists(folderPath))
        {
            create_directories(folderPath);
        }
        current_path(folderPath);

        ofstream File("tempCommit.txt", ios::app); // ios::app is to append stuff

        for (int i = 0; i < str.getSize(); i += 1)
        {
            File << str.CustomGetAt(i);
        }
        File << endl;
        File.close();
        current_path(mainDir);
    }
};