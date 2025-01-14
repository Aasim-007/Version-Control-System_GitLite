#pragma once
#include <iostream>
#include <filesystem>
#include "CustomString.h"
#include "CustomList.h"
#include "HelpingFunctions.h"
#include "Stack.h"
using namespace std;
using namespace filesystem;

path calculateSHA256(const path& filePath) {

    path commandPath = "certutil -hashfile \"";
    commandPath += filePath;
    commandPath += "\" SHA256";

    CustomString command = commandPath.string();


    char buffer[128];
    path cmdOutput;

    // Open a pipe to execute the command
    FILE* pipe = _popen(command.get_String(), "r");
    if (!pipe) {
        throw runtime_error("Failed to execute certutil command!");
    }

    // Read the output of the command line by line
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        cmdOutput += buffer;
    }

    // Close the pipe
    _pclose(pipe);

    CustomString result = cmdOutput.string();
    path ret;

    int i = 0;
    while (result[i] != '\0')
    {
        if (result[i] == '\n')
        {
            i++;
            int j = 0;
            while (result[i] != '\n')
            {

                ret += result[i];
                i++;
            }
            break;
        }
        i++;
    }


    return ret;
}

int customStoi(const char* str) {
    if (str == nullptr || *str == '\0') {
        throw std::invalid_argument("Input string is empty or null.");
    }

    int result = 0;
    bool isNegative = false;
    const char* ptr = str;

    // Handle optional '+' or '-' sign
    if (*ptr == '-') {
        isNegative = true;
        ++ptr;
    }
    else if (*ptr == '+') {
        ++ptr;
    }

    // Convert characters to integer
    int i = 0;
    while (ptr[i] != '\0')
    {
        if (ptr[i] < '0' || ptr[i]> '9') {
            throw std::invalid_argument("Input string contains non-digit characters.");
        }

        int digit = ptr[i] - '0';

        // Check for overflow
        if (result > (INT_MAX - digit) / 10) {
            throw std::out_of_range("Integer overflow detected.");
        }

        result = result * 10 + digit;
        i++;
    }

    return isNegative ? -result : result;
}

CustomString extractColumn2(ColSelect& ColS, CustomString& str)
{
    int index = 0;
    for (int i = 0; i < ColS.index; i++)
    {
        while (str[index] != ',' && str[index] != '\0') index++;
        if (str[index] == ',') index++;
    }
    CustomString column;
    while (str[index] != ',' && str[index] != '\0')
    { // Handles last entity
        column + str[index];
        index++;
    }
    column + '\0';

    return column;
}

int hashString(CustomString& col)
{
    int product = 1;
    for (int i = 0; (col.get_String())[i] != '\0'; ++i)
    {
        product *= (col.get_String())[i];
        product %= 29;
    }
    return product % 29;
}

int hashInteger(CustomString& col)
{
    int product = 1;
    for (int i = 0; (col.get_String())[i] != '\0'; ++i)
    {
        if (isdigit((col.get_String())[i]))
        {
            product *= ((col.get_String())[i] - '0');
            product %= 29;
        }
    }
    return product % 29;
}

int generateInstructorHash(CustomString& row)
{
    int i = 0;
    int nCols = 0;
    while (row[i] != '\0')
    {
        if (row[i] == ',')
        {
            nCols++;
        }
        i++;
    }


    int finalHash = 0;
    for (int i = 0; i < nCols; i++)
    {
        ColSelect index;
        index.index = i;
        CustomString colData = extractColumn2(index, row);


        bool isInteger = true;
        for (int i = 0; (colData.get_String())[i] != '\0'; ++i) {
            if (!isdigit((colData.get_String())[i])) {
                isInteger = false;
                break;
            }
        }

        if (isInteger) {
            finalHash += hashInteger(colData);
        }
        else {
            finalHash += hashString(colData);
        }

        finalHash %= 29;
    }

    if (finalHash == -3)
        cout << "ok";

    return finalHash;

}

char* intToString(int num) {
    bool isNegative = num < 0;  // Check if the number is negative
    if (num == 0) {
        char* str = new char[2];
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    int temp = num;
    int digitCount = 0;

    // Handle negative numbers
    if (isNegative) {
        num = -num;  // Make the number positive for now
        digitCount++;
    }

    // Count digits in the absolute value of num
    int tempNum = num;
    do {
        digitCount++;
        tempNum /= 10;
    } while (tempNum != 0);

    // Allocate memory for the string (+1 for null terminator)
    char* str = new char[digitCount + 1];
    str[digitCount] = '\0';  // Null terminator

    // Convert the digits to characters
    for (int i = digitCount - 1; i >= 0; i--) {
        str[i] = (num % 10) + '0';
        num /= 10;
    }

    // Add negative sign if the number was negative
    if (isNegative) {
        str[0] = '-';
    }

    return str;
}

class merkilClass
{
    path folderPath;
    path head;

public:

    void setFolderPath(path pathToFolder)
    {
        folderPath = pathToFolder;
    }


    CustomString theSha256(path& toHash)
    {

        path ok = calculateSHA256(toHash);

        CustomString res = ok.string();
        return res;
    }

    CustomString sirShehryarWala(path& toHash)
    {
        CustomString row;
        ifstream toReadFile;
        toReadFile.open(toHash);
        char buffer[1000];
        toReadFile.getline(buffer, 1000);
        toReadFile.getline(buffer, 1000);
        row.setString(buffer);

        int hash = generateInstructorHash(row);

        return CustomString(intToString(hash));

    }

    Stack<path>* initilizeMerkilTree(int konsaHash, Stack<path>& paths)
    {
        Stack<path>* paths2 = new Stack<path>;

        while (!paths.isEmpty())
        {
            //poping out of stack
            path srcFilePath = paths.top();
            std::cout << "Processing file: " << srcFilePath << std::endl;
            paths.pop();

            if (!exists(srcFilePath)) {
                std::cerr << "Error: File does not exist - " << srcFilePath << std::endl;
                continue;
            }

            path destFilePath = folderPath / "temp.txt";
            try {
                copy(srcFilePath, destFilePath, copy_options::overwrite_existing);

                //calculating hash based on selected hash
                CustomString hash;
                if (konsaHash == 2) {
                    hash = sirShehryarWala(destFilePath).get_String();
                }
                else
                {
                    hash = theSha256(destFilePath).get_String();
                }

                cout << hash.get_String() << endl;

                //edit the file to add the path of node
                ofstream toWrite;
                toWrite.open(destFilePath);
                toWrite << srcFilePath.string();
                toWrite.close();

                //renaming file after calculating hash
                path newName = folderPath / (hash.get_String());
                newName += ".txt";
                std::cout << "Renaming file to: " << newName << std::endl;
                rename(destFilePath, newName);
                paths2->push(newName);

            }
            catch (const  filesystem_error& e) {
                std::cerr << "Filesystem error: " << e.what() << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Unexpected error: " << e.what() << std::endl;
            }
        }

        return paths2;

    }

    void growTheTree(int konsaHash, Stack<path>& paths)
    {

        Stack<path> paths2;

        while (1)
        {
            path temp = paths.top();
            paths.pop();
            if (paths.isEmpty())
            {
                break;
            }
            else
            {
                paths2.push(temp);
            }

            while (!paths.isEmpty())


            {
                path path1;
                if (!paths.isEmpty())
                {
                    path1 = paths.top();
                    paths.pop();
                }
                path path2;

                if (!paths.isEmpty())

                {
                    path2 = paths.top();
                    paths.pop();
                }

                path tempPath = folderPath / "temp.txt";

                ofstream toWrite;
                toWrite.open(tempPath);

                toWrite << path1 << '\n';
                toWrite << path2;

                toWrite.close();

                CustomString hash;
                if (konsaHash == 2)
                {
                    hash = sirShehryarWala(tempPath).get_String();
                }
                else
                {
                    hash = theSha256(tempPath).get_String();
                }

                cout << hash.get_String() << endl;

                // Renaming file after calculating hash
                path newName = folderPath / (hash.get_String());
                newName += ".txt";
                std::cout << "Renaming file to: " << newName << std::endl;
                rename(tempPath, newName);

                paths2.push(newName);
            }

            path temp3 = paths2.top();
            paths2.pop();
            if (paths2.isEmpty())
            {
                break;
            }
            else
            {
                paths2.push(temp3);
            }

            while (!paths2.isEmpty())
            {
                path path3;
                path path4;
                if (!paths2.isEmpty())
                {
                    path3 = paths2.top(); // Renamed to path3
                    paths2.pop();
                }

                if (!paths2.isEmpty())
                {
                    path4 = paths2.top(); // Renamed to path4
                    paths2.pop();
                }

                path tempPath2 = folderPath / "temp2.txt"; // Renamed to tempPath2

                ofstream toWrite;
                toWrite.open(tempPath2);

                toWrite << path3 << '\n';
                toWrite << path4;

                toWrite.close();

                CustomString hash;
                if (konsaHash == 2)
                {
                    hash = sirShehryarWala(tempPath2).get_String();
                }
                else
                {
                    hash = theSha256(tempPath2).get_String();
                }

                cout << hash.get_String() << endl;

                // Renaming file after calculating hash
                path newName2 = folderPath / (hash.get_String()); // Renamed to newName2
                newName2 += ".txt";
                std::cout << "Renaming file to: " << newName2 << std::endl;
                rename(tempPath2, newName2);

                paths.push(newName2);
            }
        }


    }

    void makeMerkilTree(Stack<path>& paths)
    {

        system("cls");

        int num = 0;
        while (true) {
            system("cls");
            cout << "Select Hash" << endl;
            cout << "1. SHA 256" << endl;
            cout << "2. The instructor hash" << endl;

            cout << "Enter your choice (1 or 2): ";
            cin >> num;

            if (cin.fail() || (num != 1 && num != 2)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input! Please enter 1 or 2." << endl;
                continue;
            }
            break;
        }

        Stack<path>* paths2 = initilizeMerkilTree(num, paths);


        growTheTree(num, *paths2);


        path TempRoot = folderPath;
        TempRoot /= head;

        head = TempRoot.filename();

    }
};