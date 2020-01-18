//CS3307
//Zhiqi Bei 
//zbei@uwo.ca

#include "filemanager.h"
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("The input is incorrect");
    }
    filemanager file1 = filemanager(argv[1]);
    filemanager file2 = filemanager(argv[2]);
    
    //check if the file is exist
    if(access(file1.getName(), 0) == -1){
        file1.setErrorNum(2);
        cout<<"Error: "<<file1.getName()<<" "<<file1.getError()<<endl;
    }else{
	if(!S_ISREG(file1.getTypeCode())){
        cout<<"Error: "<<file1.getName()<<" is not a regular file"<<endl;
	}
    }
    fstream outfile(file2.getName(),fstream::binary);
    fstream infile(file1.getName(),fstream::binary);
    //file1.dump(out);
    //fstream out;
     outfile.open(file2.getName(),fstream::binary);
    if(outfile.is_open()){
	    file1.dump(outfile);
    }
    else{
	    //printf("Error");
	    cout<<file1.getError()<<endl;
	    cout<<file2.getErrorNum()<<endl;
    }
}
