#pragma once
#include <iostream>
#include <filesystem>
#include "CustomString.h"
#include "CustomList.h"
#include "HelpingFunctions.h"
#include "Stack.h"
#include "Merkle.h"
#include "CommitFunctionalities.h"
#include "ParentTree.h"
using namespace std;
using namespace filesystem;


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
