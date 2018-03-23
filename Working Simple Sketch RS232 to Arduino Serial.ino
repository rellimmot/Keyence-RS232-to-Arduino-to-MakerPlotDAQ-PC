
#include <SoftwareSerial.h>
SoftwareSerial Keyence(6, 7); // RX, TX

void setup()
{
	Keyence.begin(9600);
	Serial.begin(9600);
}

void loop()
{
	if (Serial.available())
	{ // If data comes in from serial monitor, send it out to the Keyence
		Keyence.write(Serial.read());
	}
	if (Keyence.available())
	{ // If data comes in from the Keyence, send it out to serial monitor
		Serial.write(Keyence.read());
	}
}
