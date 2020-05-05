
-- 통신데이터는 \r\n으로 끝난다고 가정한다.

theApp={version='0.1.0'}
function startApp()
    print("uart mode start!")
    tmr.delay(1000000);
    uart.setup(0,115200,8,0,1,0)

    uart.on("data",
        string.char(0x0a), -- \n 에서 끊어내기
        function(data)
            if data=="+++quit\r" then
                print("uart mode quit ")
                uart.setup(0,115200,8,0,1,1)
                uart.on("data")
            else
                print("receive from uart:", data)
                node.input(data)
            end
        end,
        0 -- not run_lua
    )
end
