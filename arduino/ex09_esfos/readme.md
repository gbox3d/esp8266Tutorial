### 파일 관리자 예제

#### 아두이노측 코드추가

```c

#include "esfos_drv.hpp"
...
...
void loop()
{
    ....
    esfos::run_driver();
    ....
}

```

#### 업로드 하기 

```sh
python3 esfos.py -p /dev/tty.usbserial-01BB76C3 -i ./data/config.json 
```

#### 다운로드하기 
