//CS3307
//Zhiqi Bei (#250916374)
//zbei@uwo.ca

#include "filemanager.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
using namespace std;
//constructor
filemanager :: filemanager(char* filename){
    this->name = filename;
    struct stat file;
    stat(filename, &file);
    this->type = file.st_mode;
    this->size = file.st_size;
    
    //the owner name
    this->ownerID = file.st_uid;
    struct passwd* user;
    user = getpwuid(ownerID);
    this->owner = user->pw_name;
    
    //the group name
    this->groupID = file.st_gid;
    struct group* group;
    group = getgrgid(groupID);
    this->group = group->gr_name;
    
    //the permission
    this->permission = file.st_mode;
    
    //the access time, modification time and status change time
    long time = file.st_atime;
    char* atime = ctime(&time);
    this->accessTime = atime;
    
    time = file.st_mtime;
    char* mtime = ctime(&time);
    this->modTime = mtime;
    
    time = file.st_ctime;
    char* chtime = ctime(&time);
    this->changeTime = chtime;
    
    //the block size
    this->blockSize = file.st_blksize;
    
    //children
    if (S_ISDIR(file.st_mode)&(file.st_size==0)) {
		expand();
    }
    
    //the error number
    this->errorNum = errno;

};
//destructor
filemanager:: ~filemanager(){
   
}
//dump
//This function will take a file stream as a parameter 
//and dump the contents of the named file to that file stream.  
//This can be used to copy the file, display its contents to the terminal, and so on. 
int filemanager::dump(ostream& infile){
    char* line = nullptr;
    ifstream file(name,fstream::binary);
    if(!file.is_open()){
		printf("WRONG!");
		errorNum = 2;
	}
    while(!file.eof()){
        file.read(line, blockSize);
        infile.write(line, blockSize);
    }
    file.close();
    
    return errorNum;
}
//rename
int filemanager:: reName(char* newname){
    errorNum = rename(name, newname);
    return errorNum;
}
//remove
int filemanager:: remove(){
    errorNum = unlink(name);
    return errorNum;
}
//compare
int filemanager:: compare(filemanager file){
    char* myline = nullptr;
    char* otherline = nullptr;
    ifstream myfile(name,fstream::binary);
    ifstream otherfile(file.getName(), fstream:: binary);
    if(!myfile.is_open()||!otherfile.is_open()){
		printf("error in open the file");
	}
    while(!myfile.eof()){
        myfile.read(myline, blockSize);
        otherfile.read(otherline, file.getBlockSize());
        if (myline!= otherline) {
            myfile.close();
            otherfile.close();
            return -1;
        }
    }
    return 0;
}
//expand
//This function operates on directories only 
//and is used to fill in the children of the file object this function was invoked upon.
int filemanager:: expand(){
    if (!S_ISDIR(getTypeCode())) {
		errorNum = 134;
		return errorNum;
	}
    DIR* dirOpen = opendir(getName());
    if (dirOpen!= NULL) {
        struct dirent* dirRead = readdir(dirOpen);
        //if the directory is not empty
        //push its children into the vector
        if (dirRead != NULL) {
            while(dirRead != NULL){
                children.push_back(dirRead->d_name);
				if ((dirRead = readdir(dirOpen))== NULL) {
					break;
				}
            }
            closedir(dirOpen);
        
		}
        
    }
    closedir(dirOpen);
    return errorNum;
}
//getter method
char* filemanager:: getName(){
    return name;
}

string filemanager:: getType(){
	string fileType;
    if(S_ISREG(type)){
        fileType = "regular file";
    }else if (S_ISDIR(type)){
        fileType = "directory";
    }else if (S_ISLNK(type)){
        fileType = "symbolic link";
    }else if (S_ISCHR(type)){
        fileType = "character special";
    }else if (S_ISBLK(type)){
        fileType = "block special";
    }else if (S_ISFIFO(type)){
        fileType = "fifo";
    }else if (S_ISSOCK(type)){
        fileType = "socket";
    }
    return fileType;
}
long filemanager:: getSize(){
    return size;
}
string filemanager:: getOwner(){
    return owner;
}
string filemanager:: getGroup(){
    return group;
}
void filemanager:: getPermission(){
    //file type
    if(S_ISREG(type))
        printf("-");
    else if(S_ISDIR(type))
        printf("d");
    else if(S_ISCHR(type))
        printf("c");
    else if(S_ISBLK(type))
        printf("b");
    else if(S_ISFIFO(type))
        printf("p");
    else if(S_ISLNK(type))
        printf("l");
    else if(S_ISSOCK(type))
        printf("s");
    
    int n;
    for(n=8;n>=0;n--){
        if(permission&(1<<n)){
            switch(n%3){
                case 2:
                    printf("r");
                    break;
                case 1:
                    printf("w");
                    break;
                case 0:
                    printf("x");
                    break;
                default:
                    break;
            }
        }
        else
        {
            printf("-");
        }
    }
}
 char* filemanager:: getAccessTime(){
    return accessTime;
}
char* filemanager:: getModTime(){
    return modTime;
}
char* filemanager::getChangeTime(){
    return changeTime;
}
int filemanager:: getBlockSize(){
    return blockSize;
}
vector<filemanager> filemanager:: getChildren(){
    return children;
}
int filemanager:: getErrorNum(){
    return errorNum;
}
string filemanager:: getError(){
    return strerror(errorNum);
}
void filemanager:: setErrorNum(int num){
	errorNum = num;
}
mode_t filemanager:: getTypeCode(){
    return type;
}

