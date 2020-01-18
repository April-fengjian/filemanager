//CS3307
//Zhiqi Bei 
//zbei@uwo.ca

#include "filemanager.h"
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char * argv[]) {
    if(argc != 3){
        printf("The input is incorrect!");
    }
    filemanager file1 = filemanager(argv[1]);
    filemanager file2 = filemanager(argv[2]);
    
    //check if the file is exist
    if(access(file1.getName(), 0) == -1){
        file1.setErrorNum(2);
        cout<<"Error: "<<file1.getName()<<" "<<file1.getError()<<endl;
    }else{
    
    //check if file1 is a regular file
    if(!S_ISREG(file1.getTypeCode())){
        cout<<"Error: "<<file1.getName()<<" is not a regular file"<<endl;
    }
    int errorNum = file1.reName(file2.getName());
    if(errorNum != 0){
        if(errorNum == 18){
            fstream file(file2.getName(),fstream::binary);
            file1.dump(file);
            file1.remove();
        }
            
    }
}
}
