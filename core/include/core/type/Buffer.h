#pragma once
#include "Type.h"

namespace hc
{
	class HADES_CORE_API Buffer : public Object
	{//�����ͣ�Ϊ�ű����������ṩ֧��
		RTTI_ABSTRACT_TYPE_DECLEAR(Buffer)
	public:
		Buffer(void){};
		~Buffer(void){};
	public:
		virtual void CantCreate() const = 0;
	};
}