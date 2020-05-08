#include <Arduino.h>
#include <Ticker.h>


class TaskExam {
    Ticker _ticker;
    int _nFsm;

    void setup() {
        pinMode( LED_BUILTIN,OUTPUT);
        digitalWrite(LED_BUILTIN,HIGH);
    }

    void loop() {

        if(_nFsm == 0) {
            _nFsm=1;
            digitalWrite(LED_BUILTIN,HIGH);
        }
        else {
            _nFsm = 0;
            digitalWrite(LED_BUILTIN,LOW);
        }

    }
     
    public :
    TaskExam() {
        setup();
        _ticker.attach_ms(300,std::bind(&TaskExam::loop,this ));
    }
    ~TaskExam() {}

};

TaskExam _taskExam;

void setup()
{

}
void loop()
{

}