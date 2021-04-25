#include <iostream>
#include <fstream>
#include <filesystem>
#include "miniGit.cpp"

using namespace std;

int main()
{
    int exit, num_commit = 0;
    miniGit git;
    doublyNode *dNode = nullptr;
    string exitStr = "", fileName = "";
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
                git.init();
                dNode = git.addDDnode(num_commit);                          // Initialize empty repository
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
                    else
                    {
                        // fileExists = true;
                        break;
                    }
                }while(checkFileName.fail());
                if (num_commit > 0 && git.checkFile(fileName, num_commit))
                {
                    cout << "File name already exist in current stage." << endl;
                }
                else
                {
                    git.addFile(git.currCommit(num_commit), fileName);
                }
                checkFileName.close();
                break;
            
            case 3://REMOVE--DONE
                cout << "Enter file name you wish to remove: " << endl;
                getline(cin, fileName);
                if (git.checkFile(fileName, num_commit))
                {
                    git.removeFile(fileName, num_commit);
                    //git.printDS();
                }
                else{cout << "File does not exist within the directory." << endl;}
                break;
            
            case 4://COMMIT--IN PROGRESS
                num_commit++;
                git.commit(num_commit);
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