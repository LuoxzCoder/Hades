#include "core/IPlugin.h"
#include "IPluginLoader.h"



using namespace eastl;
namespace hc
{
	RTTI_TYPE_IMPLEMENT( IPluginLoader );
	//---------------------------------------------------------------------------------------------------------
	IPluginLoader::IPluginLoader(void)
	{
	}
	//---------------------------------------------------------------------------------------------------------
	IPluginLoader::~IPluginLoader(void)
	{
	}
	//---------------------------------------------------------------------------------------------------------
	IPlugin* IPluginLoader::LoadPlugin( const eastl::string& name )
	{
		IPlugin* res = _DoLoadPlugin( name );									// ����һ���µĲ��DLL���̣�����DLL�Ľ���ID�Ͳ����Ϣ��¼��m_LoadedPluginMap��
		if ( res )
		{
			IPluginMap::iterator it = m_IPluginMap.find( res->GetTypeID() );
			if ( it != m_IPluginMap.end() )
			{
				_DoReleasePlugin( res );										// �ҵ��ˣ�ɾ��m_LoadedPluginMap�еĸ�ͨ��_DoLoadPlugin()���������Ĳ��������m_LoadedPluginMap֮ǰ���ع���ͬ�������
				res = it->second;
			}
			else
			{

				m_IPluginMap.insert( make_pair( res->GetTypeID(), res ) );		// û�ҵ���ͬʱ��m_IPluginMap�в����µĲ����Ϣ
			}
		}
		return res;
	}
	//---------------------------------------------------------------------------------------------------------
	void IPluginLoader::ReleasePlugin( IPlugin* plugin )
	{
		//�Ƿ��ظ�ɾ��
		m_IPluginMap.erase( plugin->GetTypeID() );
		_DoReleasePlugin( plugin );
	}

}