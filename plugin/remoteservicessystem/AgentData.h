#pragma once
#include "core/Object.hpp"
#include "Configure.h"


namespace hrss
{
	struct AgentData
	{
		char		ServiceFile[MAX_FILE_LENGTH];
		uint64		CurrentGID;//��ǰ��gid����
		uint64		OriginalGID;//ԭʼ���룬�����remoteservice�����������ǲ�һ���ģ���ͬ
		uint		CurrentHash;
		uint		OriginalHash;
	};
}