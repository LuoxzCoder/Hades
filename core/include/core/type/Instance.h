#pragma once
#include "Type.h"

namespace hc
{
	class HADES_CORE_API Instance : public Object
	{//�����ͣ�Ϊ�ű����������ṩ֧��
		RTTI_ABSTRACT_TYPE_DECLEAR(Instance)
	public:
		Instance(void){};
		~Instance(void){};
	public:
		virtual void CantCreate() const = 0;
	};
}