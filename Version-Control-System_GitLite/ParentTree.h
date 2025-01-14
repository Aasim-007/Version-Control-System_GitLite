#pragma once
#include <iostream>
#include <filesystem>
#include "CustomString.h"
#include "CustomList.h"
#include "HelpingFunctions.h"
#include "Stack.h"
#include "Merkle.h"
#include "CommitFunctionalities.h"
using namespace std;
using namespace filesystem;

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