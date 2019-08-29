/*
 * lista.cpp
 *
 *  Created on: May 5, 2017
 *      Author: OS1
 */

#include "lista.h"
#include "pcb.h"

void List::deleteThread(Thread *thread){
	Element *current = head;
	Element *past = 0;
	while ((current != 0) && (current->info != thread)) {
		past = current;
		current = current->next;
	}
	if(current != 0){
		if (past) past->next = current->next;
		else head = current->next;
		current->info = 0;
		delete current;
	}
}

Thread* List::getThreadById(ID id){
	Element *current = head;
	while((current) && (current->info->myPCB->id != id)) current = current->next;
	if (!current) return 0;
	else
		return current->info;
}

void List::put(Thread *thread){
	if (thread != 0){
		Element *neew = new Element(thread);
		if (head == 0) head == neew;
		else {
			neew->next = head;
			head = neew;
		}
	}
}

