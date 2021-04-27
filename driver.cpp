/*
CSCI 2270 Spring 21
Final Project
Group Members: Bach Nguyen, Tyler Curnow and Matthew Van Winkle
*/

#include <iostream>
#include <fstream>
#include <filesystem>
#include "miniGit.cpp"

using namespace std;

int main()
{
    miniGit git;
    ifstream checkFileName;
    int exit = 0, num_commit = 0,recent_commit = 0;
    string exitStr = "", fileName = "";
    do
    {
        do
        {
            print_menu();
            cout << "=> "; getline(cin,exitStr);
            if(!check_input(exitStr))
            {
                cout << "Invalid input. Please choose again" << endl;
            }
        }while(!check_input(exitStr));
        exit = stoi(exitStr);
        switch(exit)
        {
            case 1://INIT--DONE

                git.init(git.addDDnode(num_commit));
                cout << "New respository initialized." << endl;
                break;
            
            case 2://ADD--DONE
                if(recent_commit != num_commit)
                {
                    cout<<"can't add while not in most recent commit"<<endl;
                    break;
                }
                do
                {
                    cout << "Enter file name: " << endl;
                    cout << "=> ";getline(cin, fileName);
                    checkFileName.open(fileName);
                    if(checkFileName.fail())
                    {
                        cout << "File does not exist." << endl;
                    }
                    else
                    {
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
                if(recent_commit != num_commit)
                {
                    cout<<"can't remove while not in most recent commit"<<endl;
                    break;
                }
                cout << "Enter file name you wish to remove: " << endl;
                cout << "=> "; getline(cin, fileName);
                if (git.checkFile(fileName, num_commit))
                {
                    git.removeFile(fileName, num_commit);
                    //git.printDS();
                }
                else{cout << "File does not exist within the directory." << endl;}
                break;
            
            case 4://COMMIT--IN PROGRESS
                if (recent_commit!=num_commit)
                {
                    cout<<"can't commit while not in most recent commit"<<endl;
                    break;
                }
                num_commit++;
                recent_commit++;
                git.commit(num_commit);
                break;
            
            case 5://CHECKOUT--IN PROGRESS
                
                cout << "Are you sure you wish to checkout? *this action will overwrite the current directory* (y/n)"<<endl;
                char checkout;
                cout << "=> "; cin >> checkout;
                cin.ignore();
                if(checkout == 'y')
                {
                    cout<<"Which commit would you like to checkout?"<<endl;
                    cout << "=> "; cin >> recent_commit;
                    cin.ignore();
                    git.checkout(recent_commit);
                    break;
                }
                else{break;}
                
            case 6://EXIT--DONE
                cout<<"Please enter a filename to check differences of: ";
                cout << "=> "; getline(cin, fileName);
                git.diff(fileName,num_commit-1);
                git.status(num_commit-1);
                break;
            
            case 7:
                git.printDS();
                break;
            
            case 8:
                cout << "exit" << endl;
                fs::remove_all(".miniGit");
                git.~miniGit();
                break;

            default:
                cout << "Invalid input" << endl;
                break;
        }
    }while(exit != 6);
    return 0;
}