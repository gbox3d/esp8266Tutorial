--http://lua-users.org/wiki/StringLibraryTutorial

--문자열에서 바이트 단위로 데이터 접근하기 
print( string.byte("ABCDE",1) )

c = "ABCDE"
print(c:byte(2))
