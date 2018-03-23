
#include <SoftwareSerial.h>
SoftwareSerial Keyence(6, 7); // RX, TX
int byteReceived;
int byteSend;
const byte LED = 13;

void setup()
{
	pinMode(LED, OUTPUT);
	Keyence.begin(9600);
	Serial.begin(9600);
	
	Serial.println("CLEARDATA");
	Serial.println("LABEL,ReadingType,Sensor,Displacement");
	Serial.setTimeout(20);
}

void loop()
{
//	Serial.print("DATA,TIME,,");

	//	if (Serial.available())
	//	{ // If data comes in from serial monitor, send it out to the Keyence
	//		byteReceived = Serial.read();
	//		Keyence.write(byteReceived);
	//	}
	
	if (Keyence.available())
	{ // If data comes in from the Keyence, send it out to serial monitor
		Serial.write(Keyence.read());
		flash();
	}
	else {
		delay(20);
		Keyence.write("M");
		Keyence.write("S");
		Keyence.write('\r');
	}
}

void flash()
{
	digitalWrite(LED, HIGH);
	digitalWrite(LED, LOW);
}  // end of flash