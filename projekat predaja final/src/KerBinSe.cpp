/*
 * KerBinSe.cpp
 *
 *  Created on: May 29, 2017
 *      Author: OS1
 */

#include "KernelEv.h"
#include "SCHEDULE.H"
#include <iostream.h>


KernelBinSemaphore::KernelBinSemaphore(KernelEv *myKernel){
	value = 0;
	myKernelEvent = myKernel;
}

void KernelBinSemaphore::signal(){
	if (this->value == -1){
			this->value = 0;
			myKernelEvent->owner->status = READY;
			Scheduler::put(myKernelEvent->owner);
		}
		else{
			this->value = 1;
		}
}

void KernelBinSemaphore::wait(){
	if (System::running == myKernelEvent->owner){
			if (this->value == 1)
				this->value = 0;
			else
				if(this->value == 0){
					this->value = -1;
					myKernelEvent->owner->status = BLOCKED;
					System::dispatch();
				}
		}
}
