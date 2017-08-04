#pragma once
#include "Predefine.h"
#include "Rtti.hpp"

#include <EASTL/string.h>

namespace hc
{
	class HADES_CORE_API Object//�������ֹ�޸�
	{
		static Rtti	s_Rtti;
	public:
		Object(){}
		virtual ~Object(){}
	public:
		static const Rtti& RTTI(){ return Object::s_Rtti; }
		static uint SID(){ return Object::s_Rtti.GetTypeID(); }\
	public:
		virtual uint GetTypeID() const = 0;//�õ�����ϢID
		virtual bool isType( const Rtti& rtti ) const = 0;//�ж��Ƿ���ĳ����
		virtual const char* GetTypeName() const = 0;//��������
		virtual uint GetTypeSize() const = 0;//�������С
		virtual Object* Duplicate() const = 0;//����һ�ݸ���
		virtual bool isTypeOrDriverType( const Rtti& rtti ) const = 0;//�Ƿ�����ͬ�����ͻ��߼̳���
		virtual const Rtti& GetRtti() const = 0;
	public:
		intptr_t GetObjectID() const;
//#ifndef _TRACK_MEMORY
//	public:
//		void* operator new( uint size );
//		void operator delete( void* ptr );
//		void* operator new[]( uint size );
//		void operator delete[]( void* ptr );
//#endif
	};
}