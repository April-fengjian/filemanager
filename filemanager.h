//CS3307
//Zhiqi Bei
//zbei@uwo.ca

#ifndef filemanager_h
#define filemanager_h
#include <string>
#include <vector>
using namespace std;



class filemanager{
private:
    char* name;
    mode_t type;
    long size;
    int ownerID;
    string owner;
    int groupID;
    string group;
    mode_t permission;
    char* accessTime;
    char* modTime;
    char* changeTime;
    int blockSize;
    int errorNum;
    vector<filemanager>children;

    
    
public:
    filemanager();
    filemanager(char* filename);
    
    ~filemanager();
    int reName(char* newname);
    int expand();
    int dump(ostream& file);
    int remove();
    int compare(filemanager file);
    
    char* getName();
    string getType();
    long getSize();
    string getOwner();
    string getGroup();
    void getPermission();
    char* getAccessTime();
    char* getModTime();
    char* getChangeTime();
    int getBlockSize();
    vector<filemanager> getChildren();
    int getErrorNum();
    string getError();
    mode_t getTypeCode();
    void setErrorNum(int num);
};





#endif /* filemanager_h */
