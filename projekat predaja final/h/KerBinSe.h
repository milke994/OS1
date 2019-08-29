/*
 * KerBinSe.h
 *
 *  Created on: May 29, 2017
 *      Author: OS1
 */

#ifndef H_KERBINSE_H_
#define H_KERBINSE_H_
#include "KernelEv.h"

class KernelBinSemaphore{
private:
	int value;
	KernelEv *myKernelEvent;
public:
	KernelBinSemaphore(KernelEv *myKernel);
	void signal();
	void wait();

};



#endif /* H_KERBINSE_H_ */
