
//Ahmed Asim  :23i-0070
//Nasir Bilal :23i-0659
//Ali Sher    :23i-0683

#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <fstream>
#include <cstdio>
#include <ctime>

#include "CustomString.h"

using namespace std;
using namespace filesystem;



//template <typename T>


//Doubly Linked List ------------------------------------------------
template <typename T>
class CustomList
{
    struct Node
    {
        // Try adding an index too
        T value;
        Node* next = NULL;
        Node* prev = NULL;
    };

    friend class BTree;
    Node* head = NULL;
    int capacity = 0;
public:

    CustomList() {}

    void insert_object(T val)
    {

        if (head != NULL)
        {
            Node* temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }
            Node* this_one = new Node;
            this_one->value = val;

            temp->next = this_one;
            this_one->prev = temp;
            head->prev = this_one;
            this_one->next = head;
        }
        else
        {
            head = new Node;
            head->value = val;
            head->next = head;
            head->prev = head;
        }
        capacity += 1;

    }

    bool find(T val) {
        Node* temp = head;
        while (temp) {
            if (temp->value == val) return 1;
            temp = temp->next;
        }
        return 0;
    }

    void Remove(T val)
    {
        Node* ptr = head;

        if (ptr->value == val)
        {
            Node* temp = head;
            head = head->next;
            temp->prev->next = head;
            head->prev = temp->prev;
            delete temp;
            capacity--;
            return;
        }

        while (ptr->next != head)
        {
            if (ptr->value == val)
            {
                Node* sav = ptr->prev;
                ptr->prev->next = ptr->next;
                ptr->next->prev = sav;
                capacity -= 1;
                break;
            }
            ptr = ptr->next;
        }

    }

    bool search_it(int k)
    {
        Node* ptr = head;
        while (ptr->next != head)
        {
            if (ptr->value == k)
            {
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }

    void print()
    {
        if (head == NULL)
        {
            cout << "\nEmpty List!!\n";
            return;
        }
        int cap = capacity;
        Node* ptr = head;
        while (cap > 0)
        {
            if (ptr->value != -1)
            {
                if (T == CustomString)
                    ptr->value.print();

                else cout << ptr->value;
                cout << '\n';
            }
            ptr = ptr->next;
            cap -= 1;
        }
    }

    int getSize()
    {
        return capacity;
    }

    T getElement(int inp)
    {
        int i = 0;
        Node* temp = head;

        while (i != inp)
        {
            temp = temp->next;
            i += 1;
        }
        return temp->value;
    }

    void operator=(CustomList& copyFrom) {
        if (head) {
            Node* tempHead = head;
            do {
                Node* tempNext = head->next;
                delete head;
                head = tempNext;
            } while (head != tempHead);
            head = nullptr;
        }
        capacity = 0;

        Node* copyTempHead = copyFrom.head;
        while (capacity < copyFrom.capacity) {
            this->insert_object(copyTempHead->value);
            copyTempHead = copyTempHead->next;
        }
    }

    ~CustomList() {
        if (head) {
            Node* tempHead = head;
            do {
                Node* tempNext = head->next;
                delete head;
                head = tempNext;
            } while (head != tempHead);
        }
    }
};

CustomString Num2Str(int n)
{
    CustomString returner;
    int k = n;
    int count = 0;
    while (k != 0)
    {
        k /= 10;
        count += 1;
    }
    if (n == 0)count = 1;

    for (int i = 0; i < count; i += 1)
    {
        CustomString helper((char)((n % 10) + 48));
        concatenate_flip(helper, returner);
        n /= 10;
    }

    return returner;
}

int Str2Num(CustomString n)
{
    int num = 0;
    for (int i = 0, j = n.getSize() - 1; i < n.getSize(); i += 1, j -= 1)
    {
        num += (pow(10, i) * (n.CustomGetAt(j) - 48));
    }

    return num;
}

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

template <class T>
class Stack {
    struct sNode {
        T data;
        sNode* next;
        sNode(T data) : data(data) { next = nullptr; }
    };
    sNode* head = nullptr;
public:
    void push(T element) {
        sNode* _add = new sNode(element);
        if (head) {
            _add->next = head;
            head = _add;
        }
        else head = _add;
    }

    bool isEmpty() { return (head ? 0 : 1); }

    void pop() {
        if (isEmpty()) return;
        else {
            sNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    T top() { return head->data; }

    ~Stack() {
        /*while (head) {
            sNode* temp = head->next;
            delete head;
            head = temp;
        }*/
    }

};

// Nasir mercal --------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------------
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
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<TREEs>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
class parentTree {
    friend class VersionControlSystem;
protected:
    path folderPath;
    path CSVFilePath;
    ColSelect ColS;
    path root;
    merkilClass& merkil;
    commitClass& commit;

    struct MetaData {
        int treeType;
        path root;
        path folderPath;
        path CSVFilePath;
        ColSelect ColS;
    }metadata;

    void MetaToNode() {
        char sto[1000];
        path metadataPath = folderPath;
        metadataPath /= "metadata.txt";
        fstream metadataFile;
        metadataFile.open(metadataPath, ios::in);
        metadataFile >> metadata.treeType;
        metadataFile >> metadata.root;
        metadataFile >> metadata.folderPath;
        metadataFile >> metadata.CSVFilePath;
        metadataFile >> metadata.ColS.index;
        metadataFile.getline(sto, 1000);
        metadataFile.getline(sto, 1000);
        metadata.ColS.str.setString(sto);
        metadataFile.getline(sto, 1000);
        metadataFile.close();
    }

    void NodeToMeta() {
        path metadataPath = folderPath;
        metadataPath /= "metadata.txt";
        fstream metadataFile;
        metadataFile.open(metadataPath, ios::out);
        metadataFile << metadata.treeType;
        metadataFile << '\n';
        metadataFile << metadata.root;
        metadataFile << '\n';
        metadataFile << metadata.folderPath;
        metadataFile << '\n';
        metadataFile << metadata.CSVFilePath;
        metadataFile << '\n';
        metadataFile << metadata.ColS.index;
        metadataFile << '\n';
        metadataFile << metadata.ColS.str;
        metadataFile << '\n';
        metadataFile.close();
    }


public:

    parentTree(path folderPath, merkilClass& merkil, commitClass& commit) : folderPath(folderPath), merkil(merkil), commit(commit) {
        MetaToNode();
        //folderPath = metadata.folderPath;
        CSVFilePath = metadata.CSVFilePath;
        ColS.str = metadata.ColS.str;
        ColS.index = metadata.ColS.index;
        path tempRoot = metadata.root;

        metadata.folderPath = folderPath;
        root = folderPath;
        root /= tempRoot.filename();
        metadata.root = root;
        NodeToMeta();
    }
    parentTree(path folderPath, path CSVFilePath, ColSelect ColS, int treeNumber, merkilClass& merkil, commitClass& commit)
        : folderPath(folderPath), CSVFilePath(CSVFilePath), ColS(ColS), merkil(merkil), commit(commit) {
        metadata.treeType = treeNumber;
        metadata.ColS.index = ColS.index;
        metadata.ColS.str = ColS.str;
        metadata.folderPath = folderPath;
        metadata.CSVFilePath = CSVFilePath;
    }

    virtual void insert(CustomString& row) = 0;
    virtual void PrintTree() {}
    virtual void SearchTree(CustomString colData) {}
    virtual void DeleteTree(CustomString colData) {}

    ~parentTree() {
        metadata.root = root;
        NodeToMeta();
    }
};

//AVL Tree ------------------------------------------------------------------------------------

class AVL : public parentTree {

    //commitDat&a com(folderPath)

    struct AVLNode {
        CustomString columnData;
        CustomList<CustomString> Row_Duplicates;
        path leftChild;
        path rightChild;
    };

    int height(path& root) {
        int left = -1, right = -1;
        fstream tempFile;
        tempFile.open(root, ios::in);
        AVLNode* tempNode = new AVLNode;
        FileToNode(tempFile, *tempNode);

        if (!tempNode->leftChild.empty()) {
            path tempPath = tempNode->leftChild;
            delete tempNode;
            tempFile.close();
            left = height(tempPath);

            tempFile.open(root, ios::in);
            tempNode = new AVLNode;
            FileToNode(tempFile, *tempNode);
            if (!tempNode->rightChild.empty()) {
                path tempPath = tempNode->rightChild;
                delete tempNode;
                tempFile.close();
                right = height(tempPath);
            }
            else {
                delete tempNode;
                tempFile.close();
            }
        }
        else {
            if (!tempNode->rightChild.empty()) {
                path tempPath = tempNode->rightChild;
                delete tempNode;
                tempFile.close();
                right = height(tempPath);
            }
            else {
                delete tempNode;
                tempFile.close();
            }
        }


        if (left > right) return left + 1;
        else return right + 1;
    }

    void RightRotation(path& root) {
        path temp = root;

        fstream tempFile;
        tempFile.open(root, ios::in);
        AVLNode tempNode;
        FileToNode(tempFile, tempNode);

        root = tempNode.leftChild;

        fstream tempFile2;
        tempFile2.open(root, ios::in);
        AVLNode tempNode2;
        FileToNode(tempFile2, tempNode2);

        tempNode.leftChild = tempNode2.rightChild;
        tempNode2.rightChild = temp;

        tempFile.close();
        tempFile2.close();
        tempFile.open(temp, ios::out);
        tempFile2.open(root, ios::out);
        NodeToFile(tempNode, tempFile);
        NodeToFile(tempNode2, tempFile2);
        tempFile.close();
        tempFile2.close();
    }

    void LeftRotation(path& root) {
        path temp = root;

        fstream tempFile;
        tempFile.open(root, ios::in);
        AVLNode tempNode;
        FileToNode(tempFile, tempNode);

        root = tempNode.rightChild;

        fstream tempFile2;
        tempFile2.open(root, ios::in);
        AVLNode tempNode2;
        FileToNode(tempFile2, tempNode2);

        tempNode.rightChild = tempNode2.leftChild;
        tempNode2.leftChild = temp;


        tempFile.close();
        tempFile2.close();
        tempFile.open(temp, ios::out);
        tempFile2.open(root, ios::out);
        NodeToFile(tempNode2, tempFile2);
        NodeToFile(tempNode, tempFile);
        tempFile.close();
        tempFile2.close();
    }

    int BalanceFactor(path root) {
        int bfl = -1, bfr = -1;

        fstream tempFile;
        tempFile.open(root);
        AVLNode tempNode;
        FileToNode(tempFile, tempNode);

        if (!tempNode.rightChild.empty()) bfr = height(tempNode.rightChild);
        if (!tempNode.leftChild.empty()) bfl = height(tempNode.leftChild);

        tempFile.close();
        return bfr - bfl;
    }

    void Balance(path& root) {

        fstream tempFile;
        tempFile.open(root, ios::in);
        AVLNode tempNode;
        FileToNode(tempFile, tempNode);
        tempFile.close();

        //AVL Functionalities
        if (BalanceFactor(root) == 2) { //right heavy
            if (BalanceFactor(tempNode.rightChild) == 1 || BalanceFactor(tempNode.rightChild) == 0) LeftRotation(root); //Single Left rotation LL
            else { //double rotation LR
                RightRotation(tempNode.rightChild);
                fstream tempFile;
                tempFile.open(root, ios::out);
                NodeToFile(tempNode, tempFile);
                tempFile.close();
                LeftRotation(root);
            }
        }
        else if (BalanceFactor(root) == -2) { //left heavy
            if (BalanceFactor(tempNode.leftChild) == -1 || BalanceFactor(tempNode.leftChild) == 0) RightRotation(root); //single right rotation RR
            else { //double rotation RL
                LeftRotation(tempNode.leftChild);
                fstream tempFile;
                tempFile.open(root, ios::out);
                NodeToFile(tempNode, tempFile);
                tempFile.close();
                RightRotation(root);
            }
        }
    }

    void FileToNode(fstream& thisFile, AVLNode& thisNode) {
        char sto[1000];
        thisFile.getline(sto, 1000);
        thisNode.columnData.setString(sto);
        CustomString tempStr;
        thisFile.getline(sto, 1000);
        tempStr.setString(sto);
        while (tempStr.getSize() != 0) {
            thisNode.Row_Duplicates.insert_object(tempStr);
            thisFile.getline(sto, 1000);
            tempStr.setString(sto);
        }
        if (!thisFile.eof()) {
            thisFile >> thisNode.leftChild;
            if (thisNode.leftChild == "NULL") {
                thisNode.leftChild.clear();
            }
            else {
                path tempPath = folderPath;
                tempPath /= thisNode.leftChild; //Foldername\\22.txt
                thisNode.leftChild = tempPath;
            }
        }
        if (!thisFile.eof()) {
            thisFile >> thisNode.rightChild;
            if (thisNode.rightChild == "NULL") {
                thisNode.rightChild.clear();
            }
            else {
                path tempPath = folderPath;
                tempPath /= thisNode.rightChild;
                thisNode.rightChild = tempPath;
            }
        }
    }

    void NodeToFile(AVLNode& thisNode, fstream& thisFile)
    {
        thisFile << thisNode.columnData;
        thisFile << '\n';
        for (int i = 0; i < thisNode.Row_Duplicates.getSize(); i++) {
            CustomString tempStr = thisNode.Row_Duplicates.getElement(i);
            thisFile << tempStr;
            thisFile << '\n';
        }
        thisFile << '\n';
        if (!thisNode.leftChild.empty()) {
            path tempPath = thisNode.leftChild.filename();
            thisFile << tempPath;
        }
        else {
            thisFile << "NULL";
        }
        thisFile << '\n';
        if (!thisNode.rightChild.empty()) {
            path tempPath = thisNode.rightChild.filename();
            thisFile << tempPath;
        }
        else {
            thisFile << "NULL";
        }
        thisFile << '\n';
    }

    path hashHelper(path toHash)
    {

        path nullPath;
        path hash;
        try {
            // Compute the SHA256 hash
            path currentPath = filesystem::current_path().string();
            currentPath /= folderPath;
            currentPath /= toHash;
            hash = calculateSHA256(currentPath);

        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            return nullPath;
        }

        return hash;
    }

    path new_AVLNode(CustomString& row)
    {
        char* key = extractColumnChar(ColS, row);
        path fileName = folderPath, tempFileName = key;
        delete key;
        //random64Generator(tempFileName);
        tempFileName += ".txt";
        fileName /= tempFileName;
        fstream _file;
        _file.open(fileName, ios::out);

#if _DEBUG
        if (!_file) {
            std::cerr << "Failed to open or create the file: " << fileName << '\n';
            int error;
            cin >> error;
            return fileName; // Return error code
        }
        else {
            std::cout << "File opened or created successfully.\n";
        }
#endif // _DEBUG

        CustomString Coldata = extractColumn(ColS, row);
        _file << Coldata;
        _file << '\n';
        _file << row;
        _file << '\n';
        _file << '\n';
        _file << "NULL\n";
        _file << "NULL\n";
        _file.close();

        //path hash = hashHelper(tempFileName);
        //hash += ".txt";

        //path oPath = filesystem::current_path().string();
        //oPath /= fileName;

        //path nPath = filesystem::current_path().string();
        //nPath /= folderPath;
        //nPath /= hash;

        //filesystem::rename(oPath.string(), nPath.string());

        //path pathToReturn = folderPath;
        //pathToReturn /= hash;

        return fileName;
    }

    void insertion(CustomString& row, path& root)
    { //make it efficient by adding a parameter of Coldata
        CustomString Coldata = extractColumn(ColS, row);
        // path fileName = folderPath;
        fstream tempFile;
        tempFile.open(root);

#if _DEBUG
        if (!tempFile) {
            std::cerr << "Failed to open file in insertion: " << root << '\n';
            int error;
            cin >> error;
            return; // Return error code
        }
        else {
            std::cout << "File opened successfully in insertion: " << root << "\n";
        }
#endif // _DEBUG

        AVLNode* tempNode = new AVLNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();

        if (Coldata == tempNode->columnData) {
            tempNode->Row_Duplicates.insert_object(row);
            tempFile.open(root);
            NodeToFile(*tempNode, tempFile);
            delete tempNode;
            tempFile.close();
        }
        else if (Coldata > tempNode->columnData) {
            if (!tempNode->rightChild.empty()) {
                path tempPath = tempNode->rightChild;
                path tempPath2 = tempNode->rightChild;
                delete tempNode;
                insertion(row, tempPath);
                if (tempPath != tempPath2) {
                    tempFile.open(root, ios::in);
                    tempNode = new AVLNode;
                    FileToNode(tempFile, *tempNode);
                    tempNode->rightChild = tempPath;
                    tempFile.close();
                    tempFile.open(root, ios::out);
                    NodeToFile(*tempNode, tempFile);
                    delete tempNode;
                    tempFile.close();
                }
            }
            else {
                tempNode->rightChild = new_AVLNode(row);
                tempFile.open(root);
                NodeToFile(*tempNode, tempFile);
                delete tempNode;
                tempFile.close();
            }

            Balance(root);
        }
        else {
            if (!tempNode->leftChild.empty()) {
                path tempPath = tempNode->leftChild;
                path tempPath2 = tempNode->leftChild;
                delete tempNode;
                insertion(row, tempPath);
                if (tempPath != tempPath2) {
                    tempFile.open(root, ios::in);
                    tempNode = new AVLNode;
                    FileToNode(tempFile, *tempNode);
                    tempNode->leftChild = tempPath;
                    tempFile.close();
                    tempFile.open(root, ios::out);
                    NodeToFile(*tempNode, tempFile);
                    delete tempNode;
                    tempFile.close();
                }
            }
            else {
                tempNode->leftChild = new_AVLNode(row);
                tempFile.open(root);
                NodeToFile(*tempNode, tempFile);
                delete tempNode;
                tempFile.close();
            }

            Balance(root);
        }

        //Balance(root);
    }

    void deleteRowData(CustomString& row, path& root) {
        CustomString Coldata = extractColumn(ColS, row);
        fstream tempFile;
        tempFile.open(root);
#if _DEBUG
        if (!tempFile) {
            std::cerr << "Failed to open file in deletion: " << root << '\n';
            int error;
            cin >> error;
            return; // Return error code
        }
        else {
            std::cout << "File opened successfully in deletion: " << root << "\n";
        }
#endif // _DEBUG
        AVLNode* tempNode = new AVLNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();

        if (Coldata == tempNode->columnData) {
            if (tempNode->Row_Duplicates.find(row)) {
                if (tempNode->Row_Duplicates.getSize() > 1) {
                    //this means that file has multiple data so i will delete only one
                    tempNode->Row_Duplicates.Remove(row);
                    tempFile.open(root, ios::out);
                    NodeToFile(*tempNode, tempFile);
                    delete tempNode;
                    tempFile.close();
                }
                else {
                    //this means that there is only one row in file so whole file will be deleted
                    if (tempNode->rightChild.empty()) {
                        path tempPath = root;
                        root = tempNode->leftChild;
                        delete tempNode;
                        remove(tempPath);
                    }
                    else {
                        path tempPath = tempNode->rightChild;
                        AVLNode* tempPathNode = new AVLNode; //<<
                        fstream tempPathFile; //<<
                        tempPathFile.open(tempPath);
                        FileToNode(tempPathFile, *tempPathNode);

                        if (tempPathNode->leftChild.empty()) {
                            tempPathNode->leftChild = tempNode->leftChild;
                            remove(root);
                            root = tempPath;
                            tempFile.open(root);
                            NodeToFile(*tempPathNode, tempFile);
                            delete tempNode;
                            delete tempPathNode;
                            tempPathFile.close();
                            tempFile.close();
                        }
                        else {
                            while (!tempPathNode->leftChild.empty()) {
                                tempPath = tempPathNode->leftChild;
                                tempPathFile.close();
                                delete tempPathNode;
                                tempPathNode = new AVLNode; //<<
                                tempPathFile.open(tempPath); //<<
                                FileToNode(tempPathFile, *tempPathNode);
                            }
                            AVLNode tempVal;

                            tempVal.columnData = tempNode->columnData;
                            tempVal.Row_Duplicates = tempNode->Row_Duplicates;

                            tempNode->columnData = tempPathNode->columnData;
                            tempNode->Row_Duplicates = tempPathNode->Row_Duplicates;

                            tempPathNode->columnData = tempVal.columnData;
                            tempPathNode->Row_Duplicates = tempVal.Row_Duplicates;

                            tempPathFile.close();
                            tempPathFile.open(tempPath, ios::out);
                            tempFile.open(root, ios::out);
                            NodeToFile(*tempNode, tempFile);
                            NodeToFile(*tempPathNode, tempPathFile);
                            path tempPath2 = tempNode->rightChild;
                            path tempPath3 = tempNode->rightChild;
                            delete tempNode;
                            delete tempPathNode;
                            tempPathFile.close();
                            tempFile.close();

                            deleteRowData(row, tempPath2);
                            if (tempPath2 != tempPath3) {
                                tempFile.open(root, ios::in);
                                tempNode = new AVLNode;
                                FileToNode(tempFile, *tempNode);
                                tempNode->rightChild = tempPath2;
                                tempFile.close();

                                tempFile.open(root, ios::out);
                                NodeToFile(*tempNode, tempFile);
                                delete tempNode;
                                tempFile.close();
                            }


                            //renaming fle
                            path oPath = filesystem::current_path().string();
                            oPath /= root;

                            path nPath = filesystem::current_path().string();
                            nPath /= tempPath;

                            filesystem::rename(oPath.string(), nPath.string());
                        }
                    }
                }
            }
            else return;
        }
        else if (Coldata < tempNode->columnData) {
            path tempPath = tempNode->leftChild;
            path tempPath2 = tempNode->leftChild;
            delete tempNode;
            deleteRowData(row, tempPath);
            if (tempPath2 != tempPath) {
                tempFile.open(root, ios::in);
                tempNode = new AVLNode;
                FileToNode(tempFile, *tempNode);
                tempNode->leftChild = tempPath;
                tempFile.close();
                tempFile.open(root, ios::out);
                NodeToFile(*tempNode, tempFile);
                delete tempNode;
                tempFile.close();
            }
        }
        else {
            path tempPath = tempNode->rightChild;
            path tempPath2 = tempNode->rightChild;
            delete tempNode;
            deleteRowData(row, tempPath);
            if (tempPath2 != tempPath) {
                tempFile.open(root, ios::in);
                tempNode = new AVLNode;
                FileToNode(tempFile, *tempNode);
                tempNode->rightChild = tempPath;
                tempFile.close();
                tempFile.open(root, ios::out);
                NodeToFile(*tempNode, tempFile);
                delete tempNode;
                tempFile.close();
            }
        }

        if (!root.empty()) Balance(root);

    }


    void InOrderTraversalMerkil(path root, Stack<path>& stack) {
        fstream tempFile;
        tempFile.open(root);
        AVLNode* tempNode = new AVLNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        if (!tempNode->leftChild.empty()) {
            path tempPath = tempNode->leftChild;
            delete tempNode;
            InOrderTraversalMerkil(tempPath, stack);
        }
        else {
            delete tempNode;
        }

        stack.push(root);

        tempFile.open(root);
        tempNode = new AVLNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        if (!tempNode->rightChild.empty()) {
            path tempPath = tempNode->rightChild;
            delete tempNode;
            InOrderTraversalMerkil(tempPath, stack);
        }
        else {
            delete tempNode;
        }
    }

    void InOrderTraversal(path root) {
        fstream tempFile;
        tempFile.open(root);
        AVLNode* tempNode = new AVLNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        if (!tempNode->leftChild.empty()) {
            path tempPath = tempNode->leftChild;
            delete tempNode;
            InOrderTraversal(tempPath);
        }
        else {
            delete tempNode;
        }
        tempFile.open(root);
        tempNode = new AVLNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        cout << "\033[91m";
        for (int i = 0; i < 120; i++) cout << '-';
        cout << endl << "\033[0m";
        cout << "\033[97m" << "Key is: " << "\033[92m" << tempNode->columnData.get_String() << endl;
        cout << "\033[97m" << "All Instance of this Key:- " << "\033[0m" << endl;
        for (int i = 0; i < tempNode->Row_Duplicates.getSize(); i++) {
            tempNode->Row_Duplicates.getElement(i).print();
            cout << endl;
        }
        cout << "\033[97m" << "Left Child: " << "\033[0m" << tempNode->leftChild << '\t' << "\033[97m" << "Right Child: " << "\033[0m" << tempNode->rightChild << endl;

        if (!tempNode->rightChild.empty()) {
            path tempPath = tempNode->rightChild;
            delete tempNode;
            InOrderTraversal(tempPath);
        }
        else {
            delete tempNode;
        }
    }

    void SearchTree(CustomString colData, path root) {
        fstream tempFile;
        tempFile.open(root);
        AVLNode* tempNode = new AVLNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        if (tempNode->columnData == colData) {
            cout << "\033[91m";
            for (int i = 0; i < 120; i++) cout << '-';
            cout << endl << "\033[0m";
            cout << "\033[97m" << "Key is: " << "\033[92m" << tempNode->columnData.get_String() << endl;
            cout << "\033[97m" << "All Instance of this Key:- " << "\033[0m" << endl;
            for (int i = 0; i < tempNode->Row_Duplicates.getSize(); i++) {
                tempNode->Row_Duplicates.getElement(i).print();
                cout << endl;
            }
            cout << "\033[97m" << "Left Child: " << "\033[0m" << tempNode->leftChild << '\t' << "\033[97m" << "Right Child: " << "\033[0m" << tempNode->rightChild << endl;
            delete tempNode;
            return;
        }
        if (tempNode->columnData < colData) {
            if (tempNode->rightChild.empty()) {
                cout << "\033[91m" << "ERROR : Key Not Found!" << "\033[0m";
                delete tempNode;
                return;
            }
            path tempPath = tempNode->rightChild;
            delete tempNode;
            SearchTree(colData, tempPath);
        }
        else {
            if (tempNode->leftChild.empty()) {
                cout << "\033[91m" << "ERROR : Key Not Found!" << "\033[0m";
                delete tempNode;
                return;
            }
            path tempPath = tempNode->leftChild;
            delete tempNode;
            SearchTree(colData, tempPath);
        }
    }

    void DeleteTree(CustomString& colData, path root) {
        fstream tempFile;
        tempFile.open(root);
        AVLNode* tempNode = new AVLNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        if (tempNode->columnData == colData) {
            cout << "\033[91m";
            for (int i = 0; i < 120; i++) cout << '-';
            cout << endl << "\033[0m";
            cout << "\033[97m" << "Key is: " << "\033[92m" << tempNode->columnData.get_String() << endl;
            cout << "\033[97m" << "All Instance of this Key:- " << "\033[0m" << endl;
            for (int i = 0; i < tempNode->Row_Duplicates.getSize(); i++) {
                cout << "\033[91m" << i << ": " << "\033[0m";
                tempNode->Row_Duplicates.getElement(i).print();
                cout << endl;
            }
            cout << "\033[97m" << "Left Child: " << "\033[0m" << tempNode->leftChild << '\t' << "\033[97m" << "Right Child: " << "\033[0m" << tempNode->rightChild << endl;
            cin.ignore();
            cout << "\nEnter Index : ";
            int index;
            cin >> index;
            CustomString str = tempNode->Row_Duplicates.getElement(index);
            delRowData(str);

            delete tempNode;
            return;
        }
        if (tempNode->columnData < colData) {
            if (tempNode->rightChild.empty()) {
                cout << "\033[91m" << "ERROR : Key Not Found!" << "\033[0m";
                delete tempNode;
                return;
            }
            path tempPath = tempNode->rightChild;
            delete tempNode;
            DeleteTree(colData, tempPath);
        }
        else {
            if (tempNode->leftChild.empty()) {
                cout << "\033[91m" << "ERROR : Key Not Found!" << "\033[0m";
                delete tempNode;
                return;
            }
            path tempPath = tempNode->leftChild;
            delete tempNode;
            DeleteTree(colData, tempPath);
        }
    }

public:


    AVL(path folderPath, path CSVFilePath, ColSelect ColS, merkilClass& merkil, commitClass& commit)
        : parentTree(folderPath, CSVFilePath, ColS, 1, merkil, commit) {

        fstream file;
        file.open(CSVFilePath);

#if _DEBUG //-----------------------------------
        if (!file.is_open()) {
            cerr << "Failed to open the CSV file.\n";
            int error;
            cin >> error;
            return;
        }
        else {
            cout << "File opened successfully.\n";
        }
#endif // _DEBUG ------------------------------

        CustomString thisRow;
        char sto[1000];
        file >> thisRow;
        //int i = 0;
        while (!file.eof()) {
            //if (i++ == 6)
            //	break;
            file.getline(sto, 1000);
            thisRow.setString(sto);
            if (thisRow.getSize() != 0) insert(thisRow);
        }
        cout << root;
        file.close();

        /*cout << "Enter row to del";
        int index;
        cin >> index;
        file.open(CSVFilePath);
        while (index > 0) {
            file.getline(sto, 1000);
            index--;
        }
        file.getline(sto, 1000);
        thisRow.setString(sto);
        cout << "Row to be deleted : " << thisRow.get_String();
        delRowData(thisRow);

        cout << "\nNew Root: " << root;*/

        Stack<path> stack;
        InOrderTraversalMerkil(root, stack);
        merkil.makeMerkilTree(stack);
    }

    AVL(path folderPath, merkilClass& merkil, commitClass& commit) :parentTree(folderPath, merkil, commit) {

        /*	fstream file;
            CustomString thisRow;
            char sto[1000];
            cout << "Enter row to del";
            int index;
            cin >> index;
            file.open(CSVFilePath);
            while (index > 0) {
                file.getline(sto, 1000);
                index--;
            }
            file.getline(sto, 1000);
            thisRow.setString(sto);
            cout << "Row to be deleted : " << thisRow.get_String();
            delRowData(thisRow);

            cout << "\nNew Root: " << root;*/
    }

    void insert(CustomString& row)
    {
        if (root.empty()) root = new_AVLNode(row);
        else insertion(row, root);
    }

    void delRowData(CustomString& row) {
        if (root.empty()) return;
        else deleteRowData(row, root);

        //string/
        // DELETED: jhkdsfjkjdsf,dsflkjldsf,,dfjsdhfkds,dsfdsjfsdkfds
        //com.saveChanges(string)	

        CustomString str;
        str.setString("Deleted: ");
        str + row.get_String();
        commit.saveChanges(str);
    }

    void PrintTree() {
        InOrderTraversal(root);
    }

    void SearchTree(CustomString colData) {
        SearchTree(colData, root);
    }

    void DeleteTree(CustomString colData) {
        DeleteTree(colData, root);
    }

};

//B-Tree --------------------------------------------------------------------------------------
int nodeCounter = 0;
class BTree : public parentTree
{
private:
    //data members
    const int minDegree;
    path folderPath;
    path CSVFilePath;
    ColSelect ColS;
    path root;

    class BTreeNode
    {
    public:
        bool isLeaf;
        int nValues;					//number of current values
        CustomString* keys;
        CustomList<CustomString>* rows; //array
        path* links;
        int minDegree;
        path nodeName;
        path pathOfFolder;

        BTreeNode(path nodeName, int minDegree, bool isLeaf) :isLeaf(isLeaf), minDegree(minDegree),
            pathOfFolder(nodeName)
        {
            keys = new CustomString[2 * minDegree - 1]();
            rows = new CustomList<CustomString>[2 * minDegree - 1]();
            links = new path[2 * minDegree]();
            this->nodeName += pathOfFolder;
            this->nodeName /= (CustomString(intToString(++nodeCounter)).get_String());
            this->nodeName += ".txt";

        }

        ~BTreeNode()
        {
            delete[] keys;
            delete[] rows;
            delete[] links;
        }

        BTreeNode* splitChild(int index, BTreeNode& halfNode)
        {

            BTreeNode* otherHalfNode = new BTreeNode(pathOfFolder, halfNode.minDegree, halfNode.isLeaf);
            otherHalfNode->nValues = this->minDegree - 1;

            //copying minDegree-1 last values values to otherhalf
            for (int j = 0; j < minDegree - 1; j++)
            {
                otherHalfNode->keys[j] = halfNode.keys[j + minDegree];
                otherHalfNode->rows[j] = halfNode.rows[j + minDegree];

            }

            if (!halfNode.isLeaf)    //if not leaf then copy child
            {
                for (int j = 0; j < this->minDegree; j++)
                {
                    otherHalfNode->links[j] = halfNode.links[j + minDegree];
                }
            }


            //delete above values by reducing no of values
            halfNode.nValues = minDegree - 1;


            //creating space for new child
            for (int j = this->nValues; j >= index + 1; j--)  //in the root ( from the node which the function is called )
            {
                this->links[j + 1] = this->links[j];
            }


            //link splited other half node
            this->links[index + 1] = otherHalfNode->nodeName;


            //Make space for new values
            for (int j = this->nValues - 1; j >= index; j--)
            {
                this->keys[j + 1] = this->keys[j];
                this->rows[j + 1] = this->rows[j];
            }




            // Copy the middle key of halfNode to this BTreeNode
            this->keys[index] = halfNode.keys[this->minDegree - 1];
            this->rows[index] = halfNode.rows[this->minDegree - 1];

            // Increment count of values in this BTreeNode
            this->nValues = this->nValues + 1;

            return otherHalfNode;
        }

        //void printBTreeNode()
        //{
        //	// Print whether the node is a leaf
        //	std::cout << "Is Leaf: " << (isLeaf ? "Yes" : "No") << std::endl;

        //	// Print the number of values (keys)
        //	std::cout << "Number of Values (Keys): " << nValues << std::endl;

        //	// Print the keys in the node
        //	std::cout << "Keys: ";
        //	for (int i = 0; i < nValues; ++i) {
        //		std::cout << keys[i].get_String() << " ";
        //	}
        //	std::cout << std::endl;

        //	// Print the rows associated with each key
        //	std::cout << "Rows for each Key: " << std::endl;
        //	for (int i = 0; i < nValues; ++i) {
        //		std::cout << "  Key " << i + 1 << " (" << keys[i].get_String() << "): ";

        //		

        //		CustomList<CustomString> current = rows[i];
        //		current.print();



        //		std::cout << std::endl;
        //	}

        //	// If the node is not a leaf, print the child links
        //	if (!isLeaf) {
        //		std::cout << "Child Links: " << std::endl;
        //		for (int i = 0; i <= nValues; ++i) {
        //			std::cout << "  Link " << i << ": " << links[i].string() << std::endl;
        //		}
        //	}
        //}


    };

    void insertNonFull(CustomString& row, BTreeNode& theNode);
    path newBtreeNode(CustomString& row);

public:

    //constructor
    BTree(int minDegree, path folderPath, path CSVFilePath, ColSelect ColS, merkilClass& merkil, commitClass& commit);

    BTree(int minDegree, path folderPath, merkilClass& merkil, commitClass& commit);

    virtual void insert(CustomString& row)
    {
        if (root.empty())
            root = newBtreeNode(row);
        else
            root = insertion(row, root);



    }

    path insertion(CustomString& row, path node);
    void FileToBTreeNode(fstream& thisFile, BTreeNode& thisNode);
    void BTreeNodeToFile(ofstream& thisFile, const BTreeNode& thisNode);

    void insertAt() {}
    void del() {}
    void delAt() {}
};

BTree::BTree(int minDegree, path folderPath, path CSVFilePath, ColSelect ColS, merkilClass& merkil, commitClass& commit) :
    parentTree(folderPath, CSVFilePath, ColS, 1, merkil, commit), minDegree(minDegree)
{
    fstream file;
    file.open(CSVFilePath);

    CustomString thisRow;
    char sto[1000];
    file >> thisRow;
    int i = 0;
    while (!file.eof())
    {
        if (i == 5)
            break;

        if (i == 3)
            cout << "ok";

        file.getline(sto, 1000);
        thisRow.setString(sto);
        if (thisRow.getSize() != 0) insert(thisRow);
        i++;
    }
    file.close();
}

BTree::BTree(int minDegree, path folderPath, merkilClass& merkil, commitClass& commit) : parentTree(folderPath, merkil, commit), minDegree(minDegree) {

    /*	fstream file;
        CustomString thisRow;
        char sto[1000];
        cout << "Enter row to del";
        int index;
        cin >> index;
        file.open(CSVFilePath);
        while (index > 0) {
            file.getline(sto, 1000);
            index--;
        }
        file.getline(sto, 1000);
        thisRow.setString(sto);
        cout << "Row to be deleted : " << thisRow.get_String();
        delRowData(thisRow);

        cout << "\nNew Root: " << root;*/
}

void BTree::insertNonFull(CustomString& row, BTreeNode& theNode)
{
    int rIndex = theNode.nValues - 1;        //rightMost index

    CustomString colData = extractColumn(ColS, row);
    // //rIndex will choose the child for new value
    //while (tempNode.keys[rIndex] > colData && rIndex >= 0)
    //{
    //	tempNode.keys[rIndex + 1] = tempNode.keys[rIndex--];
    //}

    //tempNode.keys[rIndex + 1] = colData;
    //tempNode.rows[rIndex + 1].insert_object(row);
    //tempNode.nValues++;
    if (!theNode.isLeaf)
    {
        //rIndex will choose the child for new value
        while (rIndex >= 0 && theNode.keys[rIndex] > colData)
        {
            --rIndex;
        }

        // See if the found child is full
        fstream tempFile;
        tempFile.open(theNode.links[rIndex + 1]);
        BTreeNode matchedChild(folderPath, minDegree, 1);
        FileToBTreeNode(tempFile, matchedChild);

        if (matchedChild.nValues == (2 * minDegree) - 1)
        {
            BTreeNode* rightNode = theNode.splitChild(rIndex + 1, matchedChild);
            if (theNode.keys[rIndex + 1] < colData)
                rIndex++;

            ofstream file1;
            file1.open(theNode.nodeName);
            BTreeNodeToFile(file1, theNode);
            file1.close();

            file1.open(matchedChild.nodeName);
            BTreeNodeToFile(file1, matchedChild);
            file1.close();

            file1.open(rightNode->nodeName);
            BTreeNodeToFile(file1, *rightNode);
            file1.close();

        }
        tempFile.close();
        //after creating space insert in the non full node
        tempFile.open(theNode.links[rIndex + 1]);
        BTreeNode tempNode(folderPath, minDegree, 1);
        FileToBTreeNode(tempFile, tempNode);
        insertNonFull(row, tempNode);


    }

    else
    {
        while (rIndex >= 0 && theNode.keys[rIndex] > colData)
            theNode.keys[rIndex + 1] = theNode.keys[rIndex--];

        theNode.keys[rIndex + 1] = colData;
        theNode.rows[rIndex + 1].insert_object(row);
        theNode.nValues++;
    }

}

path BTree::newBtreeNode(CustomString& row)
{
    path filePath = folderPath;

    filePath /= (CustomString(intToString(++nodeCounter)).get_String());

    filePath += ".txt";

    fstream _file;
    _file.open(filePath, ios::out | ios::app);
    if (!_file) {
        std::cerr << "Failed to open or create the file: " << filePath << '\n';
        int error;
        cin >> error;
        return filePath; // Return error code
    }
    else {
        std::cout << "File opened or created successfully.\n";
    }

    CustomString colData = extractColumn(ColS, row);
    _file << filePath.string() << "\n";
    _file << 1;				//is leaf
    _file << "\n";
    _file << 1;				//n values
    _file << "\n";

    _file << "\n";

    _file << colData;		//keys
    _file << "\n";

    _file << "\n";


    _file << row;
    _file << "\n";
    _file << "&\n";



    return filePath;
}

path BTree::insertion(CustomString& row, path node)
{
    //opening temp file in which data is to be inserted
    fstream tempFile;
    tempFile.open(node, ios::in);

    //transfering data from tempfile into temp node
    BTreeNode tempNode(folderPath, minDegree, 1);
    FileToBTreeNode(tempFile, tempNode);
    tempFile.close();

    int rIndex = tempNode.nValues - 1;        //rightMost index
    CustomString colData = extractColumn(ColS, row);
    bool isDone = 0;

    if (tempNode.nValues == 2 * (minDegree)-1) //n values are maximum
    {
        BTreeNode* newNode = new BTreeNode(folderPath, minDegree, 0);
        newNode->links[0] = node;

        BTreeNode* rightNode = newNode->splitChild(0, tempNode);


        if (newNode->keys[0] < colData)
        {
            insertNonFull(row, *rightNode);
        }
        else
        {
            insertNonFull(row, tempNode);
        }

        ofstream file1;
        file1.open(tempNode.nodeName);
        BTreeNodeToFile(file1, tempNode);
        file1.close();

        file1.open(newNode->nodeName);
        BTreeNodeToFile(file1, *newNode);
        file1.close();

        file1.open(rightNode->nodeName);
        BTreeNodeToFile(file1, *rightNode);
        file1.close();

        return newNode->nodeName;
    }
    else
    {

        //check if key already exists
        for (int i = 0; i < tempNode.nValues; i++)
        {
            if (colData == tempNode.keys[i])
            {
                isDone = 1;
                tempNode.rows[i].insert_object(row);
            }
        }

        if (!isDone)
        {
            insertNonFull(row, tempNode);
        }
    }

    tempFile.open(node, ios::out);
    ofstream tempf(node);
    BTreeNodeToFile(tempf, tempNode);
    tempFile.close();
    return node;

}

void BTree::FileToBTreeNode(fstream& thisFile, BTreeNode& thisNode)
{
    char buffer[1000];
    static int counter = 0;
    //filename
    thisFile.getline(buffer, 1000);
    cout << "\n=>" << buffer << endl;
    thisNode.nodeName = buffer;
    cout << thisNode.nodeName << endl;

    //isleaf node
    thisFile.getline(buffer, 1000);
    cout << "\n=>" << buffer << endl;
    thisNode.isLeaf = (customStoi(buffer) == 1); //left
    cout << thisNode.isLeaf << endl;

    //number of current values
    thisFile.getline(buffer, 1000);
    cout << "\n=>" << buffer << endl;
    thisNode.nValues = customStoi(buffer);
    cout << thisNode.nValues << endl;

    thisFile.getline(buffer, 1000);
    cout << "\n=>" << buffer << endl;
    // Read keys
    for (int i = 0; i < thisNode.nValues; ++i)
    {
        thisFile.getline(buffer, 1000);
        cout << "\n=>" << buffer << endl;

        thisNode.keys[i].setString(buffer);
        cout << thisNode.keys[i].get_String() << endl;
    }

    thisFile.getline(buffer, 1000);
    cout << "\n=>" << buffer << endl;

    //deal with duplications

    //reading each row
    for (int i = 0; i < thisNode.nValues; ++i)
    {
        bool isExit = 0;
        while (1)
        {
            CustomList<CustomString> rowList;		//reading row line
            thisFile.getline(buffer, 1000);
            cout << "\n=>" << buffer << endl;
            if (buffer[0] == '&')
            {
                isExit = 1;
                break;
            }

            CustomString* tempStr = new CustomString;		//setting node data
            tempStr->setString(buffer);
            thisNode.rows[i].insert_object(*tempStr);

        }

    }
    thisFile.getline(buffer, 1000);
    cout << "\n=>" << buffer << endl;



    //reading childs if node is not leaf
    if (!thisNode.isLeaf)
    {
        for (int i = 0; i <= thisNode.nValues; ++i)
        {
            thisFile.getline(buffer, 1000);
            cout << "\n=>" << buffer << endl;

            thisNode.links[i] = (buffer);
            cout << thisNode.links[i] << endl;
        }
    }
}

void BTree::BTreeNodeToFile(ofstream& thisFile, const BTreeNode& thisNode)
{
    thisFile << thisNode.nodeName.string() << "\n";

    // Write if it's a leaf node
    thisFile << (thisNode.isLeaf ? "1" : "0") << "\n";

    // Write the number of current values
    thisFile << thisNode.nValues << "\n\n";

    // Write the keys
    for (int i = 0; i < thisNode.nValues; ++i) {
        thisFile << thisNode.keys[i].get_String() << "\n";
    }
    thisFile << "\n";

    // Write the rows corresponding to each key
    for (int i = 0; i < thisNode.nValues; ++i) {
        CustomList<CustomString>& rowList = thisNode.rows[i];
        CustomList<CustomString>::Node* current = rowList.head; // Assuming CustomList has a `getHead()` function

        int ii = 0;
        while (current != nullptr)
        {
            if (ii != 0 && current == rowList.head)
                break;
            ii++;
            thisFile << current->value.get_String() << "\n"; // Write each row item
            cout << current->value.get_String() << endl;

            current = current->next; // Move to the next node
        }
        thisFile << "&\n"; // Separate rows for different keys
    }
    thisFile << "\n";

    // Write the child links if the node is not a leaf
    if (!thisNode.isLeaf) {
        for (int i = 0; i <= thisNode.nValues; ++i) {
            thisFile << thisNode.links[i].string() << "\n";
        }
    }
}

//Red-Black Tree -------------------------------------------------------------------------------
class Red_Black : public parentTree {

    //commitDat&a com(folderPath)

    struct Red_BlackNode {
        CustomString columnData;
        CustomList<CustomString> Row_Duplicates;
        path leftChild;
        path rightChild;
        bool isBlack = false;
    };

    int height(path& root) {
        int left = -1, right = -1;
        fstream tempFile;
        tempFile.open(root, ios::in);
        Red_BlackNode* tempNode = new Red_BlackNode;
        FileToNode(tempFile, *tempNode);

        if (!tempNode->leftChild.empty()) {
            path tempPath = tempNode->leftChild;
            delete tempNode;
            tempFile.close();
            left = height(tempPath);

            tempFile.open(root, ios::in);
            tempNode = new Red_BlackNode;
            FileToNode(tempFile, *tempNode);
            if (!tempNode->rightChild.empty()) {
                path tempPath = tempNode->rightChild;
                delete tempNode;
                tempFile.close();
                right = height(tempPath);
            }
            else {
                delete tempNode;
                tempFile.close();
            }
        }
        else {
            if (!tempNode->rightChild.empty()) {
                path tempPath = tempNode->rightChild;
                delete tempNode;
                tempFile.close();
                right = height(tempPath);
            }
            else {
                delete tempNode;
                tempFile.close();
            }
        }


        if (left > right) return left + 1;
        else return right + 1;
    }

    void RightRotation(path& root) {
        path temp = root;

        fstream tempFile;
        tempFile.open(root, ios::in);
        Red_BlackNode tempNode;
        FileToNode(tempFile, tempNode);

        root = tempNode.leftChild;

        fstream tempFile2;
        tempFile2.open(root, ios::in);
        Red_BlackNode tempNode2;
        FileToNode(tempFile2, tempNode2);

        tempNode.leftChild = tempNode2.rightChild;
        tempNode2.rightChild = temp;

        tempFile.close();
        tempFile2.close();
        tempFile.open(temp, ios::out);
        tempFile2.open(root, ios::out);
        NodeToFile(tempNode, tempFile);
        NodeToFile(tempNode2, tempFile2);
        tempFile.close();
        tempFile2.close();
    }

    void LeftRotation(path& root) {
        path temp = root;

        fstream tempFile;
        tempFile.open(root, ios::in);
        Red_BlackNode tempNode;
        FileToNode(tempFile, tempNode);

        root = tempNode.rightChild;

        fstream tempFile2;
        tempFile2.open(root, ios::in);
        Red_BlackNode tempNode2;
        FileToNode(tempFile2, tempNode2);

        tempNode.rightChild = tempNode2.leftChild;
        tempNode2.leftChild = temp;


        tempFile.close();
        tempFile2.close();
        tempFile.open(temp, ios::out);
        tempFile2.open(root, ios::out);
        NodeToFile(tempNode2, tempFile2);
        NodeToFile(tempNode, tempFile);
        tempFile.close();
        tempFile2.close();
    }

    int BalanceFactor(path root) {
        int bfl = -1, bfr = -1;

        fstream tempFile;
        tempFile.open(root);
        Red_BlackNode tempNode;
        FileToNode(tempFile, tempNode);

        if (!tempNode.rightChild.empty()) bfr = height(tempNode.rightChild);
        if (!tempNode.leftChild.empty()) bfl = height(tempNode.leftChild);

        tempFile.close();
        return bfr - bfl;
    }

    void Balance(path& root) {

        fstream tempFile;
        tempFile.open(root, ios::in);
        Red_BlackNode tempNode;
        FileToNode(tempFile, tempNode);
        tempFile.close();

        //Red_Black Functionalities
        if (BalanceFactor(root) == 2) { //right heavy
            if (BalanceFactor(tempNode.rightChild) == 1 || BalanceFactor(tempNode.rightChild) == 0) LeftRotation(root); //Single Left rotation LL
            else { //double rotation LR
                RightRotation(tempNode.rightChild);
                fstream tempFile;
                tempFile.open(root, ios::out);
                NodeToFile(tempNode, tempFile);
                tempFile.close();
                LeftRotation(root);
            }
        }
        else if (BalanceFactor(root) == -2) { //left heavy
            if (BalanceFactor(tempNode.leftChild) == -1 || BalanceFactor(tempNode.leftChild) == 0) RightRotation(root); //single right rotation RR
            else { //double rotation RL
                LeftRotation(tempNode.leftChild);
                fstream tempFile;
                tempFile.open(root, ios::out);
                NodeToFile(tempNode, tempFile);
                tempFile.close();
                RightRotation(root);
            }
        }
    }

    void FileToNode(fstream& thisFile, Red_BlackNode& thisNode) {
        char sto[1000];
        thisFile.getline(sto, 1000);
        thisNode.columnData.setString(sto);
        CustomString tempStr;
        thisFile.getline(sto, 1000);
        tempStr.setString(sto);
        while (tempStr.getSize() != 0) {
            thisNode.Row_Duplicates.insert_object(tempStr);
            thisFile.getline(sto, 1000);
            tempStr.setString(sto);
        }
        if (!thisFile.eof()) {
            thisFile >> thisNode.leftChild;
            if (thisNode.leftChild == "NULL") {
                thisNode.leftChild.clear();
            }
            else {
                path tempPath = folderPath;
                tempPath /= thisNode.leftChild; //Foldername\\22.txt
                thisNode.leftChild = tempPath;
            }
        }
        if (!thisFile.eof()) {
            thisFile >> thisNode.rightChild;
            if (thisNode.rightChild == "NULL") {
                thisNode.rightChild.clear();
            }
            else {
                path tempPath = folderPath;
                tempPath /= thisNode.rightChild;
                thisNode.rightChild = tempPath;
            }
        }
    }

    void NodeToFile(Red_BlackNode& thisNode, fstream& thisFile)
    {
        thisFile << thisNode.columnData;
        thisFile << '\n';
        for (int i = 0; i < thisNode.Row_Duplicates.getSize(); i++) {
            CustomString tempStr = thisNode.Row_Duplicates.getElement(i);
            thisFile << tempStr;
            thisFile << '\n';
        }
        thisFile << '\n';
        if (!thisNode.leftChild.empty()) {
            path tempPath = thisNode.leftChild.filename();
            thisFile << tempPath;
        }
        else {
            thisFile << "NULL";
        }
        thisFile << '\n';
        if (!thisNode.rightChild.empty()) {
            path tempPath = thisNode.rightChild.filename();
            thisFile << tempPath;
        }
        else {
            thisFile << "NULL";
        }
        thisFile << '\n';
    }

    path hashHelper(path toHash)
    {

        path nullPath;
        path hash;
        try {
            // Compute the SHA256 hash
            path currentPath = filesystem::current_path().string();
            currentPath /= folderPath;
            currentPath /= toHash;
            hash = calculateSHA256(currentPath);

        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            return nullPath;
        }

        return hash;
    }

    path new_Red_BlackNode(CustomString& row)
    {
        char* key = extractColumnChar(ColS, row);
        path fileName = folderPath, tempFileName = key;
        delete key;
        //random64Generator(tempFileName);
        tempFileName += ".txt";
        fileName /= tempFileName;
        fstream _file;
        _file.open(fileName, ios::out);

#if _DEBUG
        if (!_file) {
            std::cerr << "Failed to open or create the file: " << fileName << '\n';
            int error;
            cin >> error;
            return fileName; // Return error code
        }
        else {
            std::cout << "File opened or created successfully.\n";
        }
#endif // _DEBUG

        CustomString Coldata = extractColumn(ColS, row);
        _file << Coldata;
        _file << '\n';
        _file << row;
        _file << '\n';
        _file << '\n';
        _file << "NULL\n";
        _file << "NULL\n";
        _file.close();

        //path hash = hashHelper(tempFileName);
        //hash += ".txt";

        //path oPath = filesystem::current_path().string();
        //oPath /= fileName;

        //path nPath = filesystem::current_path().string();
        //nPath /= folderPath;
        //nPath /= hash;

        //filesystem::rename(oPath.string(), nPath.string());

        //path pathToReturn = folderPath;
        //pathToReturn /= hash;

        return fileName;
    }

    void insertion(CustomString& row, path& root)
    { //make it efficient by adding a parameter of Coldata
        CustomString Coldata = extractColumn(ColS, row);
        // path fileName = folderPath;
        fstream tempFile;
        tempFile.open(root);

#if _DEBUG
        if (!tempFile) {
            std::cerr << "Failed to open file in insertion: " << root << '\n';
            int error;
            cin >> error;
            return; // Return error code
        }
        else {
            std::cout << "File opened successfully in insertion: " << root << "\n";
        }
#endif // _DEBUG

        Red_BlackNode* tempNode = new Red_BlackNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();

        if (Coldata == tempNode->columnData) {
            tempNode->Row_Duplicates.insert_object(row);
            tempFile.open(root);
            NodeToFile(*tempNode, tempFile);
            delete tempNode;
            tempFile.close();
        }
        else if (Coldata > tempNode->columnData) {
            if (!tempNode->rightChild.empty()) {
                path tempPath = tempNode->rightChild;
                path tempPath2 = tempNode->rightChild;
                delete tempNode;
                insertion(row, tempPath);
                if (tempPath != tempPath2) {
                    tempFile.open(root, ios::in);
                    tempNode = new Red_BlackNode;
                    FileToNode(tempFile, *tempNode);
                    tempNode->rightChild = tempPath;
                    tempFile.close();
                    tempFile.open(root, ios::out);
                    NodeToFile(*tempNode, tempFile);
                    delete tempNode;
                    tempFile.close();
                }
            }
            else {
                tempNode->rightChild = new_Red_BlackNode(row);
                tempFile.open(root);
                NodeToFile(*tempNode, tempFile);
                delete tempNode;
                tempFile.close();
            }

            Balance(root);
        }
        else {
            if (!tempNode->leftChild.empty()) {
                path tempPath = tempNode->leftChild;
                path tempPath2 = tempNode->leftChild;
                delete tempNode;
                insertion(row, tempPath);
                if (tempPath != tempPath2) {
                    tempFile.open(root, ios::in);
                    tempNode = new Red_BlackNode;
                    FileToNode(tempFile, *tempNode);
                    tempNode->leftChild = tempPath;
                    tempFile.close();
                    tempFile.open(root, ios::out);
                    NodeToFile(*tempNode, tempFile);
                    delete tempNode;
                    tempFile.close();
                }
            }
            else {
                tempNode->leftChild = new_Red_BlackNode(row);
                tempFile.open(root);
                NodeToFile(*tempNode, tempFile);
                delete tempNode;
                tempFile.close();
            }

            Balance(root);
        }

        //Balance(root);
    }

    void deleteRowData(CustomString& row, path& root) {
        CustomString Coldata = extractColumn(ColS, row);
        fstream tempFile;
        tempFile.open(root);
#if _DEBUG
        if (!tempFile) {
            std::cerr << "Failed to open file in deletion: " << root << '\n';
            int error;
            cin >> error;
            return; // Return error code
        }
        else {
            std::cout << "File opened successfully in deletion: " << root << "\n";
        }
#endif // _DEBUG
        Red_BlackNode* tempNode = new Red_BlackNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();

        if (Coldata == tempNode->columnData) {
            if (tempNode->Row_Duplicates.find(row)) {
                if (tempNode->Row_Duplicates.getSize() > 1) {
                    //this means that file has multiple data so i will delete only one
                    tempNode->Row_Duplicates.Remove(row);
                    tempFile.open(root, ios::out);
                    NodeToFile(*tempNode, tempFile);
                    delete tempNode;
                    tempFile.close();
                }
                else {
                    //this means that there is only one row in file so whole file will be deleted
                    if (tempNode->rightChild.empty()) {
                        path tempPath = root;
                        root = tempNode->leftChild;
                        delete tempNode;
                        remove(tempPath);
                    }
                    else {
                        path tempPath = tempNode->rightChild;
                        Red_BlackNode* tempPathNode = new Red_BlackNode; //<<
                        fstream tempPathFile; //<<
                        tempPathFile.open(tempPath);
                        FileToNode(tempPathFile, *tempPathNode);

                        if (tempPathNode->leftChild.empty()) {
                            tempPathNode->leftChild = tempNode->leftChild;
                            remove(root);
                            root = tempPath;
                            tempFile.open(root);
                            NodeToFile(*tempPathNode, tempFile);
                            delete tempNode;
                            delete tempPathNode;
                            tempPathFile.close();
                            tempFile.close();
                        }
                        else {
                            while (!tempPathNode->leftChild.empty()) {
                                tempPath = tempPathNode->leftChild;
                                tempPathFile.close();
                                delete tempPathNode;
                                tempPathNode = new Red_BlackNode; //<<
                                tempPathFile.open(tempPath); //<<
                                FileToNode(tempPathFile, *tempPathNode);
                            }
                            Red_BlackNode tempVal;

                            tempVal.columnData = tempNode->columnData;
                            tempVal.Row_Duplicates = tempNode->Row_Duplicates;

                            tempNode->columnData = tempPathNode->columnData;
                            tempNode->Row_Duplicates = tempPathNode->Row_Duplicates;

                            tempPathNode->columnData = tempVal.columnData;
                            tempPathNode->Row_Duplicates = tempVal.Row_Duplicates;

                            tempPathFile.close();
                            tempPathFile.open(tempPath, ios::out);
                            tempFile.open(root, ios::out);
                            NodeToFile(*tempNode, tempFile);
                            NodeToFile(*tempPathNode, tempPathFile);
                            path tempPath2 = tempNode->rightChild;
                            path tempPath3 = tempNode->rightChild;
                            delete tempNode;
                            delete tempPathNode;
                            tempPathFile.close();
                            tempFile.close();

                            deleteRowData(row, tempPath2);
                            if (tempPath2 != tempPath3) {
                                tempFile.open(root, ios::in);
                                tempNode = new Red_BlackNode;
                                FileToNode(tempFile, *tempNode);
                                tempNode->rightChild = tempPath2;
                                tempFile.close();

                                tempFile.open(root, ios::out);
                                NodeToFile(*tempNode, tempFile);
                                delete tempNode;
                                tempFile.close();
                            }


                            //renaming fle
                            path oPath = filesystem::current_path().string();
                            oPath /= root;

                            path nPath = filesystem::current_path().string();
                            nPath /= tempPath;

                            filesystem::rename(oPath.string(), nPath.string());
                        }
                    }
                }
            }
            else return;
        }
        else if (Coldata < tempNode->columnData) {
            path tempPath = tempNode->leftChild;
            path tempPath2 = tempNode->leftChild;
            delete tempNode;
            deleteRowData(row, tempPath);
            if (tempPath2 != tempPath) {
                tempFile.open(root, ios::in);
                tempNode = new Red_BlackNode;
                FileToNode(tempFile, *tempNode);
                tempNode->leftChild = tempPath;
                tempFile.close();
                tempFile.open(root, ios::out);
                NodeToFile(*tempNode, tempFile);
                delete tempNode;
                tempFile.close();
            }
        }
        else {
            path tempPath = tempNode->rightChild;
            path tempPath2 = tempNode->rightChild;
            delete tempNode;
            deleteRowData(row, tempPath);
            if (tempPath2 != tempPath) {
                tempFile.open(root, ios::in);
                tempNode = new Red_BlackNode;
                FileToNode(tempFile, *tempNode);
                tempNode->rightChild = tempPath;
                tempFile.close();
                tempFile.open(root, ios::out);
                NodeToFile(*tempNode, tempFile);
                delete tempNode;
                tempFile.close();
            }
        }

        if (!root.empty()) Balance(root);

    }


    void InOrderTraversalMerkil(path root, Stack<path>& stack) {
        fstream tempFile;
        tempFile.open(root);
        Red_BlackNode* tempNode = new Red_BlackNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        if (!tempNode->leftChild.empty()) {
            path tempPath = tempNode->leftChild;
            delete tempNode;
            InOrderTraversalMerkil(tempPath, stack);
        }
        else {
            delete tempNode;
        }

        stack.push(root);

        tempFile.open(root);
        tempNode = new Red_BlackNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        if (!tempNode->rightChild.empty()) {
            path tempPath = tempNode->rightChild;
            delete tempNode;
            InOrderTraversalMerkil(tempPath, stack);
        }
        else {
            delete tempNode;
        }
    }

    void InOrderTraversal(path root) {
        fstream tempFile;
        tempFile.open(root);
        Red_BlackNode* tempNode = new Red_BlackNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        if (!tempNode->leftChild.empty()) {
            path tempPath = tempNode->leftChild;
            delete tempNode;
            InOrderTraversal(tempPath);
        }
        else {
            delete tempNode;
        }
        tempFile.open(root);
        tempNode = new Red_BlackNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        cout << "\033[91m";
        for (int i = 0; i < 120; i++) cout << '-';
        cout << endl << "\033[0m";
        cout << "\033[97m" << "Key is: " << "\033[92m" << tempNode->columnData.get_String() << endl;
        cout << "\033[97m" << "All Instance of this Key:- " << "\033[0m" << endl;
        for (int i = 0; i < tempNode->Row_Duplicates.getSize(); i++) {
            tempNode->Row_Duplicates.getElement(i).print();
            cout << endl;
        }
        cout << "\033[97m" << "Left Child: " << "\033[0m" << tempNode->leftChild << '\t' << "\033[97m" << "Right Child: " << "\033[0m" << tempNode->rightChild << endl;

        if (!tempNode->rightChild.empty()) {
            path tempPath = tempNode->rightChild;
            delete tempNode;
            InOrderTraversal(tempPath);
        }
        else {
            delete tempNode;
        }
    }

    void SearchTree(CustomString colData, path root) {
        fstream tempFile;
        tempFile.open(root);
        Red_BlackNode* tempNode = new Red_BlackNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        if (tempNode->columnData == colData) {
            cout << "\033[91m";
            for (int i = 0; i < 120; i++) cout << '-';
            cout << endl << "\033[0m";
            cout << "\033[97m" << "Key is: " << "\033[92m" << tempNode->columnData.get_String() << endl;
            cout << "\033[97m" << "All Instance of this Key:- " << "\033[0m" << endl;
            for (int i = 0; i < tempNode->Row_Duplicates.getSize(); i++) {
                tempNode->Row_Duplicates.getElement(i).print();
                cout << endl;
            }
            cout << "\033[97m" << "Left Child: " << "\033[0m" << tempNode->leftChild << '\t' << "\033[97m" << "Right Child: " << "\033[0m" << tempNode->rightChild << endl;
            delete tempNode;
            return;
        }
        if (tempNode->columnData < colData) {
            if (tempNode->rightChild.empty()) {
                cout << "\033[91m" << "ERROR : Key Not Found!" << "\033[0m";
                delete tempNode;
                return;
            }
            path tempPath = tempNode->rightChild;
            delete tempNode;
            SearchTree(colData, tempPath);
        }
        else {
            if (tempNode->leftChild.empty()) {
                cout << "\033[91m" << "ERROR : Key Not Found!" << "\033[0m";
                delete tempNode;
                return;
            }
            path tempPath = tempNode->leftChild;
            delete tempNode;
            SearchTree(colData, tempPath);
        }
    }

    void DeleteTree(CustomString& colData, path root) {
        fstream tempFile;
        tempFile.open(root);
        Red_BlackNode* tempNode = new Red_BlackNode;
        FileToNode(tempFile, *tempNode);
        tempFile.close();
        if (tempNode->columnData == colData) {
            cout << "\033[91m";
            for (int i = 0; i < 120; i++) cout << '-';
            cout << endl << "\033[0m";
            cout << "\033[97m" << "Key is: " << "\033[92m" << tempNode->columnData.get_String() << endl;
            cout << "\033[97m" << "All Instance of this Key:- " << "\033[0m" << endl;
            for (int i = 0; i < tempNode->Row_Duplicates.getSize(); i++) {
                cout << "\033[91m" << i << ": " << "\033[0m";
                tempNode->Row_Duplicates.getElement(i).print();
                cout << endl;
            }
            cout << "\033[97m" << "Left Child: " << "\033[0m" << tempNode->leftChild << '\t' << "\033[97m" << "Right Child: " << "\033[0m" << tempNode->rightChild << endl;
            cin.ignore();
            cout << "\nEnter Index : ";
            int index;
            cin >> index;
            CustomString str = tempNode->Row_Duplicates.getElement(index);
            delRowData(str);

            delete tempNode;
            return;
        }
        if (tempNode->columnData < colData) {
            if (tempNode->rightChild.empty()) {
                cout << "\033[91m" << "ERROR : Key Not Found!" << "\033[0m";
                delete tempNode;
                return;
            }
            path tempPath = tempNode->rightChild;
            delete tempNode;
            DeleteTree(colData, tempPath);
        }
        else {
            if (tempNode->leftChild.empty()) {
                cout << "\033[91m" << "ERROR : Key Not Found!" << "\033[0m";
                delete tempNode;
                return;
            }
            path tempPath = tempNode->leftChild;
            delete tempNode;
            DeleteTree(colData, tempPath);
        }
    }

public:


    Red_Black(path folderPath, path CSVFilePath, ColSelect ColS, merkilClass& merkil, commitClass& commit)
        : parentTree(folderPath, CSVFilePath, ColS, 1, merkil, commit) {

        fstream file;
        file.open(CSVFilePath);

#if _DEBUG //-----------------------------------
        if (!file.is_open()) {
            cerr << "Failed to open the CSV file.\n";
            int error;
            cin >> error;
            return;
        }
        else {
            cout << "File opened successfully.\n";
        }
#endif // _DEBUG ------------------------------

        CustomString thisRow;
        char sto[1000];
        file >> thisRow;
        //int i = 0;
        while (!file.eof()) {
            //if (i++ == 6)
            //	break;
            file.getline(sto, 1000);
            thisRow.setString(sto);
            if (thisRow.getSize() != 0) insert(thisRow);
        }
        cout << root;
        file.close();

        Stack<path> stack;
        InOrderTraversalMerkil(root, stack);
        merkil.makeMerkilTree(stack);
    }

    Red_Black(path folderPath, merkilClass& merkil, commitClass& commit) :parentTree(folderPath, merkil, commit) {

    }

    void insert(CustomString& row)
    {
        if (root.empty()) root = new_Red_BlackNode(row);
        else insertion(row, root);
    }

    void delRowData(CustomString& row) {
        if (root.empty()) return;
        else deleteRowData(row, root);

        CustomString str;
        str.setString("Deleted: ");
        str + row.get_String();
        commit.saveChanges(str);
    }

    void PrintTree() {
        InOrderTraversal(root);
    }

    void SearchTree(CustomString colData) {
        SearchTree(colData, root);
    }

    void DeleteTree(CustomString colData) {
        DeleteTree(colData, root);
    }

};

//class RBTree
//{
//
//	class Node
//	{
//	public:
//		int data = 0;
//		bool isBlack = false;
//		Node* left = nullptr;
//		Node* right = nullptr;
//		Node* parent = nullptr;
//		//some stuff might be added later
//
//		bool isOnLeft()
//		{
//			return (this == parent->left);
//		}
//
//		Node* uncle() {
//			// If no parent or grandparent, then no uncle
//			if (parent == NULL or parent->parent == NULL)
//				return NULL;
//
//			if (parent->isOnLeft())
//				return parent->parent->right;	//right uncle
//
//			else
//				return parent->parent->left;	// left unc
//
//		}
//
//		Node* sibling()
//		{
//			// sibling null
//			if (parent == NULL)
//				return NULL;
//
//			if (isOnLeft())
//				return parent->right;
//
//			return parent->left;
//		}
//
//		void TraverseNeg(Node* inp_Parent)
//		{
//			if (parent != NULL)
//			{
//				if (isOnLeft())
//					parent->left = inp_Parent;
//
//				else
//					parent->right = inp_Parent;
//			}
//			inp_Parent->parent = parent;
//			parent = inp_Parent;
//		}
//
//		bool RedChildPresent()
//		{
//			return (left != NULL and left->isBlack == false) || (right != NULL and right->isBlack == false);
//		}
//
//
//	};
//
//
//	Node* root = nullptr;
//	bool ll = 0, rr = 0, lr = 0, rl = 0;
//
//	Node* rotateLeft(Node* node)
//	{
//		Node* x = node->right;
//		Node* y = x->left;
//		x->left = node;
//		node->right = y;
//		node->parent = x;
//		if (y != nullptr)
//			y->parent = node;
//		return x;
//	}
//
//	Node* rotateRight(Node* node)
//	{
//		Node* x = node->left;
//		Node* y = x->right;
//		x->right = node;
//		node->left = y;
//		node->parent = x;
//		if (y != nullptr)
//			y->parent = node;
//		return x;
//	}
//
//	void rotateLeft_DEL(Node*& node)
//	{
//		Node* help_me_pls = node->right;
//
//		if (node == root)
//			root = help_me_pls;
//
//		node->TraverseNeg(help_me_pls);
//
//		node->right = help_me_pls->left;
//		if (help_me_pls->left != NULL)
//			help_me_pls->left->parent = node;
//
//		help_me_pls->left = node;
//	}
//
//	void rotateRight_DEL(Node*& node) {
//		Node* help = node->left;
//
//		if (node == root)
//			root = help;
//
//		node->TraverseNeg(help);
//
//		node->left = help->right;
//		if (help->right != NULL)
//			help->right->parent = node;
//
//		help->right = node;
//	}
//
//	Node* insertHelp(Node* root, int data)
//	{
//		bool f = false; //Red-Red check
//
//		if (root == nullptr)
//		{
//			Node* helper = new Node;
//			helper->data = data;
//			return helper;
//		}
//		else if (data < root->data)
//		{
//			root->left = insertHelp(root->left, data);
//			root->left->parent = root;
//			if (root != this->root)
//			{
//				if (root->isBlack == false && root->left->isBlack == false)
//					f = true;
//			}
//		}
//		else
//		{
//			root->right = insertHelp(root->right, data);
//			root->right->parent = root;
//			if (root != this->root)
//			{
//				if (root->isBlack == false && root->right->isBlack == false)
//					f = true;
//			}
//		}
//
//		// Perform rotations
//		if (ll)
//		{
//			root = rotateLeft(root);
//			root->isBlack = true;
//			root->left->isBlack = false;
//			ll = false;
//		}
//		else if (rr)
//		{
//			root = rotateRight(root);
//			root->isBlack = true;
//			root->right->isBlack = false;
//			rr = false;
//		}
//		else if (rl)
//		{
//			root->right = rotateRight(root->right);
//			root->right->parent = root;
//			root = rotateLeft(root);
//			root->isBlack = true;
//			root->left->isBlack = false;
//			rl = false;
//		}
//		else if (lr)
//		{
//			root->left = rotateLeft(root->left);
//			root->left->parent = root;
//			root = rotateRight(root);
//			root->isBlack = true;
//			root->right->isBlack = false;
//			lr = false;
//		}
//
//		// Handle RED-RED conflicts
//		if (f)
//		{
//			if (root->parent->right == root)
//			{
//				if (root->parent->left == nullptr || root->parent->left->isBlack == true)
//				{
//					if (root->left != nullptr && root->left->isBlack == false)
//						rl = true;
//					else if (root->right != nullptr && root->right->isBlack == false)
//						ll = true;
//				}
//				else
//				{
//					root->parent->left->isBlack = true;
//					root->isBlack = true;
//					if (root->parent != this->root)
//						root->parent->isBlack = false;
//				}
//			}
//			else
//			{
//				if (root->parent->right == nullptr || root->parent->right->isBlack == true)
//				{
//					if (root->left != nullptr && root->left->isBlack == false)
//						rr = true;
//					else if (root->right != nullptr && root->right->isBlack == false)
//						lr = true;
//				}
//				else
//				{
//					root->parent->right->isBlack = true;
//					root->isBlack = true;
//					if (root->parent != this->root)
//						root->parent->isBlack = false;
//				}
//			}
//			f = false;
//		}
//		return root;
//	}
//
//	void inorderTraversalHelper(Node* node)
//	{
//		if (node != nullptr)
//		{
//			inorderTraversalHelper(node->left);
//			std::cout << node->data << " ";
//			inorderTraversalHelper(node->right);
//		}
//	}
//
//	void swapColors(Node*& x1, Node*& x2)
//	{
//		bool b = 0;
//		b = x1->isBlack;
//		x1->isBlack = x2->isBlack;
//		x2->isBlack = b;
//	}
//
//	void swapValues(Node*& inp1, Node*& inp2)
//	{
//		int temp = 0;
//		temp = inp1->data;
//		inp1->data = inp2->data;
//		inp2->data = temp;
//	}
//
//	void fixRedRed(Node*& x)
//	{
//		if (x == root)x->isBlack = true;
//	}
//
//	Node* successor(Node* x)
//	{
//		Node* temp = x;
//		while (temp->left != NULL)
//			temp = temp->left;
//		return temp;
//	}
//
//	Node* BSTreplace(Node* x)
//	{
//		if (x->left != NULL and x->right != NULL)
//			return successor(x->right);
//
//		if (x->left == NULL and x->right == NULL)
//			return NULL;
//
//		if (x->left != NULL)
//			return x->left;
//
//		else
//			return x->right;
//	}
//
//	void deleteNode(Node* inp)
//	{
//		Node* helper = BSTreplace(inp);
//
//		bool check_Black = ((helper == NULL || helper->isBlack == true) && (inp->isBlack == true));
//		Node* parent = inp->parent;
//
//		if (helper == NULL)
//		{
//			if (inp == root)
//				root = NULL;
//
//			else
//			{
//				if (check_Black)
//					fixDoubleBlack(inp);
//
//				else
//				{
//					if (inp->sibling() != NULL)
//						inp->sibling()->isBlack = false;
//				}
//
//				if (inp->isOnLeft())
//				{
//					parent->left = NULL;
//				}
//				else
//				{
//					parent->right = NULL;
//				}
//			}
//			delete inp;
//			return;
//		}
//
//		if (inp->left == NULL or inp->right == NULL)
//		{
//
//			if (inp == root)
//			{
//				inp->data = helper->data;
//				inp->left = inp->right = NULL;
//				delete helper;
//			}
//			else
//			{
//
//				if (inp->isOnLeft())
//					parent->left = helper;
//				else
//					parent->right = helper;
//
//				delete inp;
//				helper->parent = parent;
//
//				if (check_Black)
//					fixDoubleBlack(helper);
//				else
//					helper->isBlack = true;
//			}
//			return;
//		}
//
//		swapValues(helper, inp);
//		deleteNode(helper);
//	}
//
//	void fixDoubleBlack(Node* x)
//	{
//		if (x == root)
//			return;
//		Node* sibling = x->sibling(), * parent = x->parent;
//
//		if (sibling == NULL)
//
//			fixDoubleBlack(parent);
//
//		else
//		{
//			if (sibling->isBlack == false)
//			{
//				parent->isBlack = false;
//				sibling->isBlack = true;
//				if (sibling->isOnLeft())
//					rotateLeft_DEL(parent);
//				else
//					rotateLeft_DEL(parent);
//				fixDoubleBlack(x);
//			}
//			else
//			{
//				// Sibling black
//				if (sibling->RedChildPresent())
//				{
//					// at least 1 red children
//					if (sibling->left != NULL && sibling->left->isBlack == false)
//					{
//						if (sibling->isOnLeft())
//						{
//							sibling->left->isBlack = sibling->isBlack;
//							sibling->isBlack = parent->isBlack;
//							rotateRight_DEL(parent);
//						}
//						else
//						{
//							sibling->left->isBlack = parent->isBlack;
//							rotateRight_DEL(sibling);
//							rotateLeft_DEL(parent);
//						}
//					}
//					else
//					{
//						if (sibling->isOnLeft())
//						{
//							sibling->right->isBlack = parent->isBlack;
//							rotateLeft_DEL(sibling);
//							rotateRight_DEL(parent);
//						}
//						else
//						{
//							sibling->right->isBlack = sibling->isBlack;
//							sibling->isBlack = parent->isBlack;
//							rotateLeft_DEL(parent);
//						}
//					}
//					parent->isBlack = true;
//				}
//				else {
//					// 2 black children
//					sibling->isBlack = false;
//					if (parent->isBlack == true)
//						fixDoubleBlack(parent);
//					else
//						parent->isBlack = true;
//				}
//			}
//		}
//	}
//
//	Node* search(int n)
//	{
//		Node* temp = root;
//		while (temp != NULL) {
//			if (n < temp->data) {
//				if (temp->left == NULL)
//					break;
//				else
//					temp = temp->left;
//			}
//			else if (n == temp->data) {
//				break;
//			}
//			else {
//				if (temp->right == NULL)
//					break;
//				else
//					temp = temp->right;
//			}
//		}
//
//		return temp;
//	}
//
//public:
//
//	void insert(int data)
//	{
//		if (root == nullptr)
//		{
//			root = new Node;
//			root->data = data;
//			root->isBlack = true;
//		}
//		else
//			root = insertHelp(root, data);
//	}
//
//	void deleteByVal(int n)
//	{
//		if (root == NULL)
//			// Tree is empty
//			return;
//
//		Node* h = search(n);
//
//		if (h->data != n) {
//			cout << "No such node found\n";
//			return;
//		}
//
//		deleteNode(h);
//	}
//
//	void inorderTraversal()
//	{
//		inorderTraversalHelper(root);
//	}
//
//};
//
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<TREEs>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

class VersionControlSystem {
    parentTree* Tree = nullptr;
    path thisRepoPath;
    path thisBranchPath;
    commitClass commit;
    merkilClass merkil;


    void gotoxy(int x, int y)
    {
        COORD c = { x, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }

    bool RepoMenuScreen(path& repositoryPath) {
        int screen = 1;
        int totalLines = 30;
        int totalChars = 118;
        HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console
        DWORD Events = 0;     // Event count
        DWORD EventsRead = 0; // Events read from console
        bool runing = 1;
        int option = 1;
        system("cls");

        // Draw left vertical border
        for (int i = 0; i < totalLines; i++) {
            gotoxy(0, i);
            cout << "|-";
        }
        // Draw right vertical border
        for (int i = 0; i < totalLines; i++) {
            gotoxy(totalChars, i);
            cout << '-' << '|';
        }
        // Draw top horizontal border
        for (int i = 2; i <= totalChars - 1; i++) {
            gotoxy(i, 0);
            cout << '-';
        }
        // Draw bottom horizontal border
        for (int i = 2; i <= totalChars - 1; i++) {
            gotoxy(i, totalLines - 1);
            cout << '-';
        }
        cout << "\033[96m";
        gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2);     cout << "             ___       ___  ___   _    _   ___    ";
        gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 1); cout << "   |      | |    |    |    |   | | \\  / | |       ";
        gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 2); cout << "   |  /\\  | |--- |    |    |   | |  \\/  | |---    ";
        gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 3); cout << "   |_/  \\_| |___ |___ |___ |___| |      | |___    ";
        gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 5); cout << "                   TO GIT-LITE";
        cout << "\033[0m";

        gotoxy(((totalChars - 14) / 2), (totalLines - 12) / 2 + 10); cout << "\033[97m" << "INITIALIZATION" << "\033[0m";

        gotoxy((totalChars - 26) / 2, totalLines - 2); cout << "\033[97m" << "*Press any key to continue" << "\033[0m";

        while (runing) {
            GetNumberOfConsoleInputEvents(rhnd, &Events);
            if (Events != 0) { // if something happened we will handle the events we want
                INPUT_RECORD eventBuffer[500]; // create event buffer the size of how many Events
                ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead); // fills the event buffer with the events and saves count in EventsRead


                if (option == 1) {
                    gotoxy((totalChars - 35) / 2, (totalLines - 12) / 2 + 8); cout << " [Load From Existing Repositories] ";
                    gotoxy((totalChars - 35) / 2, (totalLines - 12) / 2 + 9); cout << "       Create New Repository       ";
                    gotoxy((totalChars - 35) / 2, (totalLines - 12) / 2 + 10); cout << "               Exit                ";
                }
                else if (option == 2) {
                    gotoxy((totalChars - 35) / 2, (totalLines - 12) / 2 + 8); cout << "  Load From Existing Repositories  ";
                    gotoxy((totalChars - 35) / 2, (totalLines - 12) / 2 + 9); cout << "      [Create New Repository]      ";
                    gotoxy((totalChars - 35) / 2, (totalLines - 12) / 2 + 10); cout << "               Exit                ";
                }
                else if (option == 3) {
                    gotoxy((totalChars - 35) / 2, (totalLines - 12) / 2 + 8); cout << "  Load From Existing Repositories  ";
                    gotoxy((totalChars - 35) / 2, (totalLines - 12) / 2 + 9); cout << "       Create New Repository       ";
                    gotoxy((totalChars - 35) / 2, (totalLines - 12) / 2 + 10); cout << "              [Exit]               ";
                }

                gotoxy((totalChars - 36) / 2, totalLines - 2); cout << "\033[97m" << "*Press 'Enter' to select your option" << "\033[0m";

                for (DWORD i = 0; i < EventsRead; ++i) {
                    if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {
                        switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {

                        case VK_UP: //up
                            if (option != 1) option--;
                            else  option = 3;
                            break;
                        case VK_DOWN: //down
                            if (option != 3) option++;
                            else option = 1;
                            break;
                        case VK_RIGHT: //right
                            if (option != 3) option++;
                            else option = 1;
                            break;
                        case VK_LEFT: //left
                            if (option != 1) option--;
                            else option = 3;
                            break;

                        case VK_RETURN: // Enter key
                            gotoxy(2, (totalLines - 12) / 2 + 11); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 10); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 9); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 8); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            runing = 0;
                            if (option == 3) return 0;
                            break;
                        }
                    }
                }
            }
        }

        gotoxy((totalChars - 36) / 2, totalLines - 2); cout << "                                    ";
        gotoxy(2, (totalLines - 12) / 2 + 8); for (int i = 0; i < totalChars - 4; i++) cout << ' ';

        while (screen) {
            gotoxy(2, (totalLines - 12) / 2 + 8); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
            if (screen == 2) { gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 8); cout << "\033[91m" << "          ERROR : REPOSITORY NOT FOUND! " << "\033[0m"; }
            if (screen == 3) { gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 8); cout << "\033[91m" << "       ERROR : REPOSITORY ALREADY EXISTS! " << "\033[0m";; }
            if (screen) { gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 9); cout << "      Enter name of your repository : "; }
            cin >> repositoryPath;
            if (option == 1) {
                if (exists(repositoryPath)) {
                    thisRepoPath = repositoryPath;
                    gotoxy(2, (totalLines - 12) / 2 + 8); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                    gotoxy(2, (totalLines - 12) / 2 + 9); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                    path branchPath, tempPath;
                    screen = 1;
                    while (screen) {
                        gotoxy(2, (totalLines - 12) / 2 + 8); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                        if (screen == 2) { gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 8); cout << "\033[91m" << "            ERROR : BRANCH NOT FOUND!     " << "\033[0m"; }
                        if (screen) { gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 9); cout << "      Enter name of branch to load : "; }
                        cin >> tempPath;
                        branchPath = repositoryPath;
                        branchPath /= tempPath;
                        if (exists(branchPath)) {
                            tempPath = branchPath;
                            thisBranchPath = branchPath;
                            tempPath /= "TREE\\metadata.txt";
                            fstream metaFile;
                            metaFile.open(tempPath, ios::in);
                            int treeType;
                            metaFile >> treeType;
                            metaFile.close();

                            tempPath = branchPath;
                            tempPath /= "TREE";
                            if (treeType == 1) {
                                Tree = new AVL(tempPath, merkil, commit);
                            }
                            else if (treeType == 2) {
                                Tree = new Red_Black(tempPath, merkil, commit);
                            }
                            else if (treeType == 3) {
                                cout << "Enter Minimum Degree : ";
                                int minDeg;
                                cin >> minDeg;
                                Tree = new BTree(minDeg, tempPath, merkil, commit);
                            }
                            screen = 0;
                        }
                        else {
                            screen = 2;
                        }
                    }
                }
                else {
                    screen = 2;
                }
            }
            else {
                if (exists(repositoryPath)) {
                    screen = 3;
                    continue;
                }
                //BELOW I WILL BE CREATING ALL THE FILES AND PATHS ------------------
                create_directory(repositoryPath);
                thisRepoPath = repositoryPath;
                path branchPath = repositoryPath;
                branchPath /= "MASTER";
                create_directory(branchPath);
                thisBranchPath = branchPath;
                path branchMetaPath = branchPath;
                branchMetaPath /= "metadata.txt";
                fstream branchMetaFile;
                path folderPath = branchPath;
                folderPath /= "TREE";
                create_directory(folderPath);
                path merkilPath = branchPath;
                merkilPath /= "MERKIL";
                create_directory(merkilPath);
                merkil.setFolderPath(merkilPath);
                path treeMetaPath = folderPath;
                treeMetaPath /= "metadata.txt";
                fstream treeMetaFile;
                path folderPath2 = branchPath;
                folderPath2 /= "COMMIT";
                create_directory(folderPath2);
                commit.setFolderPath(folderPath2);
                //-----------------------------------------------------------------------
                if (exists(repositoryPath) && exists(branchPath)) {
                    gotoxy((totalChars - 35) / 2, (totalLines - 13) / 2 + 11);
                    cout << "\033[32m" << "Repostory is ensured to be created!" << "\033[0m" << endl;
                }
                else {
                    gotoxy((totalChars - 27) / 2, (totalLines - 13) / 2 + 11);
                    cout << "\033[91m" << "Error in creating Repostory" << "\033[0m" << endl;
                    return 0;
                }
                screen = 0;

                gotoxy((totalChars - 36) / 2, totalLines - 2); cout << "                                    ";
                gotoxy(2, (totalLines - 12) / 2 + 8); for (int i = 0; i < totalChars - 4; i++) cout << ' ';


                gotoxy((totalChars - 32) / 2, totalLines - 2); cout << "\033[91m" << "*Press any key to select tree" << "\033[0m";
                runing = 1;
                path CSVFilePath; ColSelect ColS;
                option = 1;
                while (runing) {
                    GetNumberOfConsoleInputEvents(rhnd, &Events);
                    if (Events != 0) { // if something happened we will handle the events we want
                        INPUT_RECORD eventBuffer[500]; // create event buffer the size of how many Events
                        ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead); // fills the event buffer with the events and saves count in EventsRead

                        gotoxy(2, (totalLines - 12) / 2 + 9); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                        if (option == 1) {
                            gotoxy((totalChars - 37) / 2, (totalLines - 12) / 2 + 8);  cout << "              >AVL Tree<               ";
                            gotoxy((totalChars - 37) / 2, (totalLines - 12) / 2 + 9);  cout << "            Red Black Tree             ";
                            gotoxy((totalChars - 37) / 2, (totalLines - 12) / 2 + 10); cout << "                B-Tree                 ";
                        }
                        else if (option == 2) {
                            gotoxy((totalChars - 37) / 2, (totalLines - 12) / 2 + 8);  cout << "               AVL Tree                ";
                            gotoxy((totalChars - 37) / 2, (totalLines - 12) / 2 + 9);  cout << "           >Red Black Tree<            ";
                            gotoxy((totalChars - 37) / 2, (totalLines - 12) / 2 + 10); cout << "                B-Tree                 ";
                        }
                        else if (option == 3) {
                            gotoxy((totalChars - 37) / 2, (totalLines - 12) / 2 + 8);  cout << "               AVL Tree                ";
                            gotoxy((totalChars - 37) / 2, (totalLines - 12) / 2 + 9);  cout << "            Red Black Tree             ";
                            gotoxy((totalChars - 37) / 2, (totalLines - 12) / 2 + 10); cout << "               >B-Tree<                ";
                        }
                        gotoxy((totalChars - 36) / 2, totalLines - 2); cout << "\033[97m" << "*Press 'Enter' to select your option" << "\033[0m";

                        for (DWORD i = 0; i < EventsRead; ++i) {
                            if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {
                                switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {

                                case VK_UP: //up
                                    if (option != 1) option--;
                                    else  option = 3;
                                    break;
                                case VK_DOWN: //down
                                    if (option != 3) option++;
                                    else option = 1;
                                    break;
                                case VK_RIGHT: //right
                                    if (option != 3) option++;
                                    else option = 1;
                                    break;
                                case VK_LEFT: //left
                                    if (option != 1) option--;
                                    else option = 3;
                                    break;
                                case VK_RETURN: // Enter key
                                    gotoxy(2, (totalLines - 12) / 2 + 11); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                                    gotoxy(2, (totalLines - 12) / 2 + 10); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                                    gotoxy(2, (totalLines - 12) / 2 + 9); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                                    gotoxy(2, (totalLines - 12) / 2 + 8); for (int i = 0; i < totalChars - 4; i++) cout << ' ';

                                    gotoxy((totalChars - 25) / 2, (totalLines - 12) / 2 + 9); cout << "   Enter your CSV File : ";
                                    cin >> CSVFilePath;

                                    system("cls");
                                    DisplayFisrtRow(ColS, CSVFilePath);

                                    branchMetaFile.open(branchMetaPath, ios::out);
                                    treeMetaFile.open(treeMetaPath, ios::out);
                                    if (option == 1) {
                                        Tree = new AVL(folderPath, CSVFilePath, ColS, merkil, commit);
                                    }
                                    branchMetaFile.close();
                                    treeMetaFile.close();
                                    runing = 0;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        return 1;
    }

    bool MainMenu() {
        int totalLines = 30;
        int totalChars = 118;
        HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console
        DWORD Events = 0;     // Event count
        DWORD EventsRead = 0; // Events read from console
        bool runing = 1;
        int option = 1;
        system("cls");
        // Draw left vertical border
        for (int i = 0; i < totalLines; i++) {
            gotoxy(0, i);
            cout << "|-";
        }
        // Draw right vertical border
        for (int i = 0; i < totalLines; i++) {
            gotoxy(totalChars, i);
            cout << '-' << '|';
        }
        // Draw top horizontal border
        for (int i = 2; i <= totalChars - 1; i++) {
            gotoxy(i, 0);
            cout << '-';
        }
        // Draw bottom horizontal border
        for (int i = 2; i <= totalChars - 1; i++) {
            gotoxy(i, totalLines - 1);
            cout << '-';
        }
        cout << "\033[94m";
        gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2);     cout << "     ____ _____ _____   .     _____ _____ .___    ";
        gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 1); cout << "    |       |     |     |       |     |   |       ";
        gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 2); cout << "    |  __   |     |     |       |     |   |---    ";
        gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 3); cout << "    |___| __|__   |     |____ __|__   |   |___    ";
        gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 5); cout << "     BY: AHMED-ASIM _ NASIR-BILAL _ ALI-SHER";
        cout << "\033[0m";
        gotoxy(((totalChars - 9) / 2), (totalLines - 12) / 2 + 10); cout << "\033[97m" << "MAIN MENU" << "\033[0m";
        gotoxy((totalChars - 26) / 2, totalLines - 2); cout << "\033[97m" << "*Press any key to continue" << "\033[0m";

        while (runing) {
            GetNumberOfConsoleInputEvents(rhnd, &Events);
            if (Events != 0) { // if something happened we will handle the events we want
                INPUT_RECORD eventBuffer[500]; // create event buffer the size of how many Events
                ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead); // fills the event buffer with the events and saves count in EventsRead

                if (option == 1) {
                    gotoxy((totalChars - 22) / 2, (totalLines - 12) / 2 + 8); cout << ">Tree Functionalities<";
                    gotoxy((totalChars - 22) / 2, (totalLines - 12) / 2 + 9); cout << " Git Functionalities  ";
                    gotoxy((totalChars - 22) / 2, (totalLines - 12) / 2 + 10); cout << "         Exit         ";
                }
                else if (option == 2) {
                    gotoxy((totalChars - 22) / 2, (totalLines - 12) / 2 + 8); cout << " Tree Functionalities ";
                    gotoxy((totalChars - 22) / 2, (totalLines - 12) / 2 + 9); cout << ">Git Functionalities< ";
                    gotoxy((totalChars - 22) / 2, (totalLines - 12) / 2 + 10); cout << "         Exit         ";
                }
                else if (option == 3) {
                    gotoxy((totalChars - 22) / 2, (totalLines - 12) / 2 + 8); cout << " Tree Functionalities ";
                    gotoxy((totalChars - 22) / 2, (totalLines - 12) / 2 + 9); cout << " Git Functionalities  ";
                    gotoxy((totalChars - 22) / 2, (totalLines - 12) / 2 + 10); cout << "        >Exit<        ";
                }
                gotoxy((totalChars - 36) / 2, totalLines - 2); cout << "\033[97m" << "*Press 'Enter' to select your option" << "\033[0m";

                for (DWORD i = 0; i < EventsRead; ++i) {
                    if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {
                        switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {

                        case VK_UP: //up
                            if (option != 1) option--;
                            else  option = 3;
                            break;
                        case VK_DOWN: //down
                            if (option != 3) option++;
                            else option = 1;
                            break;
                        case VK_RIGHT: //right
                            if (option != 3) option++;
                            else option = 1;
                            break;
                        case VK_LEFT: //left
                            if (option != 1) option--;
                            else option = 3;
                            break;
                        case VK_RETURN: // Enter key
                            gotoxy(2, (totalLines - 12) / 2 + 11); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 10); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 9); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 8); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            if (option == 3) return 0;
                            else if (option == 2) {
                                while (GitMenu());
                            }
                            else if (option == 1) {
                                while (TreeMenu());
                            }
                            runing = 0;
                            break;
                        }
                    }
                }
            }
        }
        return 1;
    }

    bool TreeMenu() {
        int totalLines = 30;
        int totalChars = 118;
        HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console
        DWORD Events = 0;     // Event count
        DWORD EventsRead = 0; // Events read from console
        bool runing = 1;
        int option = 1;
        system("cls");
        // Draw left vertical border
        for (int i = 0; i < totalLines; i++) {
            gotoxy(0, i);
            cout << "|-";
        }
        // Draw right vertical border
        for (int i = 0; i < totalLines; i++) {
            gotoxy(totalChars, i);
            cout << '-' << '|';
        }
        // Draw top horizontal border
        for (int i = 2; i <= totalChars - 1; i++) {
            gotoxy(i, 0);
            cout << '-';
        }
        // Draw bottom horizontal border
        for (int i = 2; i <= totalChars - 1; i++) {
            gotoxy(i, totalLines - 1);
            cout << '-';
        }
        cout << "\033[92m";
        gotoxy((totalChars - 50) / 2, 6);     cout << "     ____ _____ _____   .     _____ _____ .___    ";
        gotoxy((totalChars - 50) / 2, 6 + 1); cout << "    |       |     |     |       |     |   |       ";
        gotoxy((totalChars - 50) / 2, 6 + 2); cout << "    |  __   |     |     |       |     |   |---    ";
        gotoxy((totalChars - 50) / 2, 6 + 3); cout << "    |___| __|__   |     |____ __|__   |   |___    ";
        gotoxy((totalChars - 50) / 2, 6 + 5); cout << "     BY: AHMED-ASIM _ NASIR-BILAL _ ALI-SHER";
        cout << "\033[0m";
        gotoxy((totalChars - 26) / 2, totalLines - 2); cout << "\033[97m" << "*Press any key to continue" << "\033[0m";

        gotoxy(((totalChars - 20) / 2), (totalLines - 12) / 2 + 10); cout << "\033[97m" << "TREE FUNCTIONALITIES" << "\033[0m";

        while (runing) {
            GetNumberOfConsoleInputEvents(rhnd, &Events);
            if (Events != 0) { // if something happened we will handle the events we want
                INPUT_RECORD eventBuffer[500]; // create event buffer the size of how many Events
                ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead); // fills the event buffer with the events and saves count in EventsRead

                gotoxy(2, (totalLines - 12) / 2 + 10); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                if (option == 1) {
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 8);  cout << "  >Print Tree<  ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 9);  cout << " Search in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 10); cout << " Insert in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 11); cout << " Delete in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 12); cout << "      Exit      ";
                }
                else if (option == 2) {
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 8);  cout << "   Print Tree   ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 9);  cout << ">Search in Tree<";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 10); cout << " Insert in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 11); cout << " Delete in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 12); cout << "      Exit      ";
                }
                else if (option == 3) {
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 8);  cout << "   Print Tree   ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 9);  cout << " Search in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 10); cout << ">Insert in Tree<";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 11); cout << " Delete in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 12); cout << "      Exit      ";
                }
                else if (option == 4) {
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 8);  cout << "   Print Tree   ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 9);  cout << " Search in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 10); cout << " Insert in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 11); cout << ">Delete in Tree<";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 12); cout << "      Exit      ";
                }
                else if (option == 5) {
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 8);  cout << "   Print Tree   ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 9);  cout << " Search in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 10); cout << " Insert in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 11); cout << " Delete in Tree ";
                    gotoxy((totalChars - 16) / 2, (totalLines - 12) / 2 + 12); cout << "     >Exit<     ";
                }
                gotoxy((totalChars - 36) / 2, totalLines - 2); cout << "\033[97m" << "*Press 'Enter' to select your option" << "\033[0m";

                for (DWORD i = 0; i < EventsRead; ++i) {
                    if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {
                        switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {

                        case VK_UP: //up
                            if (option != 1) option--;
                            else  option = 5;
                            break;
                        case VK_DOWN: //down
                            if (option != 5) option++;
                            else option = 1;
                            break;
                        case VK_RIGHT: //right
                            if (option != 5) option++;
                            else option = 1;
                            break;
                        case VK_LEFT: //left
                            if (option != 1) option--;
                            else option = 5;
                            break;
                        case VK_RETURN: // Enter key
                            gotoxy(2, (totalLines - 12) / 2 + 8);  for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 9);  for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 10); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 11); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 12); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            if (option == 5) return 0;
                            else if (option == 1) {
                                system("cls");
                                Tree->PrintTree();
                                cout << '\n' << "Enter any character to continue : ";
                                char ch;
                                cin >> ch;
                                cin.ignore();
                            }
                            else if (option == 2) {
                                { gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 9); cout << "      Enter Key that you want to search : "; }
                                CustomString colData;
                                cin >> colData;
                                cin.ignore();
                                system("cls");
                                Tree->SearchTree(colData);
                                cout << '\n' << "Enter any character to continue : ";
                                char ch;
                                cin >> ch;
                                cin.ignore();
                            }
                            else if (option == 3) {
                                system("cls");
                                CustomString str;
                                TakeDataInput(str, Tree->CSVFilePath);
                                str.changetoComa();
                                CustomString str2;
                                str2.setString("Inserted: ");
                                str2 + str.get_String();
                                commit.saveChanges(str2);
                                Tree->insert(str);
                            }
                            else if (option == 4) {
                                { gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 9); cout << "      Enter Key that you want to delete : "; }
                                CustomString colData;
                                cin >> colData;
                                system("cls");
                                Tree->DeleteTree(colData);
                                cout << '\n' << "Enter any character to continue : ";
                                char ch;
                                cin >> ch;
                                cin.ignore();
                            }
                            runing = 0;
                            break;
                        case VK_ESCAPE:
                            break;
                        }
                    }
                }
            }
        }
        return 1;
    }

    bool GitMenu() {
        int totalLines = 30;
        int totalChars = 118;
        HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console
        DWORD Events = 0;     // Event count
        DWORD EventsRead = 0; // Events read from console
        bool runing = 1;
        int option = 1;
        system("cls");
        // Draw left vertical border
        for (int i = 0; i < totalLines; i++) {
            gotoxy(0, i);
            cout << "|-";
        }
        // Draw right vertical border
        for (int i = 0; i < totalLines; i++) {
            gotoxy(totalChars, i);
            cout << '-' << '|';
        }
        // Draw top horizontal border
        for (int i = 2; i <= totalChars - 1; i++) {
            gotoxy(i, 0);
            cout << '-';
        }
        // Draw bottom horizontal border
        for (int i = 2; i <= totalChars - 1; i++) {
            gotoxy(i, totalLines - 1);
            cout << '-';
        }
        cout << "\033[93m";
        gotoxy((totalChars - 50) / 2, 6);     cout << "     ____ _____ _____   .     _____ _____ .___    ";
        gotoxy((totalChars - 50) / 2, 6 + 1); cout << "    |       |     |     |       |     |   |       ";
        gotoxy((totalChars - 50) / 2, 6 + 2); cout << "    |  __   |     |     |       |     |   |---    ";
        gotoxy((totalChars - 50) / 2, 6 + 3); cout << "    |___| __|__   |     |____ __|__   |   |___    ";
        gotoxy((totalChars - 50) / 2, 6 + 5); cout << "     BY: AHMED-ASIM _ NASIR-BILAL _ ALI-SHER";
        cout << "\033[0m";
        gotoxy(((totalChars - 19) / 2), (totalLines - 12) / 2 + 10); cout << "\033[97m" << "GIT FUNCTIONALITIES" << "\033[0m";
        gotoxy((totalChars - 26) / 2, totalLines - 2); cout << "\033[97m" << "*Press any key to continue" << "\033[0m";
        while (runing) {
            GetNumberOfConsoleInputEvents(rhnd, &Events);
            if (Events != 0) { // if something happened we will handle the events we want
                INPUT_RECORD eventBuffer[500]; // create event buffer the size of how many Events
                ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead); // fills the event buffer with the events and saves count in EventsRea
                gotoxy(2, (totalLines - 12) / 2 + 10); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                if (option == 1) {
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 8);  cout << " >New Branch< ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 9);  cout << "   Checkout   ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 10); cout << "    Merge     ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 11); cout << "  Commit log  ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 12); cout << "    Commit    ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 13); cout << "     Exit     ";
                }
                else if (option == 2) {
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 8);  cout << "  New Branch  ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 9);  cout << "  >Checkout<  ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 10); cout << "    Merge     ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 11); cout << "  Commit log  ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 12); cout << "    Commit    ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 13); cout << "     Exit     ";
                }
                else if (option == 3) {
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 8); cout << "  New Branch  ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 9); cout << "   Checkout   ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 10); cout << "   >Merge<    ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 11); cout << "  Commit log  ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 12); cout << "    Commit    ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 13); cout << "     Exit     ";
                }
                else if (option == 4) {
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 8);  cout << "  New Branch  ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 9);  cout << "   Checkout   ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 10); cout << "    Merge     ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 11); cout << " >Commit log< ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 12); cout << "    Commit    ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 13); cout << "     Exit     ";
                }
                else if (option == 5) {
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 8);  cout << "  New Branch  ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 9);  cout << "   Checkout   ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 10); cout << "    Merge     ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 11); cout << "  Commit log  ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 12); cout << "   >Commit<   ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 13); cout << "     Exit     ";
                }
                else if (option == 6) {
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 8);  cout << "  New Branch  ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 9);  cout << "   Checkout   ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 10); cout << "    Merge     ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 11); cout << "  Commit log  ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 12); cout << "    Commit    ";
                    gotoxy((totalChars - 13) / 2, (totalLines - 12) / 2 + 13); cout << "    >Exit<    ";
                }
                gotoxy((totalChars - 36) / 2, totalLines - 2); cout << "\033[97m" << "*Press 'Enter' to select your option" << "\033[0m";
                for (DWORD i = 0; i < EventsRead; ++i) {
                    if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {
                        switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {
                        case VK_UP: //up
                            if (option != 1) option--;
                            else  option = 6;
                            break;
                        case VK_DOWN: //down
                            if (option != 6) option++;
                            else option = 1;
                            break;
                        case VK_RIGHT: //right
                            if (option != 6) option++;
                            else option = 1;
                            break;
                        case VK_LEFT: //left
                            if (option != 1) option--;
                            else option = 6;
                            break;
                        case VK_RETURN: // Enter key
                            gotoxy(2, (totalLines - 12) / 2 + 13); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 12); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 11); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 10); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 9); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            gotoxy(2, (totalLines - 12) / 2 + 8); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                            if (option == 6) return 0;
                            else if (option == 5) {
                                char sto[1000];
                                CustomString str;
                                gotoxy((totalChars - 34) / 2, (totalLines - 12) / 2 + 9);
                                cout << "Enter a message to commit : ";
                                cin.getline(sto, 1000);
                                str.setString(sto);
                                commit.commitChanges(str);
                            }
                            else if (option == 4) {
                                system("cls");
                                commit.displayLog();
                                cout << '\n' << "Enter any character to continue : ";
                                char ch;
                                cin >> ch;
                                cin.ignore();
                            }
                            else if (option == 2) {
                                delete Tree;
                                path branchPath, tempPath;
                                int screen = 1;
                                while (screen) {
                                    gotoxy(2, (totalLines - 12) / 2 + 8); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                                    if (screen == 2) { gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 8); cout << "\033[91m" << "            ERROR : BRANCH NOT FOUND!     " << "\033[0m"; }
                                    if (screen) { gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 9); cout << "      Enter name of branch to load : "; }
                                    cin >> tempPath;
                                    branchPath = thisRepoPath;
                                    branchPath /= tempPath;
                                    if (exists(branchPath)) {
                                        tempPath = branchPath;
                                        thisBranchPath = branchPath;
                                        tempPath /= "TREE\\metadata.txt";
                                        fstream metaFile;
                                        metaFile.open(tempPath, ios::in);
                                        int treeType;
                                        metaFile >> treeType;
                                        metaFile.close();

                                        tempPath = branchPath;
                                        tempPath /= "TREE";
                                        if (treeType == 1) {
                                            Tree = new AVL(tempPath, merkil, commit);
                                        }
                                        else if (treeType == 2) {
                                            Tree = new Red_Black(tempPath, merkil, commit);
                                        }
                                        else if (treeType == 3) {
                                            cout << "Enter Minimum Degree : ";
                                            int minDeg;
                                            cin >> minDeg;
                                            Tree = new BTree(minDeg, tempPath, merkil, commit);
                                        }
                                        screen = 0;
                                    }
                                    else {
                                        screen = 2;
                                    }
                                }
                            }
                            else if (option == 1) {
                                delete Tree;
                                path branchPath, tempPath;
                                int screen = 1;
                                while (screen) {
                                    gotoxy(2, (totalLines - 12) / 2 + 8); for (int i = 0; i < totalChars - 4; i++) cout << ' ';
                                    if (screen == 2) { gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 8); cout << "\033[91m" << "            ERROR : BRANCH ALREADY EXISTS!     " << "\033[0m"; }
                                    if (screen) { gotoxy((totalChars - 50) / 2, (totalLines - 12) / 2 + 9); cout << "      Enter name of branch to make : "; }
                                    cin >> tempPath;
                                    branchPath = thisRepoPath;
                                    branchPath /= tempPath;
                                    if (!exists(branchPath)) {
                                        copy(thisBranchPath, branchPath, copy_options::recursive);
                                        tempPath = branchPath;
                                        thisBranchPath = branchPath;
                                        tempPath /= "TREE\\metadata.txt";
                                        fstream metaFile;
                                        metaFile.open(tempPath, ios::in);
                                        int treeType;
                                        metaFile >> treeType;
                                        metaFile.close();

                                        path merkilPath = branchPath;
                                        merkilPath /= "MERKIL";
                                        merkil.setFolderPath(merkilPath);

                                        path folderPath2 = branchPath;
                                        folderPath2 /= "COMMIT";
                                        commit.setFolderPath(folderPath2);
                                        tempPath = branchPath;
                                        tempPath /= "TREE";
                                        if (treeType == 1) {
                                            Tree = new AVL(tempPath, merkil, commit);
                                        }
                                        else if (treeType == 2) {
                                            Tree = new Red_Black(tempPath, merkil, commit);
                                        }
                                        else if (treeType == 3) {
                                            cout << "Enter Minimum Degree : ";
                                            int minDeg;
                                            cin >> minDeg;
                                            Tree = new BTree(minDeg, tempPath, merkil, commit);
                                        }
                                        screen = 0;
                                    }
                                    else {
                                        screen = 2;
                                    }
                                }
                            }
                            runing = 0;
                            break;
                        case VK_ESCAPE:
                            break;
                        }
                    }
                }
            }
        }
        return 1;
    }

public:
    VersionControlSystem() {
        mainDir = current_path();
        srand(static_cast<int>(time(nullptr)));
        path repositoryPath;
        if (!RepoMenuScreen(repositoryPath)) return;
        while (MainMenu());

    }

    ~VersionControlSystem() {
        if (Tree) {
            delete Tree;
        }
    }

} GitLite;

int main()
{
    return 0;
}