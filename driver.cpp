#include <iostream>
using namespace std;

int main()
{
    int exit;
    string exitStr;
    do
    {
        do
        {
            cout << "Select a numerical option:\n+===== Main Menu =====+" << endl;
            cout << "1. init\n2. add\n3. rm\n4. commit\n5. checkout\n6. quit\n+----------------------+" << endl;
            cin >> exitStr;
            if(exitStr != "1" && exitStr != "2" && exitStr != "3" && exitStr != "4" && exitStr != "5" && exitStr != "6")
            {
                cout << "Invalid Input" << endl;
            }
        }while(exitStr != "1" && exitStr != "2" && exitStr != "3" && exitStr != "4" && exitStr != "5" && exitStr != "6");
        exit = stoi(exitStr);
        switch(exit)
        {
            case 1:
                cout << "case 1" << endl;
                break;
            case 2:
                cout << "case 2" << endl;
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
            default:
                cout << "Invalid input" << endl;
                break;
        }
    }while(exit != 6);
    return 0;
}