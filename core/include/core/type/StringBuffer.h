#pragma once
#include "Type.h"

namespace hc
{
	struct HADES_CORE_API StringBuffer	//�ű���native����const char*ʱ��ʹ�ã�����ָ���볤��
	{
	public:
		const void*		pBuffer;
		uint			Length;
	};
	
}