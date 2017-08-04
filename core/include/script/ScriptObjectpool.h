#pragma once
#include "core/Singleton.hpp"

#include "concurrentqueue.h"



namespace hc
{
	class HADES_CORE_API ScriptObjectpool
	{
		SINGLETON_DECLARE(ScriptObjectpool);
	public:
		enum PoolIndex
		{
			POOL_INDEX_EMPTY = -1,
			POOL_INDEX_SHORT = 0,
			POOL_INDEX_USHORT = 1,
			POOL_INDEX_INT = 2,
			POOL_INDEX_UINT = 3,
			POOL_INDEX_FLOAT = 4,
			POOL_INDEX_DOUBLE = 5,
			POOL_INDEX_BOOL = 6,
			POOL_INDEX_STRING_PUSH = 7,//��������Դ����Գƣ�ԭ����ӦΪpush��Ҫһ��stringȥ���غ�������ֵ���ܷ��ص�һ���ֲ�����
			POOL_INDEX_STRING_READ = 8,//����ȡ�϶��Ƕ�ȡһ��ָ���һ�����ȣ�����Ҫ����string��������һ�Σ����Ч��
			POOL_INDEX_BUFFER = 9,
			POOL_INDEX_INT64 = 10,
			POOL_INDEX_UINT64 = 11,
			POOL_INDEX_FLOATARRAY = 12,
			POOL_INDEX_INSTANCE = 13,
			POOL_INDEX_FUNCTION = 14,
			POOL_INDEX_ARGUMENTS = 15,
			POOL_INDEX_COUNT,
			POOL_PREPARE_COUNT = 32,
		};
	private:
		typedef void* (*ObjectAllocer)();
		typedef void(*ObjectFreer)(void*);
	private:
		typedef moodycamel::ConcurrentQueue< void* > ObjectQueue;
	private:
		struct ResultPoolDataStruct
		{
			ObjectQueue			m_ObjectQueue;
			ObjectAllocer		m_ObjectAllocer;
			ObjectFreer			m_ObjectFreer;
		};
	private:
		ResultPoolDataStruct*		m_pResultPoolDataStructArray;
	public:
		ScriptObjectpool();
		~ScriptObjectpool();
	public:
		void* GetObject(uint index);
		void FreeObject(uint index, void* obj);
	};
}
