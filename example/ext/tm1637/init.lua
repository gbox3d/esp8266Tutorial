tm1637 = require('tm1637')

clk = 1
dio = 2

tmr.create():alarm(5000,tmr.ALARM_SINGLE,function () 
    print('start..')
    tm1637.init(clk, dio)
    print('init ok')
    tm1637.set_brightness(7) 
    tm1637.write_string('1.2.3.4.')
end)



-- tm1637.write_string('1.2.3.4.')
-- tm1637.set_brightness(7) 