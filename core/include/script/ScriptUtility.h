#pragma once
#include "core/Object.hpp"

#include <EASTL/string.h>
#include <EASTL/vector.h>
#include <EASTL/map.h>

namespace hc
{
	class Object;
	class FunctionRegister;
	typedef eastl::vector< FunctionRegister* > FunctionArray;//ͬ���Һ���������ͬ�ĺ�������
	typedef eastl::vector< FunctionArray > OverlappeArray;//ͬ�����������غ����б�
	typedef eastl::vector< eastl::pair< eastl::string, OverlappeArray > > ClassFuncitonArray;//�����б�
	typedef eastl::pair< eastl::string, Object* > CLassConstant;
	typedef eastl::vector< CLassConstant > ClassConstantArray;

	//���㺯��ID
	HADES_FORCEINLINE uint CaculateFunctionID()
	{
		return 0;
	}
	HADES_FORCEINLINE uint CaculateFunctionID( uint id1 )
	{
		return 1 + id1;
	}
	HADES_FORCEINLINE uint CaculateFunctionID( uint id1, uint id2 )
	{
		return 2 + id1 + id2;
	}
	HADES_FORCEINLINE uint CaculateFunctionID( uint id1, uint id2, uint id3 )
	{
		return 3 + id1 + id2 + id3;
	}
	HADES_FORCEINLINE uint CaculateFunctionID( uint id1, uint id2, uint id3, uint id4 )
	{
		return 4 + id1 + id2 + id3 + id4;
	}
	HADES_FORCEINLINE uint CaculateFunctionID( uint id1, uint id2, uint id3, uint id4, uint id5 )
	{
		return 5 + id1 + id2 + id3 + id4 + id5;
	}
	HADES_FORCEINLINE uint CaculateFunctionID( uint id1, uint id2, uint id3, uint id4, uint id5, uint id6 )
	{
		return 6 + id1 + id2 + id3 + id4 + id5 + id6;
	}
	HADES_FORCEINLINE uint CaculateFunctionID( uint id1, uint id2, uint id3, uint id4, uint id5, uint id6, uint id7 )
	{
		return 7 + id1 + id2 + id3 + id4 + id5 + id6 + id7;
	}
	HADES_FORCEINLINE uint CaculateFunctionID( uint id1, uint id2, uint id3, uint id4, uint id5, uint id6, uint id7, uint id8 )
	{
		return 8 + id1 + id2 + id3 + id4 + id5 + id6 + id7 + id8;
	}
	HADES_FORCEINLINE uint CaculateFunctionID( uint id1, uint id2, uint id3, uint id4, uint id5, uint id6, uint id7, uint id8, uint id9 )
	{
		return 9 + id1 + id2 + id3 + id4 + id5 + id6 + id7 + id8 + id9;
	}
	HADES_FORCEINLINE uint CaculateFunctionID( uint id1, uint id2, uint id3, uint id4, uint id5, uint id6, uint id7, uint id8, uint id9, uint id10 )
	{
		return 10 + id1 + id2 + id3 + id4 + id5 + id6 + id7 + id8 + id9 + id10;
	}
}