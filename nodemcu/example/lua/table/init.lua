--http://codeshared.com/archives/36

_tb = {9,4,31,2,27,5,6,33,7}

--단순 숫자 배열은 ipairs로 한다.
for k,v in ipairs(_tb) do 
    print(k,v)
end

table.insert( _tb,99 )
table.insert( _tb,1,-99 )

print(table.concat( _tb, ", ")) -- table output

print(table.remove( _tb))
print(table.concat( _tb, ", ")) -- table output

print(table.remove( _tb,1))
print(table.concat( _tb, ", ")) -- table output

print("_tb count : " , #_tb)

table.sort(_tb, function(a, b) return (a > b) and true or false end)
print(table.concat( _tb, ", ")) -- table output

_tb = {a=1,b=2,c=3}
for k,v in pairs(_tb) do 
    print(k,v)
end

print(_tb.a)


