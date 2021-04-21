#include <iostream>
#include "miniGit.cpp"

using namespace std;

int main()
{
    int exit;
    miniGit git;
    doublyNode *dNode;
    string exitStr, fileName;
    do
    {
        do
        {
            cout << "Select a numerical option:\n+===== Main Menu =====+" << endl;
            cout << "1. init\n2. add\n3. remove\n4. commit\n5. checkout\n6. quit\n+----------------------+" << endl;
            getline(cin,exitStr);
            if(exitStr != "1" && exitStr != "2" && exitStr != "3" && exitStr != "4" && exitStr != "5" && exitStr != "6")
            {
                cout << "Invalid Input" << endl;
            }
        }while(exitStr != "1" && exitStr != "2" && exitStr != "3" && exitStr != "4" && exitStr != "5" && exitStr != "6");
        exit = stoi(exitStr);
        switch(exit)
        {
            case 1:
                
                dNode = git.init();                             // Initialize empty repository
                cout << "New respository initialized." << endl;
                break;
            case 2:
                do   
                {
                    cout << "Enter file name: " << endl;
                    getline(cin, fileName);
                    if (git.checkFile(fileName))
                    {
                        cout << "File name already exist. Enter a different name." << endl;
                    }
                }while (git.checkFile(fileName));
                git.addFile(dNode, fileName);
                git.printDS();
                break;
            case 3:
                cout << "Enter file name you wish to remove: " << endl;
                getline(cin, fileName);
                if (git.checkFile(fileName))
                {
                    git.removeFile(fileName);
                    //git.printDS();
                }
                else{cout << "File does not exist within the directory." << endl;}
                break;
            case 4:
                cout << "case 4" << endl;
                break;
            case 5:
                cout << "case 5" << endl;
                break;
            case 6:
                cout << "exit" << endl;
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }while(exit != 6);
    return 0;
}