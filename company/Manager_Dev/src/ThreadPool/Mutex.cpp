//#ifndef _MUTEX_H_
//#define _MUTEX_H_
#include "../../include/ThreadPool/Mutex.h"
#include <pthread.h>
//#include "comhead.h"

/*********************************************************************
*Role:CMutex Class                                                   *
*History:                                                            *
*	Create by flydish,2004,06,25                                 *
*********************************************************************/


void CSemaphore::init( int c )
{
    _mutex.lock();
    _value = c;
    _mutex.unlock();
    _cond.signal();
}

void CSemaphore::inc()
{
    _mutex.lock();
    _value++;
    _mutex.unlock();
    _cond.signal();
}

void CSemaphore::dec()
{
    _mutex.lock();
    while ( _value <= 0 )
	_cond.wait( _mutex );
    _value--;
    _mutex.unlock();
}
//#endif

