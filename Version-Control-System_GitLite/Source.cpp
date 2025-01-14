
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
#include "CustomList.h"
#include "HelpingFunctions.h"
#include "Stack.h"
#include "Merkle.h"
#include "CommitFunctionalities.h"
#include "ParentTree.h"
#include "AVLTree.h"
#include "BTree.h"
#include "RedBlackTree.h"

using namespace std;
using namespace filesystem;


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