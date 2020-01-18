//CS3307
//Zhiqi Bei (#250916374)
//zbei@uwo.ca


#include <stdio.h>
#include "filemanager.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char * argv[]) {
    if(argc != 3){
        printf("The input is incorrect");
    }
    //check if the file is exist
    fstream check1;
    check1.open(argv[1]);
    if(!check1){
		printf("%s: No such file",argv[1]);
	}
	fstream check2;
    check2.open(argv[2]);
    if(!check2){
		printf("%s: No such file",argv[2]);
	}
	
    filemanager file1(argv[1]);
    filemanager file2(argv[2]);
    //compare the two files
    if(file1.getSize() != file2.getSize()){
	printf("The files are different");
    }else{
	int same = file1.compare(file2);
	if (same != 0) {
	    printf("The files are different");
	}
	else{
	    printf("The file is the same");
	}
    }
    check1.close();
    check2.close();
}
