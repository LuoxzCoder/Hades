#pragma once
#include "Accessinfo.h"


#include <EASTL/map.h>
namespace hc
{
	class Accessor;	
	class HADES_CORE_API IAccessPackage : public Object
	{
		RTTI_ABSTRACT_TYPE_DECLEAR(IAccessPackage);
	private:
		enum Constant
		{
			APC_DEFUALT_ACESSINFO_SIZE = 10,
		};
	private:
		bool					m_haveRequest;
		AccessinfoArray			m_AccessOrder;
		AccessorRequestCallback	m_AccessorRequestCallback;
	public:
		IAccessPackage();
		virtual ~IAccessPackage();
	private:
		virtual void _DoRequest() = 0;//����ʵ������Ҫ�����ٴ����������
		virtual void _DoReleaseAccessores() = 0;//�ͷ�ȫ������
		virtual void _DoReleaseAccessor(uint64 gid) = 0;//�ͷŵ�������
	public:
		virtual uint64 CreateAccessor() = 0;//ֻ��������������Ҫ�ٵ�������
		virtual void DestoryAccessor(uint64 id) = 0;
	public:
		//����ȫ����callback�����������̰߳�ȫ�ģ�ӦΪkeeperϵͳ���ܻ��Ƕ��̷߳��ط��ʽ��

		//���ϸ�ģʽ��ȡ�ڴ����ݣ���ȡ�����ݵ�ʱ����������������ڶ��������޸ġ�
		//���û��������統�㲥���Ϊ֮���ʱ����Ҫȷ����������Ƿ��ڿɼ���Χ�ڣ�
		//��ͨ����������õ�һ��ǰһ����Ч�����λ�ã�Ȼ����㣬�㲥
		bool UnrigorousAccessor(uint64 id, int timestamp);

		//�ϸ�ģʽ��ȡ�������ж�д���ڼ���״̬ʱ����Ҫ��д���ͷź�ſ��Զ�ȡ
		//���ǵ������������ڼ���ʱ̬���������Լ�����ȡ�����������ַ�ʽ��ȡ��
		//���ݲ��ܱ����档
		bool ReadonlyAccessor(uint64 id, int timestamp);

		//�ϸ�ģʽ��д�������ж������߶�д������ʱ����Ҫ��д����������ͷŷź��
		//���Զ�ȡ�������ַ�ʽ��ȡ�Ķ�д����Ψһ�����޸����ݵģ����ͷŶ�д��֮��
		//�ؽ��޸����ݱ������ڴ��С�
		bool ReadwriteAccessor(uint64 id, int timestamp);

	public:
		void MayChangeAccesorMode(uint64 id, Accessor::AccessMode am);
		void BeginRequest();
		void ReleaseAccessores();//ȫ���ͷ�
		void ReleaseAccessor(uint64 gid);//�ͷſ���Ȩ�Լ�����
	private:
		HADES_FORCEINLINE bool _isRquested(uint64 id);
	protected:		
		HADES_FORCEINLINE AccessinfoArray& _GetAccessOrder();
		HADES_FORCEINLINE void _Unicast();
	public:
		//�ͷŷ����䣬�Զ��ж��Ƿ���Ҫ�����޸����ݡ�
		HADES_FORCEINLINE void SetAccessorCallback(AccessorRequestCallback::Callback func);
		HADES_FORCEINLINE bool HasRequest();
		HADES_FORCEINLINE bool isReleased();
		HADES_FORCEINLINE void UpdateTimestamp(uint64 id, int t);
	};




	//---------------------------------------------------------------------------------------------------------
	HADES_FORCEINLINE bool IAccessPackage::isReleased()
	{
		return m_AccessOrder.empty();
	}
	//---------------------------------------------------------------------------------------------------------
	HADES_FORCEINLINE void IAccessPackage::UpdateTimestamp(uint64 id, int t)
	{
		AccessinfoArray::iterator it = m_AccessOrder.find(id);
		if (m_AccessOrder.end() != it)
		{
			it->second.Timestamp = t;
		}
	}
	//---------------------------------------------------------------------------------------------------------
	HADES_FORCEINLINE bool IAccessPackage::_isRquested(uint64 id)
	{
		return m_AccessOrder.end() != m_AccessOrder.find(id);
	}
	//-------------------------------------------------------------------------------------------------------
	HADES_FORCEINLINE AccessinfoArray& IAccessPackage::_GetAccessOrder()
	{
		return m_AccessOrder;
	}
	//-------------------------------------------------------------------------------------------------------
	HADES_FORCEINLINE void IAccessPackage::_Unicast()
	{
		m_haveRequest = false;
		m_AccessorRequestCallback.Unicast(m_AccessOrder);
	}
	//-------------------------------------------------------------------------------------------------------
	HADES_FORCEINLINE void IAccessPackage::SetAccessorCallback(AccessorRequestCallback::Callback func)
	{
		m_AccessorRequestCallback.Add(func);
	}
	//-------------------------------------------------------------------------------------------------------
	HADES_FORCEINLINE bool IAccessPackage::HasRequest()
	{
		return m_haveRequest;
	}
}