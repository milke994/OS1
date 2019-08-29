/*
 * listeve.h
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#ifndef H_LISTEVE_H_
#define H_LISTEVE_H_

#include <iostream.h>
#include "KernelEv.h"

class eventList{
	struct Elem{
		KernelEv *event;
		Elem* next;
		Elem(KernelEv *k){
			this->event = k;
			next = NULL;
		}
	};
	friend class KernelEv;
	Elem *head;
public:
	eventList();
	~eventList();
	void put(KernelEv *event);
	void remove(KernelEv *event);
	void signalAll();
};



#endif /* H_LISTEVE_H_ */
