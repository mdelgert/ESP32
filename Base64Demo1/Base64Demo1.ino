#include <base64.h>

base64 b;

void setup()
{
    Serial.begin(115200);
    delay(1000); // Wait for Serial to initialize
}

void loop()
{
    Serial.println("12345678 = " + b.encode("12345678"));
    delay(1000);
    Serial.println("123456 = " + b.encode("123456"));
    delay(1000);
    Serial.println("1234567 = " + b.encode("1234567"));
    delay(1000); 
}
