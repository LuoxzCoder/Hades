#include "memory/Allocator.h"
#include "stdlib.h"


namespace hc
{
	//c++ ��̬������ʼ��û���Ⱥ�˳�����ԣ��벻Ҫʹ����Ҫȫ�־�̬���Һ���NEW�ı���
	Allocator::alloc_memory Allocator::s_pAlloc = &malloc;
	Allocator::realloc_memory Allocator::s_pRealloc = &realloc;
	Allocator::release_memory Allocator::s_pRelease = &free;
	//---------------------------------------------------------------------------------------------------------
	void Allocator::Reset()
	{
		Allocator::s_pAlloc = &malloc;
		Allocator::s_pRealloc = &realloc;
		Allocator::s_pRelease = &free;
	}

}