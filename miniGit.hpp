#include <iostream>

using namespace std;

//Commmit logic
/*
add file
When user commit, check each file to look for difference

if a file is found to not be the same, create a new version of that file and increment the version number
else, do nothing to the file name and do not add the file into .miniGit

when commit, dynamically allocate doubly LL node
also need to dynamically allocate singly LL node
    set node data to equal the name and commit version
increment commit number
set previous and next pointer
copy all of singly LL node over

*/

struct singlyNode
{
    string fileName;
    string fileVersion;
    singlyNode * next;
};
struct doublyNode
{   
    int commitNumber;
    singlyNode * head;
    doublyNode * previous;
    doublyNode * next;
};

class miniGit
{
    private:
        
        doublyNode *head;

    public:

        miniGit();
        ~miniGit();
        doublyNode *init();
        doublyNode *currCommit(int commit);
        bool checkFile(string file);
        void addFile(doublyNode *Dnode, string fileName);
        void removeFile(string file);
        void printDS();
        void commit();
        
};