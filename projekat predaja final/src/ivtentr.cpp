/*
 * ivtentr.cpp
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#include "ivtentr.h"
#include <iostream.h>
#include <dos.h>
#include <stdlib.h>
IVTEntry * IVTEntry::ivTable[256];

IVTEntry::IVTEntry(unsigned ivtNum, pInterrupt New){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
#endif
	ivTable[ivtNum] = this;
	this->ivtNum = ivtNum;
	this->myEvent = NULL;

#ifndef BCC_BLOCK_IGNORE
	old = getvect(this->ivtNum);
	setvect(this->ivtNum,New);
#endif
#ifndef BCC_BLOCK_IGNORE
	asm{popf;}
#endif
}

IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
#endif
#ifndef BCC_BLOCK_IGNORE
	setvect(this->ivtNum,old);
	callOld();
	asm{popf;}
#endif
}

void IVTEntry::callOld(){
	if(old)
		(*old)();
}

void IVTEntry::signal(){
	if (this->myEvent)
		this->myEvent->signal();
}


