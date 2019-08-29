/*
 * idleth.cpp
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#include "idleth.h"
#include "pcb.h"
#include <iostream.h>

IddleThread::IddleThread() : Thread(800,1){}

void IddleThread::run(){
	while (1) {}
}

void IddleThread::start(){
	this->myPCB->status = READY;
	this->myPCB->createStack();
}
