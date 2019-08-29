/*
 * event.h
 *
 *  Created on: May 16, 2017
 *      Author: OS1
 */

#ifndef H_EVENT_H_
#define H_EVENT_H_

#include "ivtentr.h"

typedef unsigned char IVTNo;
class KernelEv;
class Event{
public:
	Event (IVTNo ivtNo);
	~Event();
	void wait();
protected:
	friend class KernelEv;
	void signal();
private:
	KernelEv* myImpl;
};



#endif /* H_EVENT_H_ */
