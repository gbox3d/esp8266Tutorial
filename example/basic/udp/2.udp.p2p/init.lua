dofile("_conwifi.lua")

--  p2p 방식 
test_str = "123456789abcd";
test_ip = "192.168.4.3"

--받기 설정
local udp_socket = net.createUDPSocket()
udp_socket:on("receive",function(sck,data,port,ip) 
    print('recv : ' .. data ) 
    print('port :' .. port)
    print('ip :' .. ip)
    --sck:send("ok")
end)

udp_socket:listen(1471) -- 첫번째 인자는 데이터를 받을 로컬포트 번호이다

function test()
    udp_socket:send(1471,test_ip,test_str)
end
