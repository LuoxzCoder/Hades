#pragma once
#include "core/Predefine.h"


//63Ϊ����λ�ã���ʹ��
//0-47Ϊrecycleablevectorʹ�õı��λ��
//��ʹ�õ�λ��Ϊ48-62
#define SD_CLIENT_FLAG		(((uint64)1)<<62)//���ӽ���Ŀͻ���
#define SD_SERVICE_FLAG		(((uint64)1)<<61)//���ӽ����Զ�̷���


#define GET_GID(a)			(0x0000FFFFFFFFFFFF&a)
#define SET_GID(a, b)		((0xFFFF000000000000&a)|b)
#define GET_FLAG(a)			(0xFFFF000000000000&a)
#define SET_FLAG(a, b)		((0x0000FFFFFFFFFFFF&a)|b)
#define IS_FLAG(a, b)		((a&b) != 0)

#define MC_USER_DEFINED_ID_MAX	50000