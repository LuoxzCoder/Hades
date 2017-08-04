#pragma once
#include "core/Object.hpp"



namespace hc
{
	class HADES_CORE_API ScriptValue// : public Object
	{
		//RTTI_TYPE_DECLEAR( ScriptValue )
	public:
		typedef void(*ClearFunction)(void* rec, Object* obj);
	private:
		Object*			m_pValue;
		void*			m_rpRecycle;
		ClearFunction	m_fClear;
	public:
		ScriptValue(void);
		~ScriptValue(void);
	public:
		static void SafeDeleteCleaner(void* rec, Object* obj);//��򵥵�delete�����
		static void NullCleaner(void* rec, Object* obj);//��������������
	public:
		HADES_FORCEINLINE void Clear()
		{
			if (NULL != m_fClear)
			{
				m_fClear(m_rpRecycle, m_pValue);
			}
		}
		HADES_FORCEINLINE void SetValue( Object* val, ClearFunction f )
		{
			m_pValue = val;
			m_fClear = f;
			m_rpRecycle = NULL;
		}
		HADES_FORCEINLINE void SetValue( const Object* val, ClearFunction f )
		{
			m_pValue = const_cast<Object*>(val);
			m_fClear = f;
			m_rpRecycle = NULL;
		}
		HADES_FORCEINLINE void SetValue(Object* val, void* rec, ClearFunction f)
		{
			m_pValue = val;
			m_rpRecycle = rec;
			m_fClear = f;
		}
		HADES_FORCEINLINE void SetValue(const Object* val, void* rec, ClearFunction f)
		{
			m_pValue = const_cast<Object*>(val);
			m_rpRecycle = rec;
			m_fClear = f;
		}
		HADES_FORCEINLINE Object* GetObject()
		{
			return m_pValue;
		}
		HADES_FORCEINLINE const Object* GetObject() const
		{
			return m_pValue;
		}
	};
}