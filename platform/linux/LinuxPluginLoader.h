#pragma once
#include "core/IPluginLoader.h"

#include <EASTL/map.h>
#include <EASTL/string.h>

namespace hcl
{
	class LinuxPluginLoader : public hc::IPluginLoader
	{
	private:
		struct PluginData
		{
			eastl::string	m_Name;
			void*			m_Handle;
			hc::IPlugin*	m_pPlugin;
		};
	private:
		typedef eastl::map< intptr_t, PluginData > PluginMap;
	private:
		PluginMap			m_LoadedPluginMap;
	public:
		LinuxPluginLoader(void);
		~LinuxPluginLoader(void);
	private:
		virtual hc::IPlugin* _DoLoadPlugin(const eastl::string& name);		// ���ز��
		virtual void _DoReleasePlugin(hc::IPlugin* plugin);				// �ͷŲ��
	public:
		virtual void AddLibraryPath(const eastl::string& path);
		virtual bool LoadDefualtPlugin(const eastl::string& path, eastl::list< hc::IPlugin* >& list);	//����Ĭ�ϲ��
	};
}