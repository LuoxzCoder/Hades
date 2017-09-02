#pragma once
#include "core/Singleton.hpp"
#include "core/IFunction.h"
//#include "thulac.h"

#include "concurrentqueue.h"
#include <string>

class THULAC;

namespace htf
{
	class ThulacFunction : public hc::IFunction
	{
		SYSTEM_SINGLETON_DECLEAR(ThulacFunction);
		RTTI_DRIVER_TYPE_DECLEAR(ThulacFunction, hc::IFunction);
	private:
		typedef moodycamel::ConcurrentQueue< THULAC* > THULACQueue;
	private:
		std::string			m_ModelPath;
		std::string			m_UserPath;
		bool				m_isSegOnly;
		bool				m_isT2S;
		bool				m_isUfilter;
		THULACQueue*		m_pTHULACQueue;
		char				m_Separator;
	public:
		ThulacFunction();
		~ThulacFunction();
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Exit();
	private:
		THULAC* _GetObject();
		void _FreeObject(THULAC* obj);
	public:
		void std::string Split(const std::string& input);
	public:
		//user_path           �����û��ʵ䣬�û��ʵ��еĴʻᱻ����uw��ǩ���ʵ���ÿһ����һ�У�UTF8����
		//t2s                 Ĭ��False, �Ƿ񽫾��Ӵӷ���ת��Ϊ����
		//just_seg            Ĭ��False, ʱ��ֻ���зִʣ������д��Ա�ע
		//ufilter             Ĭ��False, �Ƿ�ʹ�ù�����ȥ��һЩû������Ĵ�����硰���ԡ���
		//model_path          ����ģ���ļ������ļ��У�Ĭ��Ϊmodels/
		//separator           Ĭ��Ϊ��_��, ���ô������֮��ķָ��� 
		HADES_FORCEINLINE void InitializeThulac(const char* model_path, const char* user_path, int just_seg, int t2s, int ufilter, char separator);
	};





	//---------------------------------------------------------------------------------------------------------
	HADES_FORCEINLINE void ThulacFunction::InitializeThulac(const char* model_path, const char* user_path, int just_seg, int t2s, int ufilter, char separator)
	{
		m_ModelPath = model_path;
		m_UserPath = user_path;
		m_isSegOnly = just_seg;
		m_isT2S = t2s;
		m_isUfilter = ufilter;
		m_Separator = separator;
	}
}