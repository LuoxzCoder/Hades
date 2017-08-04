#include "file/IFileSystem.h"
#include "log/ILogSystem.h"
#include "UsualFile.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>


using namespace eastl;

namespace hfl
{
	//--------------------------------------------------------------------------------------------------------------
	UsualFile::UsualFile(const eastl::string& url)
		:BaseFile(url),
		m_pFile(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	UsualFile::~UsualFile(void)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	bool UsualFile::_DoOpenFile(IFile::ActionType at)
	{
		switch (at)
		{
		case IFile::AT_WRITE:
		{
								string npath;
								if (string::npos != GetFilePath().find('.'))
								{
									npath = GetFilePath().substr(0, GetFilePath().find_last_of("/\\"));
								}
								else
								{
									npath = GetFilePath();
								}
								if (access(GetFilePath().c_str(), 0) == -1) //����ļ��в�����
								{
									//HADESLOG("make folder %s\n", npath.c_str());
									mkdir(npath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
								}
								m_pFile = fopen(GetFilePath().c_str(), "wb");
								//HADESLOG("Write %s\n", GetFilePath().c_str());
		}break;
		case IFile::AT_READ:
		{
							   m_pFile = fopen(GetFilePath().c_str(), "rb");
							   //HADESLOG("Read %s\n", GetFilePath().c_str());
		}break;
		default: ASSERT(false);
		}
		//m_pFile = fopen( GetFilePath().c_str(), "rb" );
		if (NULL == m_pFile)
		{
			HADESLOG("File %s Can not Open! \n", GetFilePath().c_str());
			//ASSERT(false);
		}
		else
		{
			uint nCurrentPos = ftell(m_pFile);//���ļ���С
			fseek(m_pFile, 0, SEEK_END);
			uint size = ftell(m_pFile) + nCurrentPos;
			fseek(m_pFile, nCurrentPos, SEEK_SET);
			_SetFileSize(size);
		}
		return m_pFile != NULL ? true : false;
	}
	//--------------------------------------------------------------------------------------------------------------
	bool UsualFile::_DoCloseFile()
	{
		return fclose(m_pFile) == -1 ? false : true;
	}
	//--------------------------------------------------------------------------------------------------------------
	int UsualFile::_DoReadFile(void* data, uint bitesize)
	{
		if (fread(data, bitesize, 1, m_pFile) == 1)
		{
			return bitesize;
		}
		return 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	int UsualFile::_DoSeekFile(int to, int whence)
	{
		return fseek(m_pFile, to, whence);
	}
	//--------------------------------------------------------------------------------------------------------------
	int UsualFile::_DoTell()
	{
		return ftell(m_pFile);
	}
	//--------------------------------------------------------------------------------------------------------------
	bool UsualFile::_DoFlush()
	{
		return 0 == fflush(m_pFile);
	}
	//--------------------------------------------------------------------------------------------------------------
	int UsualFile::_DoWriteFile(const void* data, uint bitesize)
	{
		if (fwrite(data, bitesize, 1, m_pFile) == 1)
		{
			return bitesize;
		}
		return 0;
	}

}