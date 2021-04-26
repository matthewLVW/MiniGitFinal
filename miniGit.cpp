#include <iostream>
#include "miniGit.hpp"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

miniGit::miniGit()                              // Constructor
{
    DLLhead = nullptr;                          // Set Doubly LL head to null;
}
miniGit::~miniGit()                             // class destructor to deallocate data structures   
{
    doublyNode *DLLremove = nullptr;            // Declare and initialize all the temp pointers we will use
    singlyNode *SLLremove = nullptr;
    while (DLLhead != nullptr)                  // Traverse the doubly link list
    {
        while(DLLhead->head != nullptr)         // nested while loop to traverse the singly link list
        {
            cout << "Deleting: [" << DLLhead->head->fileName << "]" << endl;
            SLLremove = DLLhead->head->next;    // store the next node in the SLL to our temp pointer
            delete DLLhead->head;               // Deallocate the current head of the SLL
            DLLhead->head = SLLremove;          // reassign head to be the node stored in our temp pointer
        }
        cout << "Deleting: [" << DLLhead->commitNumber << "]" << endl;
        DLLremove = DLLhead->next;              // Once we are done deallocating the SLL according to the current DLL
        delete DLLhead;                         // We deallocate that current node (current head)
        DLLhead = DLLremove;                    // reassign the head to what we stored in our DLL temp ointer
    }
    SLLremove = nullptr;                        // set both of our temp pointer to null for good measures
    DLLremove = nullptr;
}
void miniGit::init(doublyNode *dNode)                            // Initializing repository
{
    DLLhead = dNode;
    fs::remove_all(".miniGit");                 // Remove the previous
    fs::create_directory(".miniGit");           // Initialize new
}
doublyNode *miniGit::currCommit(int commit)     // Function get the current DLL node containing given commit #
{
    if (commit == 0){return DLLhead;}
    doublyNode *crawler = DLLhead;              // Otherwise, we traverse to find (declare crawler to start at head)
    while (crawler != nullptr)                  // Traverse til crawler points to null
    {
        if (crawler->commitNumber == commit)    // If we found the commit at that particular node
        {
            break;                              // return the pointer to that node
        }
        crawler = crawler->next;                // Otherwise, we increment crawler
    }
    return crawler;                             // return crawler
}
bool miniGit::checkFile(string file, int commit)// Function to check if file exists in SLL
{
    doublyNode *dcrawler = currCommit(commit);  // Declare and set a DLL crawler to start at head
    singlyNode *crawler = dcrawler->head;       // set SLL node to start at the head
   
    while (crawler != nullptr)                  // Traverse the SLL 
    {
        if (crawler->fileName == file)          // If we find the file name
        {
            return true;                        // Function will return true
        }
        crawler = crawler->next;                // Increment crawler
    }
    return false;                               // Function returns false if file does not exist within SLL
}
void miniGit::addFile(doublyNode *Dnode, string fileName)   // Function to add file to SLL
{ 
    singlyNode *insert = new singlyNode;                    // Dynamically allocate a new SLL node to insert
    insert->fileName = fileName;                            // set the fileName to the file being read in
    insert->fileVersion = "00";                             // set initial file version
    insert->next = nullptr;                                 // set the initial ptr to null
    if (Dnode->head == nullptr)                             // If the SLL is empty
    {
        cout << "Adding to head" << endl;
        Dnode->head = insert;                               // We insert at the head
    }
    else                                                    // Otherwise, we traverse to the end
    {
        singlyNode *crawler = Dnode->head;                  // Declare a crawler to start at the head
        while (crawler->next != nullptr)                    // Traverse til we are at the end/tail node
        {    
            crawler = crawler->next;                        // Increment crawler point
        }
        crawler->next = insert;                             // Insert at the end
    }
    return;                                                 // Exit function
}
void miniGit::removeFile(string file, int commit)           // Function to remove a file (delete a node)
{
    doublyNode *main = currCommit(commit);                  // Initialize a DLL
    singlyNode *curr = main->head, *prev = nullptr;         // Set curr to head, prev to null

    while (curr != nullptr)                                 // Traverse the SLL
    {
        if (curr->fileName == file)                         // If we found the file
        {
            if (prev == nullptr)                            // If the file is the ONLY node in SLL
            {
                main->head = curr->next;                    // Then we set head to the next ptr (null)
                delete curr;                                // Dealocate current node
            }
            else                                            // Otherwise, if there are multiple files
            {
                prev->next = curr->next;                    // Set next node to next node of curr
                delete curr;                                // dealocate current node
            }
        }
        prev = curr;                                        // Increment prev pointer
        curr = curr->next;                                  // increment curr pointer
    }
}
void miniGit::printDS()                                     // Function to print entire DS for debugging purposes
{
    doublyNode *DLL = DLLhead;
    do
    {
        singlyNode *slltmp = DLL->head;
        cout <<"[C#: "<< DLL->commitNumber<< "| -]-> ";
    //     cout <<"Files: ";
        while(slltmp != nullptr)
        {
            cout << "[" << slltmp->fileVersion <<"_" << slltmp->fileName << "| -]-> ";
            // << slltmp->fileVersion <<", ";
            slltmp = slltmp->next;
        }
    cout<< "NULL" << endl;
    DLL = DLL->next;
    }while(DLL != nullptr);
}
string renameFile(singlyNode *name, string file, string version)    // Function to rename the file
{
    string temp = name->fileName, sub, type;                        // Declare all the string variable we will use
    for (int i = 0; i < temp.length();i++)                          // traverse the length of the file name string
    {
        if (temp[i] == '.')                                         // dot indicates we are at the end of the name
        {                                                           // And it seperates the name and the file type
            sub = temp.substr(0, i);                                // store the name of file using substring
            type = temp.substr(i, temp.length() - 1);               // store the type of the file using substring
        }
    }
    return sub + "_" + name->fileVersion + type;                    // return the updated name (string string concatenation)
}
void miniGit::copyList(doublyNode *Dnode, singlyNode *OG)    // Function to copy over SLL (NOT COMPLETED)
{
    if (Dnode->head == nullptr){
        cout << "Dnode->head = null" << endl;
        return;
    }
    singlyNode *curr = OG;
    singlyNode *copy = new singlyNode;
    Dnode->next->head = copy;
    while (curr != nullptr)
    {
        if(curr->next == nullptr){
            copy->fileName = curr->fileName;
            copy->fileVersion = curr->fileVersion;
            break;
        }
        else{
        singlyNode *temp = new singlyNode;
        temp->next = nullptr;
        copy->fileName = curr->fileName;
        copy->fileVersion = curr->fileVersion;
        copy->next = temp;
        copy = copy->next;
        curr = curr->next;
        }
    }
    printDS();
}
doublyNode *miniGit::addDDnode(int incrementCommit)                 // Function to add DLL node after commiting
{
   cout<<incrementCommit<<endl;
    doublyNode *NewCommit = new doublyNode;                         // Dynamically allocate new DLL node
    NewCommit->commitNumber = incrementCommit;
    NewCommit->head=nullptr;                                        // Set all of it's data members accordingly
    NewCommit->next = nullptr;                                      // initialize initial pointer
    NewCommit->previous = nullptr;                                  // initialize initial pointer
    if (DLLhead == nullptr)                                         // If the DLL is empty
    {
        DLLhead = NewCommit;                                        // We insert at the head
    }
    else                                                            // Otherwise, we insert at the tail
    {
        doublyNode *temp = DLLhead;                                 // Set the DLL to start at head
        while(temp->next != nullptr)                                // Traverse until we are the last/tail node
        {
            temp = temp->next;                                      // Increment temp
        }
        temp->next = NewCommit;                                     // Insert new node at the end
        NewCommit->previous = temp;                                 // Set previous pointer
        NewCommit->next = nullptr;                                  // set next pointer
    }
    return NewCommit;                                               // return pointer to that node
}
void miniGit::commit(int num_commit)
{
    //go to current commit DLL node
    //Run through and for each file if it already exists (if it doesn't exist just add to .minigit) then check if changes have been made
    //If changes have been made increment the version number THEN copy the file into the .minigit directory
    //if it is unchanged do nothing
    //Once you have done this for each file then:
    //create a new DLL Node with incremented commit number and port the SLL from the previous node to this one.
    doublyNode *DLL = DLLhead;
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
    DLL->next = addDDnode(num_commit);
    copyList(DLL, DLL->head);
    // DLL->commitNumber++;
    // addDDnode(DLL, DLL->commitNumber);
    // doublyNode *comm = new doublyNode;
    // singlyNode *copy = new singlyNode;
    // comm->commitNumber = DLL->commitNumber++;
    // comm->head = copy;
    // // addDDnode(comm);
    // DLL->next = comm;
    // comm->next = nullptr;
    // comm->previous = DLL;
    // SLL = DLL->head;
    // while(SLL != nullptr)
    // {
    //     copy = new singlyNode;
    //     copy = SLL;
    //     SLL = SLL->next;
    // }
    //cout << copyLine << endl;
}
void miniGit::checkout(int commitnumber)
{
    string localDirectory = fs::current_path();
    string removeline = "rm " + localDirectory+"/*";
    fstream file;
    string copied,postcopy,postcopy2;
    doublyNode *crawler = currCommit(commitnumber);
    singlyNode *tmp = crawler->head;
    string word;
    while(tmp != nullptr)
    {
        string copied = localDirectory + "/.minigit/" + renameFile(tmp, tmp->fileName, tmp->fileVersion);
        file.open(copied);
        ofstream overWrite(tmp->fileName);
        while (getline(file, word))
        {
            overWrite << word << endl;
        }
        tmp=tmp->next;
        overWrite.close();
        file.close();
    }
}