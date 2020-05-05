## tm1637 예제

### wireing

gpio 1,2 을 사용한다. (예제 참고 )  
clk 는 SCL 포트 연결  
dio 는 SDA 포트 연결  

### 코드규칙 

하위 4비트 

```text
   -1- +
       2
       4    
   -8- +
```
상위 4비트

```text
  
  +-   - +  
  8  4   |
  2      |
  + - 1- +

```       

0~9 까지 숫자 표현예

```lua
local alphabet = {
  [0] = 0x3F, 
  [1] = 0x06, 
  [2] = 0x5B, 
  [3] = 0x4F, 
  [4] = 0x66, 
  [5] = 0x6D, 
  [6] = 0x7D, 
  [7] = 0x07, 
  [8] = 0x7F, 
  [9] = 0x6F  
}
```

   

원본에 없는 한칸씩 출력할수있는 write(코드,자리수) 함수를 추가 하였다.  


## 제어 모듈 
https://github.com/uaraven/tm1637-esp  

https://github.com/eaup/tm1637-led-driver  


