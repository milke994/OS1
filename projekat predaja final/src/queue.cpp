/*
 * queue.cpp
 *
 *  Created on: Apr 14, 2017
 *      Author: OS1
 */

#include "queue.h"
#include<iostream.h>

void Queue::put(PCB * neew) {
	Element *novi = new Element(neew);
	if (first)
		last->next = novi;
	else
		first = novi;
	last = novi;
}

Queue::~Queue(){
	Element *current, *past;
	current = first;
	while (current){
		past = current;
		current = current->next;
		delete(past);
	}
	first = last = 0;
}

void Queue::removePCB(PCB* pcb){
	Element *current, *past;
	current = first;
	past = 0;
	while (current && current->info != pcb){
		past = current;
		current = current->next;
	}
	if (current){
	if (!past) first = current->next;
	else{
		past->next = current->next;
		current->next = 0;
	}
	if (current == last) last = past;
	delete(current);
	}
}

PCB* Queue::get(){
	PCB *result;
	Element *out;
	if (first){
		out = first;
		result = first->info;
		first = first->next;
		if (!first) last = 0;
		delete(out);
		return result;
	}
	else
		return 0;
}









