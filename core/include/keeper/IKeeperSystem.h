#pragma once
#include "core/Singleton.hpp"
#include "core/Delegate.hpp"
#include "core/IPlugin.h"



#include <EASTL/string.h>
#include <EASTL/vector.h>

namespace hc
{
	class Accessor;
	class IAccessPackage;	
	//���̷߳��ʿ�����
	//ʵ�ֽӿڵļ̳��߷��صı������ڴ�ı��ݣ����ܷ����ڴ汾����ֹ�ڵ���
	//���ϸ�ģʽ��ȡ��дģʽ��дͬһ���ڴ���������ı���
	class HADES_CORE_API IKeeperSystem : public IPlugin
	{
		SYSTEM_SINGLETON_DECLEAR(IKeeperSystem);
		RTTI_ABSTRACT_DRIVER_TYPE_DECLEAR(IKeeperSystem, IPlugin);
	public:
		IKeeperSystem(void);
		virtual ~IKeeperSystem(void);
	public:
		virtual void Initialize();
		virtual void Exit();
	public:
		//��������ݲ���������һ�����ݵ������
		virtual IAccessPackage* AccessPackageFactory() = 0;
		virtual void RecycleBin(IAccessPackage* package) = 0;
		virtual void RequestAccessor(IAccessPackage* pack) = 0;
	public:
		static inline int IncreaseTimestamp(int old);
	};


	//---------------------------------------------------------------------------------------------------------
	int IKeeperSystem::IncreaseTimestamp(int old)
	{
		return old + 1;
	}
}
