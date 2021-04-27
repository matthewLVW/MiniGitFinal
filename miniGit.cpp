/*
CSCI 2270 Spring 21
Final Project
Group Members: Bach Nguyen, Tyler Curnow and Matthew Van Winkle
*/
  
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
            // cout << "Deleting: [" << DLLhead->head->fileName << "]" << endl;
            SLLremove = DLLhead->head->next;    // store the next node in the SLL to our temp pointer
            delete DLLhead->head;               // Deallocate the current head of the SLL
            DLLhead->head = SLLremove;          // reassign head to be the node stored in our temp pointer
        }
        // cout << "Deleting: [" << DLLhead->commitNumber << "]" << endl;
        DLLremove = DLLhead->next;              // Once we are done deallocating the SLL according to the current DLL
        delete DLLhead;                         // We deallocate that current node (current head)
        DLLhead = DLLremove;                    // reassign the head to what we stored in our DLL temp ointer
    }
    SLLremove = nullptr;                        // set both of our temp pointer to null for good measures
    DLLremove = nullptr;
}
bool check_input(string input)                  // Function to check the inputs of the users, make sure they're valid
{
    if(input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "6" && input != "7" && input != "8")
    {
        return false;                           // return false if the input is not part of the option give
    }
    return true;                                // return true otherwise
}
void print_menu()                               // Function to print out the pain menu of the page
{
    cout << "+======= Main Menu =======+" << endl;
    cout << "+Select a numerical option+" << endl;
    cout << "1. Init\n2. Add\n3. Remove\n4. Commit" << endl;
    cout << "5. Checkout\n6. Diff & Status\n7. Print\n8. Exit" << endl;
    cout << "+--------------------------+" << endl;
}
void miniGit::init(doublyNode *dNode)           // Initializing repository
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
    doublyNode *DLL = DLLhead;                              // Declare and initialize a node to travese the DLL (start from head)
    do                                                      // Do while loop to traverse the DLL
    {
        singlyNode *slltmp = DLL->head;                     // Declare and initialize a node to traverse the SLL (start from head)
        cout <<"[C#: "<< DLL->commitNumber<< "| -]-> ";     // print current DLL node
        while(slltmp != nullptr)                            // Traverse the SLL
        {                                                   // Print current SLL node
            cout << "[" << slltmp->fileVersion <<"_" << slltmp->fileName << "| -]-> ";
            slltmp = slltmp->next;                          // Increment SLL pointer
        }
    cout<< "NULL" << endl;                                  // The last SLL pointer will point to NULL
    DLL = DLL->next;                                        // Increment DLL pointer
    }while(DLL != nullptr);                                 // Condition to exit
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
void miniGit::copyList(doublyNode *Dnode, singlyNode *OG)           // Function to copy over SLL (NOT COMPLETED)
{
    if (Dnode->head == nullptr){return;}
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
void miniGit::commit(int num_commit)                                // Function to commit changes per user's request
{
    //go to current commit DLL node
    //Run through and for each file if it already exists (if it doesn't exist just add to .minigit) then check if changes have been made
    //If changes have been made increment the version number THEN copy the file into the .minigit directory
    //if it is unchanged do nothing
    //Once you have done this for each file then:
    //create a new DLL Node with incremented commit number and port the SLL from the previous node to this one.
    doublyNode *DLL = DLLhead;                                      // Declare and initialize a DLL pointer to star from head
    string copyLine;                                                // Declare a string variable
    while(DLL->next != nullptr)                                     // Traverse until we are at the most current pointer (tail DLL node)
    {                       
        DLL = DLL->next;                                            // Increment DLL pointer
    }
    singlyNode *SLL = DLL->head;                                    // Declare and initialize a SLL pointer to start at head
    while(SLL != nullptr)                                           // Traverse the SLL
    {
        bool difference = false;                                    // Bool checker to see if the current file has been changed
        string tmp = ".minigit/" + renameFile(SLL, SLL->fileName, SLL->fileVersion);
        fstream file;                                               // Using fstream to open file
        file.open(tmp.c_str());                                     // Open file
        if(file.fail())                                             // If file does not exist in miniGit directory
        {                                                           // if file doesn't already exist in .minigit directory
            copyLine = "cp " + SLL->fileName +" .minigit/" + renameFile(SLL, SLL->fileName, SLL->fileVersion);
            system(copyLine.c_str());                               // We add the file in
        }
        else                                                        // Otherwise, if the file already exists
        {                                                           
            ifstream file1(SLL->fileName);                          // Open the current file in main directory
            string word, word1;                                     // Use two string variable to store each words to compare
            while (!file.eof())                                     // run until end of file
            {
                getline(file, word);                                // Use getline to store word from commit file
                getline(file1,word1);                               // Use geline to store word1 from original file
                if (word != word1)                                  // If we found a difference (words do not match)
                {
                    difference = true;                              // Turn bool checker to true
                    break;                                          // break out of the loop
                }
            }
            if (difference)                                         // If the files do not match, we have to update the version
            {
                int fileV = stoi(SLL->fileVersion) + 1;             // convert version to int and increment it by 1, store it in an int variable
                if (fileV < 10)                                     // If file version is less than 10
                {
                    SLL->fileVersion = "0" + to_string(fileV);      // we add an "0" at the beginning
                }
                else
                {
                    SLL->fileVersion = to_string(fileV);            // Otherwise, we assign it as is
                }                                                   
                copyLine = "cp " + SLL->fileName +" .minigit/" + renameFile(SLL, SLL->fileName, SLL->fileVersion);
                system(copyLine.c_str());                           // create a copy file with new version and the changes made
            }   
        }
        SLL = SLL->next;                                            // Increment SLL pointer
    }
    DLL->next = addDDnode(num_commit);                              // Create a new node and add it to the end of the commit DS (DLL)
    copyList(DLL, DLL->head);                                       // deep copy of all of the SLL node from previous commit with updated version number
}

void miniGit::checkout(int commitnumber)                           // Function for check out (Matthew's implementation)
{
    string localDirectory = fs::current_path();                     // store the current directory by using current_path
    string removeline = "rm " + localDirectory+ "/*";               // 
    fstream file;                                                   // Declare an fstream object to open file
    string copied,postcopy,postcopy2;                               // Declare all strings variable to use
    doublyNode *crawler = DLLhead;                                  // declare a traversal pointer to start at the head DLL node
    while(crawler->commitNumber != commitnumber)                    // Traverse until we are at the node of the commit number being passed through
    {
        crawler = crawler->next;                                    // increment counter if until we reach that node
    }
    singlyNode *tmp = crawler->head;                                // 
    while(tmp!=nullptr)
    {
        copied = localDirectory + "/.minigit/" + renameFile(tmp, tmp->fileName, tmp->fileVersion);
        file.open(tmp->fileName);
        if(file.fail())
        {
            // cout<< tmp->fileName <<endl;
            cout<<"test"<<endl;
            copied = "cp " + copied + " " + localDirectory;
            system(copied.c_str());
        }
        else
        {
            string remove = "rm " + localDirectory + "/" + tmp->fileName;
            system(remove.c_str());
            postcopy=copied;
            postcopy2=copied;
            copied = "cp " + copied + " " + localDirectory;
            system(copied.c_str());
            postcopy = "mv " + postcopy +" " + tmp->fileName;
            system(postcopy.c_str());
            postcopy2= "rm " + localDirectory + "/" + renameFile(tmp, tmp->fileName, tmp->fileVersion);
            system(postcopy2.c_str()); 
            postcopy = "cp " + localDirectory + "/" + tmp->fileName + " " + localDirectory + "/.minigit/" + renameFile(tmp, tmp->fileName, tmp->fileVersion);
            system(postcopy.c_str());
        }
    tmp=tmp->next;
    file.close();
    }
}
// void miniGit::checkout(int commitnumber)                         // Function for checkout (Bach's implementation)          
// {
//     fstream file;                                                // declare an fstream object to read in file
//     string localDirectory = fs::current_path();                  // store the path to current directory
//     doublyNode *crawler = currCommit(commitnumber);              // declare a traversal pointer & set it to the node of the read in commit number
//     singlyNode *tmp = crawler->head;                             // set an SLL pointer to start at the head of the DLL
//     string word;                                                 // string to store each line being read in
//     while(tmp != nullptr)                                        // Traverse the SLL
//     {                                                            // copied will be the specific in miniGit directory   
//         string copied = localDirectory + "/.minigit/" + renameFile(tmp, tmp->fileName, tmp->fileVersion);
//         file.open(copied);                                       // Open that particular file
//         ofstream overWrite(tmp->fileName);                       // declare an ofstream object and set it to open the main file
//         while (getline(file, word))                              // traverse until the end of the miniGit file
//         {
//             overWrite << word << endl;                           // Overwrite the main file with the contents in the miniGit file
//         }
//         tmp=tmp->next;                                           // increment SLL traversal pointer
//         overWrite.close();                                       // close file in miniGit file
//         file.close();                                            // close file in main directory
//     }
// }
bool miniGit::diff(string filename,int commitnumber)
{
    ifstream(file);
    ifstream(file2);
    file.open(filename);
    singlyNode* tmp = currCommit(commitnumber)->head;
    string filename2, word,word1;;
    while(tmp != nullptr)
    {
        if(tmp->fileName == filename)
        {
            filename2 = ".minigit/" + renameFile(tmp, tmp->fileName, tmp->fileVersion);
            file2.open(filename2.c_str());
            break;
        }
        tmp=tmp->next;
    }
    while (!file.eof())
    {
        getline(file, word);
        getline(file2,word1);
        if (word != word1)
        {
            cout << "First diffence: " << word1 << endl;
            return true;
        }
    }
return false;          
} 

void miniGit::status(int commitnumber)
{
    singlyNode* tmp = currCommit(commitnumber)->head;
    fstream file;
    fstream file2;
    string filename2,word,word1;
    while(tmp!=NULL)
    {
        bool print = diff(tmp->fileName,commitnumber);
        
        if(print)
        {
            cout << tmp->fileName << " has a difference." << endl;
        }
        else
        {
            cout << tmp->fileName << " did not have a difference."<< endl;
        }
        tmp=tmp->next;
    }
}