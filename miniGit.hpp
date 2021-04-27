// CSCI 2270 -- Spring 21
// Final Project -- Mini_Git
// Group Members: Bach Nguyen, Tyler Curnow and Matthew Van Winkle

#include <iostream>
using namespace std;
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
        
        doublyNode *DLLhead;

    public:

        miniGit();
        ~miniGit();
        void init(doublyNode *dNode);
        doublyNode *currCommit(int commit);
        bool checkFile(string file, int commit);
        void addFile(doublyNode *Dnode, string fileName);
        void removeFile(string file, int commit);
        void printDS();
        void copyList(doublyNode *Dnode, singlyNode *OG);
        void commit(int num_commit);
        doublyNode *addDDnode(int incrementCommit);
        void checkout(int commitNumber);
        void print_difference(string filename,int commitnumber);
        bool check_difference(string filename,int commitnumber);
        void status(int commitnumber);
};