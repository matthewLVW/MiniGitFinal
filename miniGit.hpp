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
        
        doublyNode *head;

    public:

        miniGit();
        ~miniGit();
        doublyNode *init();
        bool checkFile(string file);
        void addFile(doublyNode *Dnode, string fileName);
        void printDS();
        
};