-- ʾ���ű����ܣ�����һ����Ϊ��sample���ı�

luasql = require "luasql.mysql"

--������������
local env  = luasql.mysql()
assert(env)
print(env)

--�������ݿ⣨���������ݿ��� �û��� ���룩
local conn = env:connect('test','root','')
assert(conn)
print(conn)

--�������ݿ�
status,errorString = conn:execute([[CREATE TABLE sample (id INTEGER, name TEXT)]])
print(status,errorString )

status,errorString = conn:execute([[INSERT INTO sample values('12','Raj')]])
print(status,errorString )

cursor,errorString = conn:execute([[select * from sample]])
print(cursor,errorString)

row = cursor:fetch ({}, "a")
while row do
  print(string.format("Id: %s, Name: %s", row.id, row.name))
  row = cursor:fetch (row, "a")
end

-- close everything
cursor:close()
conn:close()
env:close()