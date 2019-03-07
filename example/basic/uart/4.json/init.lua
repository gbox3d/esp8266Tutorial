--이 예제는 데이터 단위가 \r\n으로 끝난다고 가정한다.

theApp = {verion = "0.1.0"}

function _doJson(buf)
    print(buf .. "\r\n")
end

function startApp()
    print("uart mode start!")
    uart.setup(0, 115200, 8, 0, 1, 0)
    -- 아스키코드값을 직접넣어주려면 string.char를 사용한다.
    --  0x0d, 즉 \r 를 만나면 데이터를 끈어 넘겨준다.(마샬링) 넘겨주는 데이터는 마샬링 바이트까지 포함된다.
    uart.on(
        "data",
        string.char(0x0a), --parse by \n 에서 끊기
        (function()
            local _fsm = 0
            local _buf = ""
            local _open = 0
            return function(data)
                print("--------start--------")
                print("length : " .. data:len())
                _open =0
                _fsm =0
                data:gsub(
                    ".",
                    function(code) -- 한바이트씩 처리하기
                        if _fsm == 0 then
                            if code == "{" then
                                _buf = _buf .. code
                                _open = _open + 1
                                _fsm = 10
                            end
                        elseif _fsm == 10 then
                            _buf = _buf .. code
                            if code == "}" then
                                _open = _open - 1
                                if _open == 0 then
                                    _fsm = 0
                                    _doJson(_buf)
                                    _buf = ""
                                end
                            elseif code=="{" then _open = _open + 1
                            end
                        end
                        print(code:byte() .. "/" .. code)
                    end
                )
                print("--------end--------")
            end
        end)(),
        0 -- not run_lua
    )
end
