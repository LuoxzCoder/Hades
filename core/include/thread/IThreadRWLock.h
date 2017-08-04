#pragma once
#include "IThreadEntity.h"



namespace hc
{
	class HADES_CORE_API IThreadRWLock : public IThreadEntity
	{//��д��
		RTTI_ABSTRACT_DRIVER_TYPE_DECLEAR(IThreadRWLock, IThreadEntity)
	public:
		IThreadRWLock():IThreadEntity( ThreadProperty::ET_RWLOCK ){}
		virtual ~IThreadRWLock(void){};
	public:
		virtual void ReadLock() = 0;//����ʽ�Ķ�ȡ��
		virtual void WriteLock() = 0;//��ռ��д����
		virtual void Unlock() = 0;//����
	};
}