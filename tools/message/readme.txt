int len = evbuffer_get_length(m_rpInputBuffer);\\��ȡ������buffer����
byte* buffer = m_pRawbuffer->NewBuffer(len);\\׼���ó���buffer
bufferevent_read(m_pBufferevent, buffer, len);\\����buffer
Message msg;
while (m_pRawbuffer->UnpackMessage(msg))\\�����Ϣ
{
	m_rpHost->OnReceive(m_ID, msg)\\������Ϣ
}
m_pRawbuffer->Cleanup();\\��β