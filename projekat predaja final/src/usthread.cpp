/*
 * usthread.cpp
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#include "usthread.h"
#include <iostream.h>
UserThread::UserThread(int argc,char *argv[]) : Thread (2*defaultStackSize, 0){
	this->argc = argc;
	this->argv = argv;
	retValue = 0;
}

void UserThread::run(){
	this->retValue = userMain(this->argc, this->argv);
}

