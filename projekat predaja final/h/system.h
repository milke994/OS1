/*
 * system.h
 *
 *  Created on: May 5, 2017
 *      Author: OS1
 */

#ifndef H_SYSTEM_H_
#define H_SYSTEM_H_

#include "thread.h"
#include "pcb.h"
#include "lista.h"
#include "tlist.h"
#include "idleth.h"
#include "lock.h"
typedef void interrupt(*pInterrupt)(...);



class TList;
class GlList;
class System{
public:
	static PCB *running;
	static PCB *iddle;
	static PCB *starting;
	static TList *TimeList;
	static List *GlList;
	volatile static unsigned int flag;
	volatile static int forced;
	static pInterrupt Old;
	static int retValue;
	static void interrupt timer(...);

	static int numberim;
	static void ReplaceRoutine();
	static void restoreInterrupt();

	static void dispatch();
	static void wakeUp();
	static void init();
	static void restore();
	friend class PCB;
	friend class TList;
	friend class Thread;
};

extern void tick();

#endif /* H_SYSTEM_H_ */
