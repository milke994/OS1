/*
 * system.cpp
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#include "system.h"
#include<iostream.h>
#include<stdlib.h>
#include<stdio.h>
#include<dos.h>
#include "pcb.h"
#include "SCHEDULE.H"
#include "usthread.h"

volatile int System::forced = 0;
volatile unsigned int System::flag = 0;
PCB* System::running = 0;
PCB* System::starting = 0;
PCB* System::iddle = 0;

pInterrupt System::Old = 0;
int System::retValue = 0;
List* System::GlList;
TList* System::TimeList;
ElementOfTimeList *current;
unsigned tsp,tss,tbp;
IddleThread* iddlethread;
int System::numberim = 0;

void System::wakeUp(){
	if (TimeList && TimeList->head){
		if(TimeList->head->timeToWait > 0)
			TimeList->head->timeToWait--;
		while (TimeList->head && TimeList->head->timeToWait == 0){
			Scheduler::put(TimeList->get()->myPCB);
		}
	}
}

void System::ReplaceRoutine(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
#endif
#ifndef BCC_BLOCK_IGNORE
	System::Old = getvect(0x08);
	setvect(0x08,System::timer);
	setvect(0x60,Old);
#endif
#ifndef BCC_BLOCK_IGNORE
	asm{popf;}
#endif
}

void System::restoreInterrupt(){
#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf;
		cli;
	}
	setvect(0x08,Old);
	asm{popf;}
#endif
}

void System::dispatch(){
#ifndef BCC_BLOCK_IGNORE
	asm {
		pushf;
		cli;
	}
#endif
	forced = 1;
	System::timer();
#ifndef BCC_BLOCK_IGNORE
	asm{
		popf;
	}
#endif
}

void System::init(){
	GlList = new List();
	TimeList = new TList();
	System::forced = 0;
	System::running = new PCB(0,0,0);
	System::running->timeSlice = 0;
	System::starting = System::running;
	System::running->status = READY;
	iddlethread = new IddleThread();
	System::iddle = iddlethread->myPCB;
	iddlethread->start();

	System::ReplaceRoutine();

}

void System::restore(){
	System::restoreInterrupt();
	delete iddle->myThread;
	delete System::running;
	delete GlList;
	delete TimeList;
}

void interrupt System::timer(...){
	if (!forced){
		(*Old)();
		System::running->timePassed++;
		System::wakeUp();
		tick();
	}
	if (forced || (System::running->timePassed >= running->timeSlice && System::running->timeSlice != 0)){
		if ((System::running->val > 0) && (!forced)){
			flag = 1;
			return;
		}
		forced = 0;
#ifndef BCC_BLOCK_IGNORE
		asm{
			mov tsp, SP
			mov tss, SS
			mov tbp, BP
		}
#endif
		System::running->ss = tss;
		System::running->sp = tsp;
		System::running->bp = tbp;

		if(System::running->status == READY && System::running != System::iddle){
			Scheduler::put(System::running);
		}
		System::running = Scheduler::get();
		if (System::running == 0){
			System::running = System::iddle;
		}
		tsp = System::running->sp;
		tss = System::running->ss;
		tbp = System::running->bp;
#ifndef BCC_BLOCK_IGNORE
		asm{
			mov SP,tsp
			mov SS,tss
			mov BP,tbp
		}
#endif
		System::running->timePassed = 0;
	}
	//if(!forced) (*Old)();
}
