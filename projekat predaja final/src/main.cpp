/*
 * main.cpp
 *
 *  Created on: May 17, 2017
 *      Author: OS1
 */
#include "system.h"
#include <stdlib.h>

extern int userMain(int argc, char *argv[]);
int main(int argc,char* argv[]){
	System::init();
	System::retValue = userMain(argc,argv);
	System::restore();
	return System::retValue;
}



