#include <iostream>
#include "miniGit.hpp"
#include <filesystem>

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
    else
    {
        return;
    }
}