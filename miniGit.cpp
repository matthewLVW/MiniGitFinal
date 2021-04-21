#include <iostream>
#include "miniGit.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

miniGit::miniGit()
{
    
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
    ifstream inFile(fileName);

    if(!inFile.is_open())
    {
        if (!checkFile(fileName))
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
        }
        else{return;}
    }
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
    do{
        singlyNode *slltmp = DLL->head;
        cout <<"Commit number: "<<DLL->commitNumber<<endl;
        cout <<"Files: ";
        while(slltmp != nullptr)
        {
            cout << slltmp->fileName <<", ";
            slltmp = slltmp->next;
        }
    cout<<endl;
    DLL = DLL->next;
    }while(DLL != nullptr);
}