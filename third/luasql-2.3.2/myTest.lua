--������������
luasql = require "luasql.mysql"
local env = luasql.mysql()
assert(env)
print(env)

--�������ݿ⣨���������ݿ��� �û��� ���룩
local conn = env:connect('test','root','')
assert(conn)
print(conn)

--�������ݿ�
conn:execute"SET NAMES GB2312"

--�������ݿ��ķ�
function rows (connection, sql_statement)
  local cursor = assert (connection:execute (sql_statement))
  return function ()
    return cursor:fetch()
  end
end

for id, name, degree in rows(conn ,"SELECT * from MyClass") do
    print(string.format("%d  %s  %f", id, name, degree))
end

conn:close()  --�ر����ݿ�����
env:close()   --�ر����ݿ⻷��