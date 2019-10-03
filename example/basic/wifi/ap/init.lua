wifi.setmode(wifi.SOFTAP)
--패스워드를 8자이상입력하지않으면 ssid 가 ESP8266_XXX이런식으로 설정됨
--wifi.ap.config({ssid="esptest",pwd="123456789"})

-- nil 을 주면 패스워드 설정안해도됨
wifi.ap.config({ssid="esp"..node.chipid(),pwd="123456789a"})
wifi.ap.setip({ip="192.168.4.1",netmask="255.255.255.0",gateway="192.168.4.1"})

print(wifi.ap.getip())

local udp_socket = net.createUDPSocket()
udp_socket:on("receive",function(sck,data,port,ip) 
    print('recv : ' .. data ) 
    print('port :' .. port)
    print('ip :' .. ip)
    --sck:send("ok")
end)

udp_socket:listen(2019) -- 첫번째 인자는 데이터를 받을 로컬포트 번호이다
