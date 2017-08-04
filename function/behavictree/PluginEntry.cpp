#include "BehavictreePlugin.h"
#include "core/Predefine.h"
#include "core/Log.h"


namespace hbtf
{
	//����ֻʵ����һ�����ص���Ϊ����û�취���������ƽ��
	HADES_EXTERN HADES_PLUGIN hc::IPlugin* CreateSystem()
	{
		DEBUGLOG( "Local behavictree function loaded!\r\n" );
		return NEW BehavictreePlugin;
	}
	HADES_EXTERN HADES_PLUGIN void DestroySystem(hc::IPlugin* plugin)
	{
		DEBUGLOG( "Local behavictree function release!\r\n" );
		SAFE_DELETE( plugin );
	}
}