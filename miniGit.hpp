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
        void checkout(int commitnumber);
};
