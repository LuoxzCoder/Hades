#include "thread/IThreadSystem.h"
#include "thread/IThreadMutex.h"
#include "LocalAccessPackage.h"
#include "LocalKeeperSystem.h"
#include "keeper/Accessor.h"


using namespace hc;
namespace hlks
{
	//---------------------------------------------------------------------------------------------------------
	LocalAccessPackage::LocalAccessPackage(LocalKeeperSystem* sys)
		:m_rpLocalKeeperSystem(sys)
	{
		m_AcessCallback = MEMBER_FUNC_PTR(&LocalAccessPackage::OnAccessorCallback);
		m_pIThreadMutex = static_cast<IThreadMutex*>(
			IThreadSystem::Instance()->
			ThreadEntityFactory(ThreadProperty::ET_MUTEX));
	}
	//---------------------------------------------------------------------------------------------------------
	LocalAccessPackage::~LocalAccessPackage()
	{
		SAFE_DELETE(m_AcessCallback);
		IThreadSystem::Instance()->RecycleBin(m_pIThreadMutex);
	}
	//---------------------------------------------------------------------------------------------------------
	uint64 LocalAccessPackage::CreateAccessor()
	{
		return m_rpLocalKeeperSystem->CreateAccessor();
	}
	//---------------------------------------------------------------------------------------------------------
	void LocalAccessPackage::DestoryAccessor(uint64 id)
	{
		ASSERT(nullid != id);
		m_rpLocalKeeperSystem->DestoryAccessor(id);
	}
	//---------------------------------------------------------------------------------------------------------
	void LocalAccessPackage::_DoRequest()
	{
		//�˴�������һ���ش�bug���ᵼ������
		//����ԭ���������һ���Խ�ȫ�������󶼷��ͳ�ȥ��
		//A���������1ֻ����2ֻ�����߶�д��B�����1��д����2��д
		//�ڵ�ǰkeeper�Ĵ���ԭ����ֻ�����Բ��У���д���ܲ���
		//��AB�����ִ��˳��ΪB����A�ڽ���֮ʱ�ᷢ��
		//�����ǰkeeper����һ����1��ֻ����������ôB�������޷���1��ȡ����Ȩ�ޣ����õ�2�ķ���Ȩ�ޣ��˳�
		//��ʱA������뵽��������У���ȡ��1��ֻ�������������޷����2�Ĳ���������������AB���������ľ���

		//����һ�������һ���Զ��ǷŴ������߳�����
		//Aִ�е���ȡ��1�ģ��ڻ�ȡ2֮ǰ���߳��л��ˣ�Bû��ȡ1�ĵ��ǵõ�2���ˣ�һ�����������
		_DoReleaseAccessores();//���ͷ�
		m_pIThreadMutex->Lock();
		AccessinfoArray& queue = _GetAccessOrder();
		m_SendIterator = queue.begin();
		_ExecuteRequest();
		m_pIThreadMutex->Unlock();
	}
	//---------------------------------------------------------------------------------------------------------
	void LocalAccessPackage::_ExecuteRequest()
	{
		AccessinfoArray& queue = _GetAccessOrder();
		ASSERT(queue.end() != m_SendIterator);
		Accessinfo& ai = m_SendIterator->second;
		++m_SendIterator;
		switch (ai.eAccessMode)
		{
		case Accessor::AM_UNRIGOROUS:
		{
										m_rpLocalKeeperSystem->UnrigorousAccessor(ai.GID, ai.Timestamp, m_AcessCallback);
										break;
		}
		case Accessor::AM_READ_ONLY:
		{
									   m_rpLocalKeeperSystem->ReadonlyAccessor(ai.GID, ai.Timestamp, m_AcessCallback);
									   break;
		}
		case Accessor::AM_READ_WRITE:
		{
										m_rpLocalKeeperSystem->ReadwriteAccessor(ai.GID, ai.Timestamp, m_AcessCallback);
										break;
		}
		default:ASSERT(false);
		}
	}
	//---------------------------------------------------------------------------------------------------------
	void LocalAccessPackage::OnAccessorCallback(hc::Accessor* acc)
	{
		//���̷߳��ز���ȫ
		m_pIThreadMutex->Lock();
		AccessinfoArray& queue = _GetAccessOrder();
		if (NULL != acc)
		{
			AccessinfoArray::iterator it = queue.find(acc->GetID());
			ASSERT(queue.end() != it);
			it->second.pAccessor = acc;
		}
		if (queue.end() == m_SendIterator)
		{
			_Unicast();
		}
		else
		{
			_ExecuteRequest();
		}
		m_pIThreadMutex->Unlock();
	}
	//---------------------------------------------------------------------------------------------------------
	void LocalAccessPackage::_DoReleaseAccessores()
	{
		AccessinfoArray& queue = _GetAccessOrder();
		FOR_EACH(AccessinfoArray, it, queue)
		{
			m_rpLocalKeeperSystem->ReleaseAccessor(it->second.pAccessor);
			it->second.pAccessor = NULL;
		}
	}
	//---------------------------------------------------------------------------------------------------------
	void LocalAccessPackage::_DoReleaseAccessor(uint64 gid)
	{
		ASSERT(nullid != gid);
		AccessinfoArray& queue = _GetAccessOrder();
		AccessinfoArray::iterator it = queue.find(gid);
		ASSERT(queue.end() != it);
		m_rpLocalKeeperSystem->ReleaseAccessor(it->second.pAccessor);
		it->second.pAccessor = NULL;
	}

}