#include "BufferUtility.hpp"
#include "Rawbuffer.h"
#include "Message.h"
#include <conio.h>

using namespace hc;
void main(void)
{
	Rawbuffer rb;
	Message msg;
	Message unmsg;
	byte buffer[] = { 'a', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', 'd' };
	byte error[] = { '1', '3', '4', '4', '2', '5' };
	//memcpy(msg.Data(), buffer, sizeof(buffer));
	msg.CopyMessage(0, buffer, sizeof(buffer));

	{//message�ȺŲ���
		Message test;
		test = msg;
		BufferUtility::CompareBuffer(msg.GetRawBuffer(), msg.GetRawLength(), test.GetRawBuffer(), test.GetRawLength(), "message operator = test");
	}

	{
		byte* buff = rb.NewBuffer(msg.GetRawLength());
		memcpy(buff, msg.GetRawBuffer(), msg.GetRawLength());
		while (rb.UnpackMessage(&unmsg))
		{
			BufferUtility::CompareBuffer(msg.GetRawBuffer(), msg.GetRawLength(), unmsg.GetRawBuffer(), unmsg.GetRawLength(), "unpack message test");
		}
		rb.Cleanup();
	}

	{//����ճ��
		byte* buff = rb.NewBuffer(msg.GetRawLength());
		memcpy(buff, msg.GetRawBuffer(), msg.GetRawLength());
		buff = rb.NewBuffer(msg.GetRawLength());
		memcpy(buff, msg.GetRawBuffer(), msg.GetRawLength());
		while (rb.UnpackMessage(&unmsg))
		{
			BufferUtility::CompareBuffer(msg.GetRawBuffer(), msg.GetRawLength(), unmsg.GetRawBuffer(), unmsg.GetRawLength(), "stick message test");
		}
		rb.Cleanup();
	}

	{//���԰��
		byte* buff = rb.NewBuffer(msg.GetRawLength());
		memcpy(buff, msg.GetRawBuffer(), msg.GetRawLength());
		//����һ�����
		buff = rb.NewBuffer(msg.GetRawLength() - sizeof(buffer));
		memcpy(buff, msg.GetRawBuffer(), msg.GetRawLength() - sizeof(buffer));
		while (rb.UnpackMessage(&unmsg))
		{
			BufferUtility::CompareBuffer(msg.GetRawBuffer(), msg.GetRawLength(), unmsg.GetRawBuffer(), unmsg.GetRawLength(), "half message test");
		}
		rb.Cleanup();
		//��ȫ���
		buff = rb.NewBuffer(sizeof(buffer));
		memcpy(buff, &msg.GetRawBuffer()[msg.GetRawLength() - sizeof(buffer)], sizeof(buffer));
		while (rb.UnpackMessage(&unmsg))
		{
			BufferUtility::CompareBuffer(msg.GetRawBuffer(), msg.GetRawLength(), unmsg.GetRawBuffer(), unmsg.GetRawLength(), "half message + remain test");
		}
		rb.Cleanup();
	}

	{//���Դ��
		byte* buff = rb.NewBuffer(sizeof(error));
		memcpy(buff, error, sizeof(error));
		while (rb.UnpackMessage(&unmsg))
		{
			BufferUtility::CompareBuffer(msg.GetRawBuffer(), msg.GetRawLength(), unmsg.GetRawBuffer(), unmsg.GetRawLength(), "error package test");
		}
		rb.Cleanup();
		//���һ��ͷ
		buff = rb.NewBuffer(sizeof(error));
		memcpy(buff, error, sizeof(error));
		buff = rb.NewBuffer(HeadStruct::GetHeadSize());
		memcpy(buff, msg.GetRawBuffer(), HeadStruct::GetHeadSize());
		while (rb.UnpackMessage(&unmsg))
		{
			BufferUtility::CompareBuffer(msg.GetRawBuffer(), msg.GetRawLength(), unmsg.GetRawBuffer(), unmsg.GetRawLength(), "error package + head test");
		}
		rb.Cleanup();
		//��ͷ֮�����ӽ�ȥ
		buff = rb.NewBuffer(msg.GetRawLength() - HeadStruct::GetHeadSize());
		memcpy(buff, &msg.GetRawBuffer()[HeadStruct::GetHeadSize()], msg.GetRawLength() - HeadStruct::GetHeadSize());
		while (rb.UnpackMessage(&unmsg))
		{
			BufferUtility::CompareBuffer(msg.GetRawBuffer(), msg.GetRawLength(), unmsg.GetRawBuffer(), unmsg.GetRawLength(), "error package + head test + remain");
		}
		rb.Cleanup();
	}

	{
		byte* buff = rb.NewBuffer(msg.GetRawLength());
		memcpy(buff, msg.GetRawBuffer(), msg.GetRawLength());
		while (rb.UnpackMessage(&unmsg))
		{
			BufferUtility::CompareBuffer(msg.GetRawBuffer(), msg.GetRawLength(), unmsg.GetRawBuffer(), unmsg.GetRawLength(), "end message test");
		}
		rb.Cleanup();
	}
	getch();
}