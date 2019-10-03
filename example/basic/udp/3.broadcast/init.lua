
function OnSTAGetIp()
    print("STATION_GOT_IP:" .. wifi.sta.getip())

    --todo
    --createUDPSocket 으로 예제 수정요함
    udp_socket=net.createConnection(net.UDP)
    udp_socket:connect(5683,"192.168.4.255")

    tmr.alarm(0,2000,1,function()
        udp_socket:send("hello")
        print('send ok..and ' .. node.heap() )
    end)

end
