1��ȷ��lua���ѱ��룬����ʹ�õ��ǡ�\third\LuaJIT-2.1.0-beta2\src\��Ŀ¼�µ�lua51.lib��


2��ȷ��mysql���Ѱ�װ������mysql��lib��̫��δ�ϴ���svn����
�������ӣ�
http://dev.mysql.com/downloads/mysql/
ѡ��Windows (x86, 32-bit), ZIP Archive���������غ��ѹ��װ��
��װ������
http://jingyan.baidu.com/article/597035521d5de28fc00740e6.html
http://blog.csdn.net/i_am_wangbo/article/details/49999407


3����mysql���ݿ������Ϊ�����޸�luasqlĿ¼�µ�makefile�ļ��е��������ݣ�
�ļ�����Makefile.win.mysql
�޸����ݣ�
��1��lua�����·����
LUA_INC=F:\Hades\third\LuaJIT-2.1.0-beta2\src
LUA_LIBDIR=F:\Hades\third\LuaJIT-2.1.0-beta2\src
LUA_LIB=F:\Hades\third\LuaJIT-2.1.0-beta2\src\lua51.lib

��2��mysql�����·����
DRIVER_INCLUDE= /I"F:\Hades\third\mysql_server\mysql-5.7.14-win32\include"
DRIVER_LIBS= "F:\Hades\third\mysql_server\mysql-5.7.14-win32\lib\libmySQL.lib" "F:\Hades\third\mysql_server\mysql-5.7.14-win32\lib\mysqlclient.lib" 

��3��Hades���ߵ��������ļ������Ŀ¼��
OUTPUT_DIR="F:\Hades\build\function"


4��luasql�ı��뷽����
ȷ��lua��mysql��ʹ��32λ�⣬windowsƽ̨�´�VS�Դ���32λ�����д��ڣ�����luasql����Ŀ¼������������
F:\Hades\function\luasql-2.3.2>nmake /f Makefile.win.mysql
�������ɹ�������srcĿ¼������ mysql.dll �ļ���
��Makefile.win.mysql �ļ�������Ϊ������󿽱�һ�� mysql.dll �� OUTPUT_DIR Ŀ¼�¡�


5����luasql����mysql���ݿ⣺
��1��ȷ������mysql���ݿ���������

��2�����Խű���
myTest.lua�������ݿ����б����ȡֵ��
myTest2.lua�������ݿ��н���һ���±�