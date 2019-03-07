--
-- Created by IntelliJ IDEA.
-- User: gbox3d
-- Date: 2019-03-07
-- Time: 05:11
-- To change this template use File | Settings | File Templates.
--

--이 예제는 데이터 단위가 \r\n으로 끝난다고 가정한다.

theApp = {verion = '0.1.0'}

function startApp()
    print("uart mode start!")
    uart.setup(0,115200,8,0,1,0)
    -- 아스키코드값을 직접넣어주려면 string.char를 사용한다.
    --  0x0d, 즉 \r 를 만나면 데이터를 끈어 넘겨준다.(마샬링) 넘겨주는 데이터는 마샬링 바이트까지 포함된다.
    uart.on("data", string.char(0x0a), --parse by \n 에서 끊기
        function(data)
            print('--------start--------')
            data:gsub(".", function(code) -- 한바이트씩 처리하기
                print(code:byte() .. '/' .. code)
            end)
            print('--------end--------')
        end,
        0 -- not run_lua
    )
end
