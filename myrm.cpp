//CS3307
//Zhiqi Bei 
//zbei@uwo.ca

#include <stdio.h>
#include "filemanager.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char * argv[]) {
    if(argc<2){
        printf("The input is incorrect");
    }
    else{
        for (int i = 1; i<=argc-1; i++) {
            //check is file exist
            fstream check;
            check.open(argv[i]);
            if(!check){
				printf("cannot remove %s : No such file or directory\n",argv[i]);
            }
            filemanager file = filemanager(argv[i]);
            int num = file.remove();
            
            //if not remove successfully
            if (num != 0) {
                string error = file.getError();
                cout<<error<<endl;
            }
        }
    }
}
