#include "WindowsPluginLoader.h"
#include "core/IPlugin.h"

using namespace eastl;
using namespace hc;
namespace hcw
{
	//---------------------------------------------------------------------------------------------------------
	WindowsPluginLoader::WindowsPluginLoader(void)
	{
	}

	//---------------------------------------------------------------------------------------------------------
	WindowsPluginLoader::~WindowsPluginLoader(void)
	{
	}

	//---------------------------------------------------------------------------------------------------------
	IPlugin* WindowsPluginLoader::_DoLoadPlugin(const eastl::string& name)
	{
		IPlugin* res = NULL;
		string fullname;
#ifdef _DEBUG
		fullname = name + "_d.dll";
#else
		fullname = name + ".dll";
#endif // _DEBUG		
		HMODULE hmodule = LoadLibraryA(fullname.c_str());
		ASSERT(NULL != hmodule);
		// �õ������nameָ����dll�е�"Create_Plugin"�����ķ��ص�ַ��Ҳ���ǵõ������IPlugin* Create_Plugin()������ַ��
		IPluginLoader::EntryFuncPtr func = (IPluginLoader::EntryFuncPtr)GetProcAddress(hmodule, "CreateSystem");
		if (func)	// ��������ɹ�
		{
			PluginData data;
			data.m_Name = name;
			data.m_pPlugin = func();
			data.m_Handle = hmodule;
			m_LoadedPluginMap.insert(make_pair(data.m_pPlugin->GetObjectID(), data));		// ��m_LoadedPluginMap�в�������Ϣ
			res = data.m_pPlugin;
		}
		return res;
	}

	//---------------------------------------------------------------------------------------------------------
	void WindowsPluginLoader::_DoReleasePlugin(IPlugin* plugin)
	{
		PluginMap::iterator pluginData = m_LoadedPluginMap.find(plugin->GetObjectID());
		// �õ������nameָ����dll�е�"Destroy_Plugin"�����ķ��ص�ַ��Ҳ���ǵõ������void Destroy_Plugin()������ַ��
		IPluginLoader::ExitFuncPtr func = (IPluginLoader::ExitFuncPtr)GetProcAddress(pluginData->second.m_Handle, ("DestroySystem"));
		func(pluginData->second.m_pPlugin);								// ���ٲ��
		FreeLibrary(pluginData->second.m_Handle);
		m_LoadedPluginMap.erase(plugin->GetObjectID());					// ��m_LoadedPluginMap��ɾ�������Ϣ
	}

	//---------------------------------------------------------------------------------------------------------
	bool WindowsPluginLoader::LoadDefualtPlugin(const eastl::string& path, eastl::list< IPlugin* >& list)
	{
		IPlugin* p1 = LoadPlugin(path + "plugin/windowsfilesystem");
		IPlugin* p2 = LoadPlugin(path + "plugin/fileconsolelogsystem");
		IPlugin* p3 = LoadPlugin(path + "plugin/jsonconfiguresystem");	//����Ĭ�ϵ��������		
		if (p1 && p2 && p3)
		{
			list.push_back(p1);
			list.push_back(p2);
			list.push_back(p3);
			return true;
		}
		return false;
	}
	//---------------------------------------------------------------------------------------------------------
	void WindowsPluginLoader::AddLibraryPath(const eastl::string& path)
	{
		SetDllDirectoryA(path.c_str());
	}
}