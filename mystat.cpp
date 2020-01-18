//CS3307
//Zhiqi Bei 
//zbei@uwo.ca

#include <iostream>
#include <vector>
#include "filemanager.h"

int main(int argc, char * argv[]) {
    
    for (int i = 1; i<argc; i++) {
	filemanager file(argv[i]);
	cout<<"File: "<<file.getName()<<endl;
        cout<<"Size: "<<file.getSize()<<"         Blocks: "<<file.getBlockSize()<<endl;
        cout<<"Type: "<<file.getType()<<endl;
        cout<<"Owner: "<<file.getOwner()<<"       Group: "<<file.getGroup()<<endl;
	printf("Permission: (");
	file.getPermission();
	printf(")\n");
	cout<<"Access Time:        "<<file.getAccessTime();
	cout<<"Modification time:  "<<file.getModTime();
	cout<<"Status Change Time: "<<file.getChangeTime();
    }
}
