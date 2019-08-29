#ifndef KERSEM_H_
#define KERSEM_H_

#include "pcb.h"
#include "system.h"
#include "queue.h"

class KernelSem{
	int value;
	Queue *queue;
	friend class System;
	friend class TList;
public:
	KernelSem(int init);
	~KernelSem();
	void wait(Time maxWait);
	void signal();
	int val() const;

protected:
	void block(Time maxWait);
	void unblock();
};


#endif
