/*
 * lista.h
 *
 *  Created on: May 5, 2017
 *      Author: OS1
 */

#ifndef H_LISTA_H_
#define H_LISTA_H_

#include "thread.h"

class Element{
public:
	Thread* info;
	Element *next;
	Element(Thread *neew){
		info = neew;
		next = 0;
	}
};

class List{
public:
	Element *head;
	Thread* getThreadById(ID id);
	void put(Thread *pcb);
	void deleteThread(Thread *pcb);
	List(){
		head = 0;
	}
};


#endif /* H_LISTA_H_ */
