/*
  Designed specifically to work with the Adafruit FONA
  ----> http://www.adafruit.com/products/1946
  ----> http://www.adafruit.com/products/1963
  ----> http://www.adafruit.com/products/2468
  ----> http://www.adafruit.com/products/2542

 */
#include "Adafruit_FONA.h"

#define FONA_RX 2
#define FONA_TX 10
#define FONA_RST 4
#define FONA_RI 7

// Use this for FONA 800 and 808s
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);
// Use this one for FONA 3G
//Adafruit_FONA_3G fona = Adafruit_FONA_3G(FONA_RST);

#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

void getLocation( char * longitude, char * latitude)
{
  uint16_t returncode;
  // this is a large buffer for replies
  char replybuffer[255];
  if (!fona.getGSMLoc(&returncode, replybuffer, 250))
    Serial.println(F("Failed!"));
  if (returncode == 0)
  {
    strcpy(longitude, strtok(replybuffer, ","));
    strcpy(latitude, strtok(NULL, ","));
  } else
  {
    Serial.print(F("Fail code #")); Serial.println(returncode);
  }
}

void power_on()
{
  Serial.println(F("FONA POWER ON"));

  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  uint8_t type = fona.type();
  Serial.print(F("Found "));
  switch (type)
  {
    case FONA800L:
      Serial.println(F("FONA 800L")); break;
    case FONA800H:
      Serial.println(F("FONA 800H")); break;
    case FONA808_V1:
      Serial.println(F("FONA 808 (v1)")); break;
    case FONA808_V2:
      Serial.println(F("FONA 808 (v2)")); break;
    case FONA3G_A:
      Serial.println(F("FONA 3G (American)")); break;
    case FONA3G_E:
      Serial.println(F("FONA 3G (European)")); break;
    default:
      Serial.println(F("???")); break;
  }

/*
  // Print module IMEI number.
  char imei[16] = {0}; // MUST use a 16 character buffer for IMEI!
  uint8_t imeiLen = fona.getIMEI(imei);
  if (imeiLen > 0) {
    Serial.print("Module IMEI: "); Serial.println(imei);
  }
  */

  // Optionally configure a GPRS APN, username, and password.
  // You might need to do this to access your network's GPRS/data
  // network.  Contact your provider for the exact APN, username,
  // and password values.  Username and password are optional and
  // can be removed, but APN is required.
  //fona.setGPRSNetworkSettings(F("m2mpremium"), F("sfr"), F("sfr"));

  // Optionally configure HTTP gets to follow redirects over SSL.
  // Default is not to follow SSL redirects, however if you uncomment
  // the following line then redirects over SSL will be followed.
  //fona.setHTTPSRedirect(true);

  Serial.println("delay 8s");
  delay(8000);
  if (!fona.enableGPRS(true))
    Serial.println(F("Failed to turn GPRS on"));

  Serial.println("delay 4s");
  delay(4000);
}

void getJSON(char * url)
{
  uint16_t statuscode;
  int16_t length;
  if(!fona.HTTP_GET_start(url, &statuscode, (uint16_t *)&length )) {
    Serial.println("getJSON failed!");
  }
  while (length > 0) {
  	while (fona.available()) {
	  char c = fona.read();
	  Serial.write(c);
	  length--;
	  if (! length) break;
	}
  }
  Serial.println("getJSON done");
  fona.HTTP_GET_end();
}
