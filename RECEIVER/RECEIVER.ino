
#define MARK_EXCESS_MICROS    20 // recommended for the cheap VS1838 modules

#include <IRremote.h>

#if defined(ESP32)
int IR_RECEIVE_PIN = 7;
#else
int IR_RECEIVE_PIN = 7;
#endif

int relay = 9;

void shock() 
{
  Serial.print("send eletricity!");

  digitalWrite(relay, LOW);
  delay(2000);

  digitalWrite(relay, HIGH);

}
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

    Serial.begin(115200);   // Status message will be sent to PC at 9600 baud
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)  || defined(ARDUINO_attiny3217)
    delay(2000); // To be able to connect Serial monitor after reset or power up and before first printout
#endif
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver, enable feedback LED, take LED feedback pin from the internal boards definition

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN);
}

//+=============================================================================
// The repeating section of the code
//
void loop() {
    if (IrReceiver.decode()) {  // Grab an IR code
        // Check if the buffer overflowed
        if (IrReceiver.results.overflow) {
            Serial.println("IR code too long. Edit IRremoteInt.h and increase RAW_BUFFER_LENGTH");
        } else {
            Serial.println();
            IrReceiver.printIRResultShort(&Serial);
            if (IrReceiver.decodedIRData.command == 0x34) {
              shock();
            }
        }
        IrReceiver.resume();                            // Prepare for the next value
    }
}
