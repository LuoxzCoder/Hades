#pragma once
#include "Configure.h"



namespace hc
{
	//@��Ҫ����big,little ending������
	class Message;
	class Rawbuffer
	{
	private:
		uint		m_BufferSize;//��ǰ���ܴ�С
		uint		m_Length;//��Ч����
		uint		m_Position;//��ǰĩβλ��
		uint		m_Index;//��ǰ���λ��
		byte*		m_pBuffer;
	public:
		Rawbuffer();
		~Rawbuffer();
	private:
		bool _FindNextMessage();
		bool _DoUnpackMessage(Message* msg);
	public:
		bool UnpackMessage(Message* msg);//���û��message���򷵻ؿ�
		byte* NewBuffer(uint len);
		void Cleanup();
		void PrepareBuffer(uint len);
	};
}