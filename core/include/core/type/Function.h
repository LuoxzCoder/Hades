#pragma once
#include "Type.h"

namespace hc
{
	class HADES_CORE_API Function : public Object
	{//�����ͣ�Ϊ�ű����������ṩ֧��
		RTTI_ABSTRACT_TYPE_DECLEAR(Function)
	public:
		Function(void){};
		~Function(void){};
	public:
		virtual void CantCreate() const = 0;
	};
}