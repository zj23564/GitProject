#ifndef _MUTEX_H_
#define _MUTEX_H_

#include <pthread.h>
//#include "comhead.h"

/*********************************************************************
*Role:CMutex Class                                                   *
*History:                                                            *
*	Create by flydish,2004,06,25                                 *
*********************************************************************/

class CMutex
{
    friend class CConditionM;

protected:
    pthread_mutex_t     _mutex;
    pthread_mutexattr_t _mutex_attr;

public:
    CMutex()
    {
	pthread_mutexattr_init( &_mutex_attr );
	pthread_mutex_init( &_mutex, &_mutex_attr );
    }

    ~CMutex()
    {
	pthread_mutex_destroy( &_mutex );
	pthread_mutexattr_destroy( &_mutex_attr );
    }

    int lock() { return pthread_mutex_lock( &_mutex ); }
    int unlock() { return pthread_mutex_unlock( &_mutex ); }

    int trylock() { return pthread_mutex_trylock( &_mutex ); }
};


/*********************************************************************
*Role:CCondition Class                                                   *
*History:                                                            *
*	Create by flydish,2004,06,25                                 *
*********************************************************************/

class CConditionM
{
protected:
    pthread_cond_t  _cond;

public:
    CConditionM() { pthread_cond_init( &_cond, NULL ); }
    ~CConditionM() { pthread_cond_destroy( &_cond ); }

    void wait( CMutex& m ){
	pthread_cond_wait( &_cond, &m._mutex );
    }

    void signal(){
	pthread_cond_signal( &_cond );
    }

    void broadcast(){
	pthread_cond_broadcast( &_cond );
    }
};

/*********************************************************************
*Role:CCondition Class                                                   *
*History:                                                            *
*	Create by flydish,2004,06,25                                 *
*********************************************************************/
class CSemaphore
{
protected:
    int         _value;
    CMutex      _mutex;
    CConditionM _cond;
public:
    CSemaphore( int c=0 ):_value(c){}
    ~CSemaphore(){}
    int value() const { return _value; }
    void init(int c);
    void inc();
    void dec();
};



#endif
