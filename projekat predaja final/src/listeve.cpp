/*
 * listeve.cpp
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#include "listeve.h"

eventList::eventList(){
	head = 0;
}

eventList::~eventList(){
	Elem *past, *current;
	current = head;
	while (current){
		past = current;
		current = current->next;
		delete past;
	}
}

void eventList::signalAll(){
	Elem *current = head;
	while (current){
		current->event->signal();
		current = current->next;
	}
}

void eventList::put(KernelEv *event){
	Elem *current = head;
	head = new Elem(event);
	head->next = current;
}

void eventList::remove(KernelEv *event){
	Elem *past, *current;
	past = NULL;
	current = head;
	while(current && current->event != event){
		past = current;
		current = current->next;
	}
	if(current){
		if(past)
			past->next = current->next;
		else
			head = current->next;
		delete current;
	}
}


