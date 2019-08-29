/*
 * thread.h
 *
 *  Created on: Apr 13, 2017
 *      Author: OS1
 */

#ifndef H_THREAD_H_
#define H_THREAD_H_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
class PCB; // Kernel's implementation of a user's thread

class Thread {
public:

	void start();
	void waitToComplete();
	virtual ~Thread();
	ID getId();
	static ID getRunningId();
	static Thread * getThreadById(ID id);

protected:
	friend class IddleThread;
	friend class System;
	friend class Thread;
	friend class UserThread;
	friend class PCB;
	friend class List;
	friend class TList;
	Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}

private:
	PCB* myPCB;
};


	void dispatch ();

#endif /* H_THREAD_H_ */
