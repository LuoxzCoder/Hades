#pragma once
#include "thread/IThreadRWLock.h"



namespace hpts
{
	class ThreadRWLock : public hc::IThreadRWLock
	{
	private:
		void*	m_pRWLock;
	public:
		ThreadRWLock(void);
		virtual ~ThreadRWLock(void);
	public:
		virtual void ReadLock();//����ʽ�Ķ�ȡ��
		virtual void WriteLock();//��ռ��д����
		virtual void Unlock();//����
	};
}
