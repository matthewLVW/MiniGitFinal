#include <iostream>
#include "miniGit.cpp"
#include <fstream>

using namespace std;

int main()
{
    int exit;
    miniGit git;
    doublyNode *dNode;
    string exitStr, fileName;
    ifstream checkFileName;
    bool fileExists = false;
    do
    {
        do
        {
            cout << "Select a numerical option:\n+===== Main Menu =====+" << endl;
            cout << "1. init\n2. add\n3. remove\n4. commit\n5. checkout\n6. quit\n7. print\n+----------------------+" << endl;
            getline(cin,exitStr);
            if(exitStr != "1" && exitStr != "2" && exitStr != "3" && exitStr != "4" && exitStr != "5" && exitStr != "6" && exitStr != "7")
            {
                cout << "Invalid Input" << endl;
            }
        }while(exitStr != "1" && exitStr != "2" && exitStr != "3" && exitStr != "4" && exitStr != "5" && exitStr != "6" && exitStr != "7");
        exit = stoi(exitStr);
        switch(exit)
        {
            case 1://INIT--DONE
                dNode = git.init();                             // Initialize empty repository
                cout << "New respository initialized." << endl;
                break;
            case 2://ADD--DONE
                do{
                    fileExists = false;
                    cout << "Enter file name: " << endl;
                    getline(cin, fileName);
                    checkFileName.open(fileName);
                    if(checkFileName.fail())
                    {
                        cout << "File does not exist." << endl;
                    }
                    else if(!checkFileName.fail())
                    {
                        fileExists = true;
                    }
                    checkFileName.close();
                }while(!fileExists);
                if (git.checkFile(fileName))
                {
                    cout << "File name already exist in current stage." << endl;
                }
                else
                {
                    git.addFile(dNode, fileName);
                    git.printDS();
                }
                checkFileName.close();
                break;
            case 3://REMOVE--DONE
                cout << "Enter file name you wish to remove: " << endl;
                getline(cin, fileName);
                if (git.checkFile(fileName))
                {
                    git.removeFile(fileName);
                    //git.printDS();
                }
                else{cout << "File does not exist within the directory." << endl;}
                break;
            case 4://COMMIT--IN PROGRESS
                cout << "case 4" << endl;
                break;
            case 5://CHECKOUT--IN PROGRESS
                cout << "case 5" << endl;
                break;
            case 6://EXIT--DONE
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