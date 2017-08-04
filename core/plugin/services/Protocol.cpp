#include "serialize/ISerializeSystem.h"
#include "network/message/IMessage.h"
#include "services/Protocol.h"
#include "core/Bufferpool.h"


namespace hc
{
	RTTI_TYPE_IMPLEMENT(Protocol);
	//---------------------------------------------------------------------------------------------------------
	Protocol::Protocol(void)
		:m_rpBuffer(NULL)
		, m_pMessage(NULL)
	{
		m_DataHead.RealSize = 0;
		m_DataHead.BufferSize = 0;
		m_DataHead.FunctionID = nullhandle;
		m_DataHead.CallerID = nullid;
		m_DataHead.CallerSessionID = nullid;
		m_DataHead.CallerHash = nullhandle;
	}
	//---------------------------------------------------------------------------------------------------------
	Protocol::~Protocol(void)
	{
		
	}
	//---------------------------------------------------------------------------------------------------------
	uint Protocol::Serialize(byte* buffer)
	{
		uint off = sizeof(m_DataHead);
		memcpy(buffer, &m_DataHead, off);
		memcpy(buffer + off, m_rpBuffer, m_DataHead.BufferSize);
		return off + m_DataHead.BufferSize;
	}
	//---------------------------------------------------------------------------------------------------------
	void Protocol::Parse(const byte* buffer, uint len)
	{
		uint off = sizeof(m_DataHead);
		memcpy(&m_DataHead, buffer, off);
		if (m_DataHead.BufferSize > 0)
		{
			SetBuffer(buffer + off, m_DataHead.BufferSize);
		}
	}
	//---------------------------------------------------------------------------------------------------------
	void Protocol::SetBuffer(const byte* buff, uint size)
	{
		ASSERT(NULL == m_rpBuffer);
		m_rpBuffer = Bufferpool::Instance()->Get(size, m_DataHead.RealSize);
		m_DataHead.BufferSize = size;
		memcpy(m_rpBuffer, buff, size);
	}
	//---------------------------------------------------------------------------------------------------------
	void Protocol::Reset()
	{
		ISerializeSystem::Instance()->FreeSerializable(m_pMessage);
		//�˴�������realsize�������buffersize����call���ʱ������ClearBuffer���buffersize����Ϊ0������bug
		Bufferpool::Instance()->Free(m_DataHead.RealSize, m_rpBuffer);
		m_DataHead.RealSize = 0;
		m_DataHead.BufferSize = 0;
		m_DataHead.FunctionID = nullhandle;
		m_DataHead.CallerID = nullid;
		m_DataHead.CallerSessionID = nullid;
		m_DataHead.CallerHash = nullhandle;
		m_rpBuffer = NULL;
		m_pMessage = NULL;
	}
}