#pragma once
#include "core/IPluginLoader.h"

#include <EASTL/map.h>
#include <EASTL/string.h>
#include <Windows.h>

namespace hcw
{
	class WindowsPluginLoader : public hc::IPluginLoader
	{
	private:
		struct PluginData
		{
			eastl::string	m_Name;
			HMODULE			m_Handle;
			hc::IPlugin*	m_pPlugin;
		};
	private:
		typedef eastl::map< intptr_t, PluginData > PluginMap;
	private:
		PluginMap			m_LoadedPluginMap;
	public:
		WindowsPluginLoader(void);
		~WindowsPluginLoader(void);
	private:
		virtual hc::IPlugin* _DoLoadPlugin(const eastl::string& name);		// ���ز��
		virtual void _DoReleasePlugin(hc::IPlugin* plugin);				// �ͷŲ��
	public:
		virtual void AddLibraryPath(const eastl::string& path);
		virtual bool LoadDefualtPlugin(const eastl::string& path, eastl::list< hc::IPlugin* >& list);	//����Ĭ�ϲ��
	};
}