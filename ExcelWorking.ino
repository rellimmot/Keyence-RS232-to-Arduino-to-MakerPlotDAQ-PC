#include <SoftwareSerial.h>
SoftwareSerial Keyence(6, 7); // (RX, TX) from Keyence RS232

// how much serial data input expected before a newline
const unsigned int MAX_INPUT = 16; //16 bits for an 'MS' data request

const byte LED = 13; // Debugging LED for flash()

void setup()
{
	Keyence.begin(9600);
	Serial.begin(9600);

	// for the Excel graph to work, let's set it up:
	Serial.println("CLEARDATA"); // Clears old data from Excel sheet
	Serial.println("LABEL,Time,Timer,Reading Type,Sensor Lo/Go/Hi,Displacement"); //Sets up labels for readings LABEL is req'd
	Serial.println("RESETTIMER"); //resets timer to 0
// write first data request to get things going
	delay(500);
	KeyenceRequest();
	delay(500);
} // end of setup

  /* here to process incoming serial data after a terminator received */
void process_data(const char * data)
{   // Use this area to tell the Arduino what to do with the data:
	Serial.print("DATA,TIME,TIMER,");
	Serial.print(data);
	Serial.println();
	delay(80);
	flash();
}  // end of process_data

void processIncomingByte(const byte inByte)
{
	static char input_line[MAX_INPUT];
	static unsigned int input_pos = 0;

	switch (inByte)
	{
	case '\n':   // end of text
		input_line[input_pos] = 0;  // terminating null byte

									// terminator reached! process input_line here ...
		process_data(input_line);
		// reset buffer for next time
		input_pos = 0;
		// now that collection is complete, request new data
		KeyenceRequest();

		break;
	case '\r':   // discard carriage return
		break;
	default:
		// keep adding if not full ... allow for terminating null byte
		if (input_pos < (MAX_INPUT - 1))
			input_line[input_pos++] = inByte;
		break;
	}  // end of switch
} // end of processIncomingByte  

void loop()
{
	// if serial data available, process it
	while (Keyence.available() > 0)
			processIncomingByte(Keyence.read());

	// do other stuff here like testing digital input (button presses) ...
}  // end of loop

void KeyenceRequest() {
	// write new data request
	Keyence.write("M");
	Keyence.write("S");
	Keyence.write('\r');
}

void flash()
{
	digitalWrite(LED, HIGH);
	delay(1);
	digitalWrite(LED, LOW);
}  // end of flash