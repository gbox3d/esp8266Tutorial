## esp8266 arduino

공식문서  
https://arduino-esp8266.readthedocs.io/en/latest/index.html


### vscode c/cpp 환경설정 

c_cpp_properties.json파일 예제  


```json
{
    "configurations": [
        {
            "name": "Mac",
            "includePath": [
                "/Users/gbox3d/Library/Arduino15/packages/esp8266/tools/**",
                "/Users/gbox3d/Library/Arduino15/packages/esp8266/hardware/esp8266/2.7.1/**",
                "/Users/gbox3d/Documents/Arduino/libraries/**",
                "/Users/gbox3d/Library/Arduino15/packages/**",
                "${workspaceFolder}/**"
            ],
            "defines": [
                "UBRRH",ㄴ
                "LED_BUILTIN"
            ],
            "macFrameworkPath": [
                "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks"
            ],
            "compilerPath": "/usr/bin/clang",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "clang-x64",
            "forcedInclude": []
        }
    ],
    "version": 4
}
```



### gpio

16 핀은 pulldown 가능하다, 나머지 핀들은 pullup 만 가능함.  

```text
wemos 보드용핀  

d0 : 16  , INPUT_PULLDOWN_16, INPUT,OUTPUT
d1 : 5  , INPUT_PULLUP, INPUT,OUTPUT
d2 : 4, INPUT_PULLUP, INPUT,OUTPUT
d3 : 0, INPUT_PULLUP, INPUT,OUTPUT
d4 : 2, INPUT_PULLUP, INPUT,OUTPUT
d5 : 14, INPUT_PULLUP, INPUT,OUTPUT
d6 : 12, INPUT_PULLUP, INPUT,OUTPUT
d7 : 13, INPUT_PULLUP, INPUT,OUTPUT
d8 : 15, INPUT_PULLUP, INPUT,OUTPUT
d9 : 3, INPUT_PULLUP, INPUT,OUTPUT
d10 : 1, INPUT_PULLUP, INPUT,OUTPUT
d11 : 9, INPUT_PULLUP, INPUT,OUTPUT
d12 : 10, INPUT_PULLUP, INPUT,OUTPUT
d13 : x
d14 : x
d15 : x

```

### interrupt

인터럽트 함수앞에 반드시 ICACHE_RAM_ATTR  붙여주어야 한다. esp8266만의 특징이므로 주의 해야한다.  
그렇지 않을 경우 무한리셋에 빠진다.

```c++

volatile boolean enableTriger = true;
ICACHE_RAM_ATTR void detect_sensor()
{
    if (enableTriger)
    {
        enableTriger = false;
        Serial.print("detect : ");
        Serial.println(millis());
    }
}
```

https://randomnerdtutorials.com/interrupts-timers-esp8266-arduino-ide-nodemcu/


### file io
https://circuits4you.com/2018/01/31/example-of-esp8266-flash-file-system-spiffs/


### tm1637
https://github.com/avishorp/TM1637