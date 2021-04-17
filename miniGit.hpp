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
        
        singlyNode *head;

    public:
        

};