#pragma once
#include "core/Object.hpp"
#include "core/Types.h"


namespace hc
{
	//�����Begin next end������Ҫ�������ã�����Ȼ�������������
	class HADES_CORE_API IFunctionIterator : public Object
	{
		RTTI_ABSTRACT_TYPE_DECLEAR(IFunctionIterator);
	public:
		IFunctionIterator(void);
		virtual ~IFunctionIterator(void);
	public:
		virtual void Being() const = 0;
		virtual bool Next() const = 0;
		virtual DataType GetFieldType() const = 0;
		virtual const char* GetStringField(uint& len) const = 0;
		virtual int GetIntField() const = 0;
		virtual uint64 GetUInt64Field() const = 0;
		virtual bool HaveRenturnValue() const = 0;
		virtual void End() const = 0;
		virtual const IFunctionIterator* GetBaseFunctionIterator() const = 0;
		virtual bool isFunctionExist(const eastl::string& name) const = 0;
	};
}
