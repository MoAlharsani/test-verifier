/***************************************************
  This is an example sketch for our optical Fingerprint sensor

  Designed specifically to work with the Adafruit BMP085 Breakout
  ----> http://www.adafruit.com/products/751

  These displays use TTL Serial to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/


#include <Adafruit_Fingerprint.h>


#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// Set up the serial port to use softwareserial..
SoftwareSerial mySerial(2, 3);

#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// #0 is green wire, #1 is white
#define mySerial Serial1

#endif


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
bool fingerprintDetected = false;  // Variable to keep track of fingerprint detection

void setup()
{
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
  
  } else {
    while (1) { delay(1); }
  }

 
  finger.getParameters();

  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    
  }
  else {
    
  }
}

void loop()                     // run over and over again
{
  if (!fingerprintDetected) {
    fingerprintDetected = getFingerprintID();
  }
  delay(50);            //don't need to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      // Image taken
      break;
    case FINGERPRINT_NOFINGER:
      // No finger detected
      return 0;
    case FINGERPRINT_PACKETRECIEVEERR:
      // Communication error
      return 0;
    case FINGERPRINT_IMAGEFAIL:
      // Imaging error
      return 0;
    default:
      // Unknown error
      return 0;
  }

  // Image taken successfully, continue processing

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      // Image converted
      break;
    case FINGERPRINT_IMAGEMESS:
      // Image too messy
      return 0;
    case FINGERPRINT_PACKETRECIEVEERR:
      // Communication error
      return 0;
    case FINGERPRINT_FEATUREFAIL:
      // Could not find fingerprint features
      return 0;
    case FINGERPRINT_INVALIDIMAGE:
      // Could not find fingerprint features
      return 0;
    default:
      // Unknown error
      return 0;
  }

  // Image converted successfully, continue processing

  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    // Fingerprint match found
    Serial.println(finger.fingerID);  // Print the ID
    return finger.fingerID;
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    // Communication error
    return 0;
  } else if (p == FINGERPRINT_NOTFOUND) {
    // No match found
    return 0;
  } else {
    // Unknown error
    return 0;
  }
}
