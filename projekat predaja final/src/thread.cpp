/*
 * thread.cpp
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#include "thread.h"
#include <iostream.h>
#include <stdlib.h>
#include <dos.h>
#include "pcb.h"
#include "SCHEDULE.H"
#include "system.h"

Thread::Thread(StackSize stackSize,Time timeSlice){
	lock
	myPCB = new PCB(this,stackSize,timeSlice);
	System::GlList->put(this);
	unlock
}

Thread::~Thread(){
	waitToComplete();
	lock
	delete myPCB;
	unlock
}

void Thread::waitToComplete(){
	lock
	if(System::running != this->myPCB){
		if(this->myPCB->status == OVER || this->myPCB == System::iddle){
			unlock
			return;
		}
		System::running->status = BLOCKED;
		this->myPCB->blockedOnWaitToComplete->put(System::running);
		System::dispatch();
	}
	unlock
}

void Thread::start(){
	lock
	myPCB->status = READY;
	myPCB->createStack();
	Scheduler::put(myPCB);
	unlock
}

ID Thread::getId(){
	return myPCB->id;
}

ID Thread::getRunningId(){
	return System::running->id;
}

Thread* Thread::getThreadById(ID id){
	Thread *result = System::GlList->getThreadById(id);
	if (!result) return 0;
	else return result;
}

void dispatch(){
	lock
	System::dispatch();
	unlock
}
