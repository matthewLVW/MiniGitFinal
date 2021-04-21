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
            cout << "1. init\n2. add\n3. rm\n4. commit\n5. checkout\n6. quit\n7. print\n+----------------------+" << endl;
            cin >> exitStr;
            if(exitStr != "1" and exitStr != "2" and exitStr != "3" and exitStr != "4" and exitStr != "5" and exitStr != "6" && exitStr != "7")
            {
                cout << "Invalid Input" << endl;
            }
        }while(exitStr != "1" && exitStr != "2" && exitStr != "3" && exitStr != "4" && exitStr != "5" && exitStr != "6" && exitStr != "7");
        exit = stoi(exitStr);
        switch(exit)
        {
            case 1:
                
                dNode = git.init();                 // Initialize empty repository
                cout << "New respository initialized." << endl;
                break;
            case 2:
                    cout << "Enter file name: " << endl;
                    cin>>fileName;
                    git.addFile(dNode, fileName);
                break;
            case 3:
                cout << "case 3" << endl;
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
            case 7:
                git.printDS();
                break;
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }while(exit != 6);
    return 0;
}