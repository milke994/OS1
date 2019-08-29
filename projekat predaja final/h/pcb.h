/*
 * pcb.h
 *
 *  Created on: Apr 14, 2017
 *      Author: OS1
 */

#ifndef H_PCB_H_
#define H_PCB_H_

#include "thread.h"
#include "queue.h"

class Queue;

enum Status {NEW, READY, BLOCKED, OVER};

class PCB{
private:
	Status status;

	PCB (Thread *myThread, StackSize stackSize, Time timeSlice);
	virtual ~PCB();

	static void runWrapper();
	static ID UkId;
	ID id;
	void createStack();
	unsigned int ss,sp,bp;
	int WaitResult;
	StackSize stacksize;
	Time timeSlice;
	Time timePassed;
	Thread *myThread;
	Queue *blockedOnWaitToComplete;

	unsigned *stack;



public:
	int volatile val;
	friend class List;
	friend class TList;
	friend class IddleThread;
	friend class Semaphore;
	friend class KernelSem;
	friend class Thread;
	friend class System;
	friend class KernelEv;
	friend class Event;
	friend class KernelBinSemaphore;
};


#endif /* H_PCB_H_ */
