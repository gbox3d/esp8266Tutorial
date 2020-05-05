--
-- Created by IntelliJ IDEA.
-- User: gbox3d
-- Date: 2019-03-23
-- Time: 22:15
-- To change this template use File | Settings | File Templates.
--

--풀다운 입력예제
--150ms 이상 지속되는 펄스만 받기

print("pluse detector example use triger v1.0")

minimumPulse = 50

local pinSensor = 5 --sck, gpio14
gpio.mode(pinSensor, gpio.INPUT)

pluseEdge = 0
--업펄스 감지
function callBackUpPluse(level, when, eventcount)

    gpio.trig(pinSensor, "none")
    pluseEdge = when --시작점 저장

    tmr.create():alarm(minimumPulse,tmr.ALARM_SINGLE,function()
        if gpio.read(5) == gpio.HIGH then
            print("ready",gpio.read(5))
            gpio.trig(pinSensor, "both", callBackDownPluse) --다운 펄스 기다리기
        else
            print("cancel",gpio.read(5)) --이하면 취소
            gpio.trig(pinSensor, "up",callBackUpPluse)
        end
    end)

end

--다운펄스감지
function callBackDownPluse (level, when, eventcount)
    gpio.trig(pinSensor, "none")
    print(level .. "," .. when .. "," .. eventcount)
    print( when - pluseEdge ) -- 펄스 길이

    tmr.create():alarm(minimumPulse,tmr.ALARM_SINGLE,function()  gpio.trig(pinSensor, "up", callBackUpPluse) end)
end


gpio.trig(pinSensor, "up", callBackUpPluse)

