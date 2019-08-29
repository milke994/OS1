/*
 * ivtentr.h
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#ifndef H_IVTENTR_H_
#define H_IVTENTR_H_
#include "system.h"
#include "listeve.h"

#define PREPAREENTRY(ivtno,old)\
	void interrupt routine##ivtno(...);\
	IVTEntry entry##ivtno(ivtno,routine##ivtno);\
	void interrupt routine##ivtno(...){\
		if(old) entry##ivtno.callOld();\
		entry##ivtno.signal();\
		System::dispatch();\
	}

class KernelEv;
class IVTEntry{
	friend class eList;
	static IVTEntry *ivTable[];
	unsigned ivtNum;
	KernelEv *myEvent;
	pInterrupt old;
	friend class KernelEv;
public:
	IVTEntry(unsigned ivtNum, pInterrupt New);
	~IVTEntry();
	void signal();
	void callOld();
};


#endif /* H_IVTENTR_H_ */
