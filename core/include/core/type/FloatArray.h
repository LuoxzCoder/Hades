#pragma once
#include "Type.h"

namespace hc
{
	class HADES_CORE_API FloatArray : public Object
	{//�����ͣ�Ϊ�ű����������ṩ֧��
		RTTI_ABSTRACT_TYPE_DECLEAR(FloatArray)
	public:
		FloatArray(void){};
		~FloatArray(void){};
	public:
		virtual void CantCreate() const = 0;
	};
}