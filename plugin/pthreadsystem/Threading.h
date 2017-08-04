#pragma once
#include "thread/ThreadProperty.h"
#include "core/Predefine.h"

#include <pthread.h>

namespace hpts
{
	class ThreadMutex;
	class Threading//�̻߳�����
	{
	private:
		eastl::string						m_Name;
		ThreadMutex*						m_pMutex;
		pthread_attr_t*						m_pThreadAttr;
		pthread_t*							m_pThreadID;
		hc::ThreadProperty::ThreadPriority	m_ePriority;
		bool								m_isRunning;
	public:
		Threading(void);
		virtual ~Threading(void);
	public:
		static void* ThreadProc( void* param );
	private:
		virtual void _OnStart() = 0;//�߳�����ʱ���¼�
		virtual void _OnReset() = 0;//�߳����³�ʼ���̣߳�׼�������¼�
		virtual bool _StopWork() = 0;//ֹͣ�̹߳������߳�׼���˳�,�����Ƿ�ɹ��˳������ʧ�ܽ�ǿ���˳�
	public:
		virtual void* DoWork() = 0;//�����߳�
	public:
		void Reset();//���³�ʼ���̣߳�׼������
		void Start();//�����߳�
		void Stop();//�ر��߳�
		void SetPriority( hc::ThreadProperty::ThreadPriority tp );
		void SetName(const eastl::string& name);
	public:
		HADES_FORCEINLINE bool isRunning() const;
		HADES_FORCEINLINE hc::ThreadProperty::ThreadPriority GetPriority() const;
	};


	//---------------------------------------------------------------------------------------------------------
	HADES_FORCEINLINE bool Threading::isRunning() const
	{
		return m_isRunning;
	}
	//---------------------------------------------------------------------------------------------------------
	HADES_FORCEINLINE hc::ThreadProperty::ThreadPriority Threading::GetPriority() const
	{
		return m_ePriority;
	}
}

