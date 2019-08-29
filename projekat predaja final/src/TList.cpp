/*
 * TList.cpp
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#include <iostream.h>
#include "tlist.h"

TList::TList(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
#endif
	head = 0;
#ifndef BCC_BLOCK_IGNORE
	asm{
		popf;
	}
#endif
}

TList::~TList(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
#endif
	ElementOfTimeList *help, *current;
	current = head;
	while (current){
		help = current;
		current = current->next;
		delete help;
	}

#ifndef BCC_BLOCK_IGNORE
	asm{ pushf; }
#endif
}

void TList::put(Thread *thread, Time time, KernelSem *semaph){
#ifndef BCC_BLOCK_IGNORE
	asm{cli;}
#endif
	ElementOfTimeList *n = new ElementOfTimeList(thread,time,semaph);
	ElementOfTimeList *current = head;
	ElementOfTimeList *past = 0;

	while (current && current->timeToWait < n->timeToWait){
		n->timeToWait = n->timeToWait - current->timeToWait;
		past = current;
		current = current->next;
	}
	if (current) current->timeToWait = current->timeToWait - n->timeToWait;
	n->next = current;
	if (past) past->next = n;
	else
		head = n;
}

void TList::removeThread(Thread *thread){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
#endif
	ElementOfTimeList *current = head;
	ElementOfTimeList *past = 0;
	while (current && current->info != thread){
		past = current;
		current = current->next;
	}
	if (current){
		if (past)
			past->next = current->next;
		else
			head = current->next;
		if (current->next)
			current->next->timeToWait = current->next->timeToWait + current->timeToWait;
		delete current;
	}
#ifndef BCC_BLOCK_IGNORE
	asm{popf;}
#endif
}

int TList::isEmpty(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
#endif
	int result = 1;
	if (head) result = 0;
#ifndef BCC_BLOCK_IGNORE
	asm{popf;}
#endif
	return result;
}

Thread* TList::get(){
	Thread* result;
	ElementOfTimeList *current = head;
	current->mySemaph->queue->removePCB(current->info->myPCB);
	current->info->myPCB->status = READY;
	current->mySemaph->value++;
	current->info->myPCB->WaitResult = 0;
	result = current->info;
	head = head->next;
	delete current;
	return result;
}
