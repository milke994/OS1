/*
 * TList.h
 *
 *  Created on: May 5, 2017
 *      Author: OS1
 */

#ifndef H_TLIST_H_
#define H_TLIST_H_

#include "kersem.h"
#include"thread.h"

class KernelSem;
class ElementOfTimeList{
public:
	Thread *info;
	Time timeToWait;
	KernelSem *mySemaph;
	ElementOfTimeList *next;
	ElementOfTimeList(Thread *thread, Time time, KernelSem *semaph, ElementOfTimeList *n = 0){
		this->info = thread;
		this->timeToWait = time;
		this->mySemaph = semaph;
		this->next = n;
	}
};
class TList{
	ElementOfTimeList *head;
public:
	TList();
	~TList();
	void put(Thread *thread,Time time, KernelSem *semaph);
	void removeThread(Thread *thread);
	int isEmpty();
	Thread* get();
	friend class System;
};



#endif /* H_TLIST_H_ */
