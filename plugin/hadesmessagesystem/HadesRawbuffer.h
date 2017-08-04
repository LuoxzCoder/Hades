#pragma once
#include "network/message/IRawbuffer.h"



namespace hms
{
	//@��Ҫ����big,little ending������
	class HadesRawbuffer : public hc::IRawbuffer
	{
	public:
		HadesRawbuffer();
		virtual ~HadesRawbuffer();
	private:
		virtual bool _haveValidMessage(byte* buffer, uint& length, uint& index);
		virtual uint _GetRawbufferLength(byte* buffer);
	private:
		bool _FindNextMessage(byte* buffer, uint& length, uint& index);
		bool _DoUnpackMessage();
	};
}