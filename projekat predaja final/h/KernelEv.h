/*
 * kevent.h
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#ifndef H_KERNELEV_H_
#define H_KERNELEV_H_

#include "pcb.h"
#include "ivtentr.h"
#include "KerBinSe.h"

typedef unsigned char IVTNo;

class KernelEv{
	PCB *owner;
	IVTNo ivtNum;
	KernelBinSemaphore *myBinSemaphore;
	friend class KernelBinSemaphore;
public:
	KernelEv(IVTNo ivtNum);
	~KernelEv();
	void signal();
	void wait();
};


#endif /* H_KERNELEV_H_ */
