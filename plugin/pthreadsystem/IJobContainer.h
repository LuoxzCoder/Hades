#pragma once
#include "core/SmartPtr.hpp"
#include "thread/IJob.h"


namespace hpts
{
	//���Ϊ������,��������ȥ�̳�������߳̿��Զ�̬�ı�������ͣ�����Ŀǰû�������ݻ�
	class IJobContainer
	{
	public:
		IJobContainer(void){}
		virtual ~IJobContainer(void){}
	public:
		virtual void Clear() = 0;
		virtual bool TryPopJob(hc::SmartPtr<hc::IJob>& job) = 0;
		virtual void PushJob(hc::SmartPtr<hc::IJob>& job) = 0;
		virtual uint Size() = 0;
	};
}
