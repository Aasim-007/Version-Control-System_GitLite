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