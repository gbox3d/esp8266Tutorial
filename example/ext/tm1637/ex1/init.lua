tm1637 = require('tm1637')

clk = 6
dio = 5

tmr.create():alarm(5000,tmr.ALARM_SINGLE,function () 
    print('start..')
    tm1637.init(clk, dio)
    print('init ok')
    tm1637.set_brightness(7) 
    tm1637.write_string('1.2.3.4.')
end)


id  = 0
sda = 1
scl = 2

-- initialize i2c, set pin1 as sda, set pin2 as scl
i2c.setup(0, sda, scl, i2c.SLOW)

function sendData(addr,data)
    i2c.start(id)
    i2c.address(id, addr, i2c.TRANSMITTER)
    i2c.write(id, data)
    i2c.stop(id)
end

function readData(addr,bytenum)
    i2c.start(id)
    i2c.address(id, addr, i2c.RECEIVER)
    c = i2c.read(id, bytenum)
    i2c.stop(id)

    --http://lua-users.org/wiki/StringLibraryTutorial
    -- c:gsub(".", function(code) -- 한바이트씩 처리하기
    --     print(code:byte() .. '/' .. code)
    -- end)

    return c
end

print("i2c sample")

--sendData(8,"{a:1}");

--sendData(8,{49})
-- tm1637.write_string('1.2.3.4.')
-- tm1637.set_brightness(7) 