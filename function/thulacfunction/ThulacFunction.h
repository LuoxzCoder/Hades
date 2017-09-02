#pragma once
#include "core/Singleton.hpp"
#include "core/IFunction.h"
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
		enum Constant
		{
			TC_PREPAER_SIZE = 4,
		};
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
		THULAC* _NewObject();
		THULAC* _GetObject();
		void _FreeObject(THULAC* obj);
	public:
		eastl::string Split(const std::string& input);
		//user_path           �����û��ʵ䣬�û��ʵ��еĴʻᱻ����uw��ǩ���ʵ���ÿһ����һ�У�UTF8����
		//t2s                 Ĭ��False, �Ƿ񽫾��Ӵӷ���ת��Ϊ����
		//just_seg            Ĭ��False, ʱ��ֻ���зִʣ������д��Ա�ע
		//ufilter             Ĭ��False, �Ƿ�ʹ�ù�����ȥ��һЩû������Ĵ�����硰���ԡ���
		//model_path          ����ģ���ļ������ļ��У�Ĭ��Ϊmodels/
		//separator           Ĭ��Ϊ��_��, ���ô������֮��ķָ��� 
		void InitializeThulac(const char* model_path, const char* user_path, int just_seg, int t2s, int ufilter, char separator);
	};
}