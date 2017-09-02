#include "WindowsFileSystem.h"
#include "UsualFile.h"
#include "log/ILogSystem.h"


#include <EASTL/string.h>
#include <Windows.h>
#include <stdlib.h>
#include <direct.h>
#include <stdio.h>
#include <io.h>


using namespace hc;
using namespace eastl;
namespace hfw
{
	//-------------------------------------------------------------------------------------------------------
	WindowsFileSystem::WindowsFileSystem(void)
	{
	}
	//-------------------------------------------------------------------------------------------------------
	WindowsFileSystem::~WindowsFileSystem(void)
	{
	}
	//-------------------------------------------------------------------------------------------------------
	eastl::string WindowsFileSystem::_GetRootPath()
	{
		char strFilePath[MAX_PATH + 1] = {0};
		GetModuleFileNameA(NULL, strFilePath, MAX_PATH);	// �õ�ProjectBooster_console.exe������·��		
		(strrchr(strFilePath, ('\\')))[1] = 0;				// �������һ����\���󣨺������ַ�����"\ProjectBooster_console.exe"��������ĸ'P'��Ϊ0����ʾ�ַ�������
		SetCurrentDirectoryA( strFilePath );				// ���õ�ǰ�Ĺ���Ŀ¼Ϊ���һ����\��ǰ���������ַ���
		return strFilePath;
	}
	//-------------------------------------------------------------------------------------------------------
	void WindowsFileSystem::_DoMakeFolder( const eastl::string& path )
	{
		if( access(path.c_str(),0) == -1 ) //����ļ��в�����
		{
			HADESLOG("make folder %s\n", path.c_str());
			mkdir(path.c_str());
		}
	}
	//-------------------------------------------------------------------------------------------------------
	bool WindowsFileSystem::_DoIsFileExist( const eastl::string& filename )
	{
		if( 0 == access(filename.c_str(), 0) )//���ֱ�Ӵ���
		{
			return true;
		}
		return false;
	}
	//-------------------------------------------------------------------------------------------------------
	bool WindowsFileSystem::_DoDeleteFile( const eastl::string& strFileName )
	{
		if( isFileExist(strFileName) )
		{
			remove( strFileName.c_str() );
		}
		return true;
	}
	////-------------------------------------------------------------------------------------------------------
	//eastl::vector<eastl::string> WindowsFileSystem::GetFileNamesWithExpand( const eastl::string& path, const eastl::string& exp )
	//{
	//	vector<string> files;
	//	string fullpath = path;
	//	struct _finddata_t c_file; 
	//	intptr_t   hFile; 
	//	if(_chdir(fullpath.c_str())) 
	//	{
	//		HADESLOG("Cant' open direction, %s\n", fullpath.c_str() );
	//		ASSERT(false);
	//	} 
	//	else 
	//	{
	//		hFile = _findfirst("*.*", &c_file); 
	//		if( 0 < c_file.size )
	//		{
	//			HADESLOG("include file, %s\n", c_file.name );
	//			string filename = c_file.name;
	//			if ( exp.empty() || string::npos != filename.find(exp) )
	//			{
	//				files.push_back( filename.substr(filename.find_last_of("/\\")+1) );
	//			}
	//		}
	//	}
	//	while(_findnext(hFile, &c_file) == 0) 
	//	{ 
	//		if( 0 < c_file.size )
	//		{
	//			HADESLOG("include file, %s\n", c_file.name );
	//			string filename = c_file.name;
	//			if ( exp.empty() || string::npos != filename.find(exp) )
	//			{
	//				files.push_back( filename.substr(filename.find_last_of("/\\")+1) );
	//			}
	//		}
	//	} 
	//	_findclose(hFile); 
	//	return files;
	//}
	//-------------------------------------------------------------------------------------------------------
	IFile* WindowsFileSystem::_DoFileFactory( const eastl::string& path )
	{
		return NEW UsualFile( path );
	}
	//-------------------------------------------------------------------------------------------------------
	void WindowsFileSystem::RecycleBin( IFile* file )
	{
		SAFE_DELETE( file );
	}

}