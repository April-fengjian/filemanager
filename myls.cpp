//CS3307
//Zhiqi Bei (#250916374)
//zbei@uwo.ca

#include <stdio.h>
#include "filemanager.h"
#include <sys/stat.h>
#include <unistd.h>
#include <vector>
#include <limits.h>
#include <iostream>


int main(int argc, char * argv[]) {
    string list = "-l";
    
    //only ls
    if (argc == 1) {
        char current[PATH_MAX];
        filemanager file = filemanager(current);
        file.expand();
        //use iterator to print each child in the directory
        if(S_ISDIR(file.getTypeCode())){
                vector<filemanager>:: iterator iter;
                for (iter = file.getChildren().begin(); iter != file.getChildren().end(); iter++) {
                    printf("%s  ", (*iter).getName());
                }
        }
        
    }
    //ls -l
    if((argc == 2)&(argv[1]==list) ){
        char current[PATH_MAX];
        getcwd(current,PATH_MAX);
        filemanager file = filemanager(current);
        file.getPermission();
        cout<<" "<<file.getOwner();
        cout<<" "<<file.getGroup();
        cout<<" "<<file.getSize();
        cout<<" "<<file.getModTime();
    }
    
    //ls with filename
    if((argc >= 2)&(argv[1]!=list)){
        for (int i = 1; i<=argc-1; i++){
            filemanager file = filemanager(argv[i]);
            if(S_ISDIR(file.getTypeCode())){
                vector<filemanager>:: iterator iter;
                for (iter = file.getChildren().begin(); iter != file.getChildren().end(); iter++) {
                    //cout<<(*iter).getName()<<endl;
                    printf("%s  ", (*iter).getName());
                    }
            }
            if (S_ISREG(file.getTypeCode())) {
                cout<<file.getName()<<endl;
            }
        }
    }
    
    //ls -l filename
    if((argc > 2)&(argv[1]==list)){
        for (int i = 2; i<=argc-1; i++){
            filemanager file = filemanager(argv[i]);
            if(S_ISDIR(file.getTypeCode())){
                vector<filemanager>:: iterator iter;
                for (iter = file.getChildren().begin(); iter != file.getChildren().end(); iter++) {
                    file.getPermission();
                    cout<<" "<<(*iter).getOwner();
                    cout<<" "<<(*iter).getGroup();
                    cout<<" "<<(*iter).getSize();
                    cout<<" "<<(*iter).getModTime();
                    }
            }
            if (S_ISREG(file.getTypeCode())) {
                file.getPermission();
                cout<<" "<<file.getOwner();
                cout<<" "<<file.getGroup();
                cout<<" "<<file.getSize();
                cout<<" "<<file.getModTime();
            }
        }
    }
    
}
