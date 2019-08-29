/*
 * kevent.cpp
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#include "SCHEDULE.H"
#include <iostream.h>
#include "KernelEv.h"

KernelEv::KernelEv(IVTNo ivtNum){
	if (IVTEntry::ivTable[ivtNum]){
		this->ivtNum = ivtNum;
		myBinSemaphore = new KernelBinSemaphore (this);
		this->owner = System::running;
		IVTEntry::ivTable[ivtNum]->myEvent = this;
	}
}

KernelEv::~KernelEv(){
	IVTEntry::ivTable[ivtNum]->myEvent = 0;
	delete myBinSemaphore;
}

void KernelEv::signal(){
	myBinSemaphore->signal();
}

void KernelEv::wait(){
	myBinSemaphore->wait();
}


