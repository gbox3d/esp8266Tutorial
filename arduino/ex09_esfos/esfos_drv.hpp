#ifndef ESFOS_DRIVER_HPP
#define ESFOS_DRIVER_HPP

namespace esfos
{
    //Serial Parse
    inline void run_driver()
    {
        while (Serial.available() > 0)
        {
            String _strLine = Serial.readStringUntil('\n');
            // _strLine.remove(_strLine.length() - 1);
            //Serial.print(_strLine);
            if (_strLine == "<save>")
            {

                Serial.printf("save ready\n");
                delay(200);
                String _fileName = Serial.readStringUntil('\n');
                Serial.printf("file name %s \n", _fileName.c_str());

                // String _content = Serial.readStringUntil('\n');
                // Serial.printf("%s \n",_content.c_str());
                // Serial.printf("ok \n");

                File _f = SPIFFS.open(_fileName, "w");
                if (_f)
                {
                    delay(200);
                    //Serial.printf("file name %s \n", _fileName.c_str());
                    String _content = Serial.readStringUntil('\n');
                    int _size = _f.write(_content.c_str());
                    
                    Serial.printf("%s , %d byte saved\n", _content.c_str(), _size);

                    _f.close();
                }
                else
                {
                    Serial.printf("file error %s \n", _fileName.c_str());
                    Serial.printf("saved failed \n");
                }
            }
        }
    }

} // namespace esfos

#endif
