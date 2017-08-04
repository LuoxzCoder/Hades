#pragma once
#include "core/Configure.h"
#include "core/Object.hpp"



namespace hc
{
	//@��Ҫ����big,little ending������
	class IMessage;
	class HADES_CORE_API IRawbuffer : public Object
	{
		RTTI_ABSTRACT_TYPE_DECLEAR(IRawbuffer);
	private:
		enum Constant
		{
			RBC_MAX_ERROR_COUNT = 1,
		};
	private:
		const uint	m_HeadSize;
		uint		m_ErrorCount;
		uint		m_BufferSize;//��ǰ���ܴ�С
		uint		m_Length;//��Ч����
		uint		m_Position;//��ǰĩβλ��
		uint		m_Index;//��ǰ���λ��
		byte*		m_pBuffer;
	public:
		IRawbuffer(uint headsize);
		virtual ~IRawbuffer();
	private:
		virtual bool _haveValidMessage(byte* buffer, uint& length, uint& index) = 0;
		virtual uint _GetRawbufferLength(byte* buffer) = 0;
	protected:
		bool _PrepareBuffer(uint len);
	public:
		bool UnpackMessage(IMessage*& msg);//���û��message���򷵻ؿ�
		byte* NewBuffer(uint len);
		bool Windup();//����������̫��ͷ���false
		void Reset();
	protected:
		HADES_FORCEINLINE void _ErrorOccurred();//��buffer��������ʱ����ã���Ҫ��ֹ����
	};


	//---------------------------------------------------------------------------------------------------------
	HADES_FORCEINLINE void IRawbuffer::_ErrorOccurred()
	{
		++m_ErrorCount;
		m_Index = 0;
		m_Length = 0;
		m_Position = 0;
	}
}