/*
 * queue.h
 *
 *  Created on: Apr 14, 2017
 *      Author: OS1
 */

#ifndef H_QUEUE_H_
#define H_QUEUE_H_

class PCB;

class Queue{
private:
	struct Element{
		PCB *info;
		Element *next;
		Element(PCB* neew){
			info = neew;
			next = 0;
		}
	};
	friend class PCB;
public:
	Element *first, *last;

	Queue(){first = last = 0;}
	~Queue();

	int notEmpty(){
			if (first) return 1;
			else return 0;
		}

	PCB* get();

	void put(PCB*  pcb);

	void removePCB(PCB * pcb);
};




#endif /* H_QUEUE_H_ */
