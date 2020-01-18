//CS3307
//Zhiqi Bei (#250916374)
//zbei@uwo.ca

#include <stdio.h>
#include "filemanager.h"
#include <sys/stat.h>
#include <fstream>
#include <iostream>

int main(int argc, char * argv[]){
    for (int i = 1; i<argc; i++) {
        
        filemanager file(argv[i]);
        
        if (!S_ISREG(file.getTypeCode())) {
            printf("%s is not a regular file", file.getName());
        }
        ifstream outfile(file.getName(),fstream::binary);
        if(! outfile){
                printf("File cannot open");
        }
        file.dump(cout);
        outfile.close();
    }
}
