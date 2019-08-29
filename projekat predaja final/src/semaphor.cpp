/*
 * semaphor.cpp
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#include "semaphor.h"
#include "system.h"
#include "KerSem.h"

Semaphore::Semaphore(int initval){
	lock
	myImpl = new KernelSem(initval);
	unlock
}

Semaphore::~Semaphore(){
	lock
	delete myImpl;
	unlock
}

int Semaphore::wait(Time maxWait){
	lock
	myImpl->wait(maxWait);
	unlock
	return(System::running->WaitResult);
}

void Semaphore::signal(){
	lock
	myImpl->signal();
	unlock
}

int Semaphore::val()const{
	return myImpl->val();
}

