#include "ThreadRWLock.h"


#include <pthread.h>


namespace hpts
{
	//------------------------------------------------------------------------------------------------------
	ThreadRWLock::ThreadRWLock(void)
	{
		m_pRWLock = NEW pthread_rwlock_t;
		pthread_rwlock_init( static_cast<pthread_rwlock_t*>(m_pRWLock), NULL );
	}
	//------------------------------------------------------------------------------------------------------
	ThreadRWLock::~ThreadRWLock(void)
	{
		pthread_rwlock_destroy( static_cast<pthread_rwlock_t*>(m_pRWLock) );
		delete static_cast<pthread_rwlock_t*>(m_pRWLock);
	}
	//------------------------------------------------------------------------------------------------------
	void ThreadRWLock::ReadLock()//����ʽ�Ķ�ȡ��
	{
		pthread_rwlock_rdlock( static_cast<pthread_rwlock_t*>(m_pRWLock) );
	}
	//------------------------------------------------------------------------------------------------------
	void ThreadRWLock::WriteLock()//��ռ��д����
	{
		pthread_rwlock_wrlock( static_cast<pthread_rwlock_t*>(m_pRWLock) );
	}
	//------------------------------------------------------------------------------------------------------
	void ThreadRWLock::Unlock()//����
	{
		pthread_rwlock_unlock( static_cast<pthread_rwlock_t*>(m_pRWLock) );
	}
}