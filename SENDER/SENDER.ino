#include <Arduino.h>

#define IR_SEND_PIN         3

int buttonPin = A1;
uint16_t sAddress = 0x0102;
uint8_t sCommand = 0x34;
uint8_t sRepeats = 0;

int val = 0;
#include <IRremote.h>                            
IRsend irsend;

long frameCounter = 0;
                               
void setup()  
{  
    Serial.begin(115200);           //  setup serial
}  
                               
void loop()  
{  
  val = analogRead(buttonPin);  // read the input pin

  //0 to 1024
  if (val > 100) {

    frameCounter++;
    if (frameCounter > 100) {
      frameCounter = -700;
      val = 0;
      Serial.println("send!");
      IrSender.sendNEC(sAddress & 0xFF, sCommand, sRepeats);
    }
  } else {
    frameCounter = 0;
  }
  
                                  
  delay(1);  
}
