#include <iostream>
#include "miniGit.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

miniGit::miniGit()
{
    head = nullptr;
}
miniGit::~miniGit()
{
    
}
doublyNode *miniGit::init()
{
    doublyNode *Dnode = new doublyNode;
    Dnode->commitNumber = 0;
    Dnode->head = nullptr;
    Dnode->previous = nullptr;
    Dnode->next = nullptr;
    fs::remove_all(".miniGit");
    fs::create_directory(".miniGit");
    head = Dnode;
    return Dnode;
}
doublyNode *miniGit::currCommit(int commit)
{
    doublyNode *crawler = head;
    while (crawler != nullptr)
    {
        if (crawler->commitNumber == commit)
        {
            return crawler;
        }
        crawler = crawler->next;
    }
    return nullptr;
}
bool miniGit::checkFile(string file)
{
    doublyNode *dcrawler = head;
    singlyNode *crawler = dcrawler->head;
   
    while (crawler != nullptr)
    {
        if (crawler->fileName == file)
        {
            return true;
        }
        crawler = crawler->next;
    }
    return false;
}
void miniGit::addFile(doublyNode *Dnode, string fileName)
{ 
    singlyNode *insert = new singlyNode;
    insert->fileName = fileName;
    insert->fileVersion = "00";
    insert->next = nullptr;
    if (Dnode->head == nullptr)
    {
        Dnode->head = insert;
    }
    else
    {
        singlyNode *crawler = Dnode->head;
        while (crawler->next != nullptr)
        {    
            crawler = crawler->next;
        }
        crawler->next = insert;
    }
    return;
}
void miniGit::removeFile(string file)
{
    doublyNode *main = head;
    singlyNode *curr = main->head, *prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->fileName == file)
        {
            if (prev == nullptr)
            {
                main->head = curr->next;
                delete curr;
            }
            else
            {
                prev->next = curr->next;
                delete curr;
            }
        }
        prev = curr;
        curr = curr->next;
    }
}
void miniGit::printDS()
{
    doublyNode *DLL = head;
    do
    {
        singlyNode *slltmp = DLL->head;
        cout <<"[C#: "<< DLL->commitNumber<< "| -]-> ";
    //     cout <<"Files: ";
        while(slltmp != nullptr)
        {
            cout << "[" << slltmp->fileName << "| -]-> ";
            // << slltmp->fileVersion <<", ";
            slltmp = slltmp->next;
        }
    cout<<endl;
    DLL = DLL->next;
    }while(DLL != nullptr);
}
string renameFile(singlyNode *name, string file, string version)
{
    string temp = name->fileName, sub, type;
    for (int i = 0; i < temp.length();i++)
    {
        if (temp[i] == '.')
        {
            sub = temp.substr(0, i);
            type = temp.substr(i, temp.length() - 1);
        }
    }
    return sub + "_" + name->fileVersion + type;
}
void miniGit::addDDnode(doublyNode *Dnode)
{
    if (head == nullptr)
    {
        head = Dnode;
        Dnode->previous = nullptr;
    }
    else
    {
        doublyNode *crawler = head;
        while (crawler->next != nullptr)
        {  
            Dnode->previous = crawler;
            crawler = crawler->next;
        }
        crawler->next = Dnode;
    }
    return;
}
// singlyNode *copyList(singlyNode *OG, doublyNode *Dnode, bool checker, string version)
// {
//     singlyNode *curr = OG;
//     singlyNode *copy = new singlyNode;
//     Dnode->head = copy;
//     copy->next = nullptr;
//     while (curr != nullptr)
//     {
//         copy->fileName = OG->fileName;
//         if (checker){copy->fileVersion = version;}
//         else{copy->fileVersion = OG->fileVersion;}
//         copy->next = OG->next;
//         copy = copy->next;
//         curr = curr->next;
//     }
//     return copy;
// }
void miniGit::commit()
{
    //go to current commit DLL node
    //Run through and for each file if it already exists (if it doesn't exist just add to .minigit) then check if changes have been made
    //If changes have been made increment the version number THEN copy the file into the .minigit directory
    //if it is unchanged do nothing
    //Once you have done this for each file then:
    //create a new DLL Node with incremented commit number and port the SLL from the previous node to this one.
    doublyNode *DLL = head;
    string copyLine;
    while(DLL->next != nullptr)
    {
        DLL = DLL->next;
    }
    singlyNode *SLL = DLL->head;
    while(SLL != nullptr)
    {
        //logic to check if file already exists
        //logic to check if files are the exact same
        bool difference = false;
        // string tmp = ".minigit/" + SLL->fileName + SLL->fileVersion;
        string tmp = ".minigit/" + renameFile(SLL, SLL->fileName, SLL->fileVersion);
        fstream file;
        file.open(tmp.c_str());
        if(file.fail())
        { //if file doesn't already exist in .minigit directory adds the file.
            //copyLine = "cp " + SLL->fileName +" .minigit/" + SLL->fileName + SLL->fileVersion;
            copyLine = "cp " + SLL->fileName +" .minigit/" + renameFile(SLL, SLL->fileName, SLL->fileVersion);
            system(copyLine.c_str());
        }
        else
        {//if file does exist:
            ifstream file1(SLL->fileName);
            string word, word1;
            while (!file.eof())
            {
                getline(file, word);
                getline(file1,word1);
                if (word != word1)
                {
                    difference = true;
                    break;
                }
            }
            if (difference)
            {
                int fileV = stoi(SLL->fileVersion) + 1;
                if (fileV < 10)
                {
                    SLL->fileVersion = "0" + to_string(fileV); 
                }
                else
                {
                    SLL->fileVersion = to_string(fileV);
                }
                // cout << "Updating file version: " << SLL->fileVersion << endl;
                // copyLine = "cp " + SLL->fileName +" .minigit/" + SLL->fileName + SLL->fileVersion;
                copyLine = "cp " + SLL->fileName +" .minigit/" + renameFile(SLL, SLL->fileName, SLL->fileVersion);
                system(copyLine.c_str());   
            }
            // file.close();
            // file.open(tmp.c_str());    
        }
        SLL = SLL->next;
    }
    doublyNode *comm = new doublyNode;
    singlyNode * copy = new singlyNode;
    comm->commitNumber = DLL->commitNumber++;
    comm->head = copy;
    addDDnode(comm);
    // comm->next = nullptr;
    // comm->previous = DLL;
    SLL = DLL->head;
    while(SLL != nullptr)
    {
        copy = new singlyNode;
        copy = SLL;
        SLL = SLL->next;
    }
    //cout << copyLine << endl;
}