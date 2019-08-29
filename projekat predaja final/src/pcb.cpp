/*
 * pcb.cpp
 *
 *  Created on: May 3, 2017
 *      Author: OS1
 */

#include "pcb.h"
#include <stdlib.h>
#include <iostream.h>
#include <dos.h>
#include "thread.h"
#include "lista.h"
#include"system.h"
#include "SCHEDULE.H"

ID PCB::UkId = 0;

PCB::PCB(Thread *myThread, StackSize stackSize, Time timeSlice){
	this->timeSlice = timeSlice;
	this->myThread = myThread;
	if (stackSize > 0x8000) this->stacksize = 0x8000;
	else this->stacksize = stackSize;
	this->timePassed = 0;
	this->WaitResult = 0;
	id = ++UkId;
	ss = 0;
	bp = 0;
	sp = 0;
	this->val = 0;
	status = NEW;
	blockedOnWaitToComplete = new Queue();
	this->stack = NULL;
}

PCB::~PCB(){
	delete blockedOnWaitToComplete;
	delete[] stack;
	System::GlList->deleteThread(this->myThread);
}

void PCB::runWrapper(){
	System::running->myThread->run();
	lock
	System::running->status = OVER;
	while (System::running->blockedOnWaitToComplete->notEmpty()){
		PCB *pcb = System::running->blockedOnWaitToComplete->get();
		pcb->status = READY;
		Scheduler::put(pcb);
	}
	unlock
	System::dispatch();
}

void PCB::createStack(){
	int i = 1;
	stack = new unsigned[stacksize / 2];
	StackSize n = stacksize / 2;
	stack[n-i] = 0x200;
	i++;
#ifndef BCC_BLOCK_IGNORE
	stack[n-i] = FP_SEG(PCB::runWrapper);
	i++;
	stack[n-i] = FP_OFF(PCB::runWrapper);
	i++;
#endif
	for(;i < 12;i++){
		stack[n - i] = 0;
	}
#ifndef BCC_BLOCK_IGNORE
	sp = FP_OFF(stack + n - i);
	ss = FP_SEG(stack + n - i);
	bp = FP_OFF(stack + n - i);
#endif
}
