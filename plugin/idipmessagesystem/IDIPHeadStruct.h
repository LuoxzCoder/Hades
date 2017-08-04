#pragma once
#include "core/Predefine.h"
#include "tlbbsy_idip.h"
#ifdef WIN32
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif

#pragma pack(1)
namespace hms
{
	struct IDIPHeadStruct
	{
	private:
		uint32_t  dwPacketLen;                          /* ���� */
		uint32_t  dwCmdid;                              /* ����ID */
		uint32_t  dwSeqid;                              /* ��ˮ�� */
		char      szServiceName[SERVICE_NAME_LENGTH];   /* ������ */
		uint32_t  dwSendTime;                           /* ����ʱ��YYYYMMDD��Ӧ������ */
		uint32_t  dwVersion;                            /* �汾�� */
		char      szAuthenticate[AUTHENTICATE_LENGTH];  /* ���ܴ� */
		int32_t   iResult;                              /* ������,���������ͣ�0������ɹ�����Ҫ�⿪��������ϸ��Ϣ,1������ɹ��������巵��Ϊ�գ�����Ҫ������壨eg����ѯ�û���ɫ���û���ɫ�����ڵȣ���-1: ����ͨ���쳣,-2����ʱ,-3�����ݿ�����쳣,-4��API�����쳣,-5��������æ,-6����������,С��-100 ���û��Զ��������Ҫ��дszRetErrMsg */
		char      szRetErrMsg[ERROR_MSG_LENGTH];        /* ������Ϣ */
	public:
		HADES_FORCEINLINE static uint GetHeadSize()
		{
			return sizeof(IDIPHeadStruct);
		}
	public:
		//---------------------------------------------------------------------------------------------------------
		HADES_FORCEINLINE bool isValid() const
		{
			return true;
		}
		//---------------------------------------------------------------------------------------------------------
		HADES_FORCEINLINE void SetID(uint id)
		{
			dwCmdid = htonl(id);
		}
		//---------------------------------------------------------------------------------------------------------
		HADES_FORCEINLINE void SetRawLength(uint len)
		{
			dwPacketLen = htonl(len);
		}
		//---------------------------------------------------------------------------------------------------------
		HADES_FORCEINLINE uint GetID() const
		{
			return ntohl(dwCmdid);
		}
		//---------------------------------------------------------------------------------------------------------
		HADES_FORCEINLINE uint GetMessageLength() const
		{
			return ntohl(dwPacketLen) - sizeof(IDIPHeadStruct);
		}
		//---------------------------------------------------------------------------------------------------------
		HADES_FORCEINLINE uint GetRawLength() const
		{
			return ntohl(dwPacketLen);
		}
		//---------------------------------------------------------------------------------------------------------
		HADES_FORCEINLINE uint GetResult() const
		{
			return ntohl(iResult);
		}
	};
}
#pragma pack()