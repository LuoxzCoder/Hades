#include "thread/IThreadSystem.h"
#include "HolderThread.h"
#include "log/ILogSystem.h"


using namespace hc;
namespace hlks
{
	SINGLETON_IMPLEMENT(HolderThread);
	//---------------------------------------------------------------------------------------------------------
	HolderThread::HolderThread()
	{
		m_pIJobDispatcher =
			static_cast<IJobDispatcher*>(
			IThreadSystem::Instance()->ThreadEntityFactory(ThreadProperty::ET_JOB_DISPATCHER));
		m_pIJobDispatcher->SetSortType(ThreadProperty::ST_UNSORT);
		m_pIJobDispatcher->SetName("Accessor");
		//Ŀǰֻ����1���̣߳��������������ʱ�򣬻ᵼ��memcpy�Ĳ���ȫ����
		//��Ҫ������UnrigorousAccessor����ģ��鿴�ú�����
		//���о�����Ҫ�޸�AccessPackage
		m_pIJobDispatcher->SetThreadCount(1);
		m_pIJobDispatcher->Start();

		m_pCopyJobCallback = MEMBER_FUNC_PTR(&HolderThread::OnFreeCopyJob);
		m_pSaveJobCallback = MEMBER_FUNC_PTR(&HolderThread::OnFreeSaveJob);
	}
	//---------------------------------------------------------------------------------------------------------
	HolderThread::~HolderThread()
	{
		m_pIJobDispatcher->Stop();
		IThreadSystem::Instance()->RecycleBin(m_pIJobDispatcher);
		SAFE_DELETE(m_pCopyJobCallback);
		SAFE_DELETE(m_pSaveJobCallback);
	}
	//---------------------------------------------------------------------------------------------------------
	void HolderThread::OnFreeCopyJob(hc::SmartPtr<IJob>& job)
	{
		m_CopyJobQueue.enqueue(job);
	}
	//---------------------------------------------------------------------------------------------------------
	void HolderThread::OnFreeSaveJob(hc::SmartPtr<IJob>& job)
	{
		m_SaveJobQueue.enqueue(job);
	}


}