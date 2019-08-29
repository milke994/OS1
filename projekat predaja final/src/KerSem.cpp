/*
 * KerSem.cpp
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#include <iostream.h>

#include "kersem.h"
#include "system.h"
#include "SCHEDULE.H"

KernelSem::KernelSem(int initvalue){
	queue = new Queue();
	value = initvalue;
}

KernelSem::~KernelSem(){
	PCB *pcb;
	while (queue->notEmpty()){
		pcb = queue->get();
		System::TimeList->removeThread(pcb->myThread);
		pcb->status = READY;
		Scheduler::put(pcb);
	}
	delete queue;
}

void KernelSem::signal(){
	if (value++ < 0 && queue->notEmpty()){
		unblock();
	}
}

void KernelSem::unblock(){
	PCB *pcb = queue->get();
	System::TimeList->removeThread(pcb->myThread);
	pcb->WaitResult = 1;
	pcb->status = READY;
	Scheduler::put(pcb);
}

void KernelSem::wait(Time maxWait){
	if (--value < 0){
		block(maxWait);
	}
}

void KernelSem::block(Time maxWait){
	PCB *pcb = System::running;
	pcb->status = BLOCKED;
	queue->put(pcb);
	if (maxWait > 0)
		System::TimeList->put(pcb->myThread,maxWait,this);
	System::dispatch();
}

int KernelSem::val() const{
	return value;
}


