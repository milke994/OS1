/*
 * event.cpp
 *
 *  Created on: May 17, 2017
 *      Author: OS1
 */

#include <iostream.h>
#include "event.h"
#include "KernelEv.h"
#include "system.h"

Event::Event(IVTNo ivtNo){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
#endif
	this->myImpl = new KernelEv(ivtNo);

#ifndef BCC_BLOCK_IGNORE
	asm{
		popf;
	}
#endif
}

Event::~Event(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
#endif
	delete myImpl;
#ifndef BCC_BLOCK_IGNORE
	asm{
		popf;
	}
#endif
}

void Event::wait(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
#endif
	this->myImpl->wait();
#ifndef BCC_BLOCK_IGNORE
	asm{
		popf;
	}
#endif
}

void Event::signal(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
#endif
	this->myImpl->signal();
#ifndef BCC_BLOCK_IGNORE
	asm{
		popf;
	}
#endif
}

