




#include <WiFi.h>
#include <Firebase_ESP_Client.h>

// Connect to Motor A output on Driver 1
const int ina1 = 23; // Motor Open 1 (MO1)
const int ina2 = 22; // Motor Open 1 (MO1)

// Connect to Motor B output on Driver 1
const int ina3 = 1; // Motor Close 1 (MC1)
const int ina4 = 3; // Motor Close 1 (MC1)


// ## Pin Definitions for L298N Driver 2 (Gate 2) ##
// Connect to Motor A output on Driver 2
const int inb1 = 21; // Motor Open 2 (MO2)
const int inb2 = 19; // Motor Open 2 (MO2)

// Connect to Motor B output on Driver 2
const int inb3 = 18; // Motor Close 2 (MC2)
const int inb4 = 5; // Motor Close 2 (MC2)

const int Close = 4; // Motor Close 2 (MC2)

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Airtel_M-1102"
#define WIFI_PASSWORD "amc@m1102"

/* 2. Define the API Key */
#define API_KEY "AIzaSyA27lgwgBhByNuye_b5hVOZTeK7IjLLbis"

/* 3. Define the RTDB URL */
#define DATABASE_URL "https://saarthi-84622-default-rtdb.asia-southeast1.firebasedatabase.app/"

/* 4. Define the user Email and password that already registered or added in your project */
#define USER_EMAIL "naman.saarthi@gmail.com"
#define USER_PASSWORD "12345678"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

const int ledPin1 = 15  ;


void setup()
{
  

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  pinMode(Close, INPUT_PULLUP);
  pinMode(ina1, OUTPUT);
  pinMode(ina2, OUTPUT);
  pinMode(ina3, OUTPUT);
  pinMode(ina4, OUTPUT);
  pinMode(inb1, OUTPUT);
  pinMode(inb2, OUTPUT);
  pinMode(inb3, OUTPUT);
  pinMode(inb4, OUTPUT);
  stop_all_motors();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
  Firebase.reconnectNetwork(true);

  // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
  // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
  fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;
  
}


void loop()
{
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    // Handle /index/hom
    int activate = 0;
    if (Firebase.RTDB.getInt(&fbdo, "activate", &activate))
    {
      Serial.print("On?: ");
      Serial.println(activate);

      if (activate == 1)
      {
        stop_all_motors();
        gate1_open();
        gate2_open();
        Firebase.RTDB.setInt(&fbdo,"activate", 0);  
      }
      else if((digitalRead(Close))==LOW){
        
        gate2_close();
        gate1_close();
      }
      
  }
}}


void gate1_open() {
  // Stop the "close" motor first to be safe
  digitalWrite(ina1, LOW);
  digitalWrite(ina2, LOW);
  digitalWrite(ina3, LOW);
  digitalWrite(ina4, LOW);
  
  digitalWrite(ina4, HIGH);
  digitalWrite(ina3, LOW);

  delay(1000);

  digitalWrite(ina1, HIGH);
  digitalWrite(ina2, LOW);

  delay(2000);

  digitalWrite(ina1, LOW);
  digitalWrite(ina2, LOW);

  delay(9000);

  digitalWrite(ina4, LOW);
  digitalWrite(ina3, LOW);
  
  
}

void gate1_close() {
  // Stop the "open" motor first to be safe
  digitalWrite(ina1, LOW);
  digitalWrite(ina2, LOW);
  digitalWrite(ina3, LOW);
  digitalWrite(ina4, LOW);

  // Run the "close" motor (MC1)
  digitalWrite(ina2, HIGH);
  digitalWrite(ina1, LOW);
  digitalWrite(ina3, HIGH);
  digitalWrite(ina4, LOW);
  delay(2000);
  digitalWrite(ina1, LOW);
  digitalWrite(ina2, LOW);
  delay(10000);
  digitalWrite(ina3, LOW);
  digitalWrite(ina4, LOW);
  
}

// ======================================================
// ## Gate 2 Control Functions ##
// ======================================================

void gate2_open() {
  // Stop the "close" motor first to be safe
  // Stop the "close" motor first to be safe
  digitalWrite(inb1, LOW);
  digitalWrite(inb2, LOW);
  digitalWrite(inb3, LOW);
  digitalWrite(inb4, LOW);
  
  digitalWrite(inb4, HIGH);
  digitalWrite(inb3, LOW);

  delay(1000);

  digitalWrite(inb1, HIGH);
  digitalWrite(inb2, LOW);

  delay(3000);

  digitalWrite(inb1, LOW);
  digitalWrite(inb2, LOW);

  delay(6000);

  digitalWrite(inb4, LOW);
  digitalWrite(inb3, LOW);
  

}

void gate2_close() {
  // Stop the "open" motor first to be safe
  digitalWrite(inb1, LOW);
  digitalWrite(inb2, LOW);
  digitalWrite(inb3, LOW);
  digitalWrite(inb4, LOW);

  // Run the "close" motor (MC1)
  digitalWrite(inb2, HIGH);
  digitalWrite(inb1, LOW);
  digitalWrite(inb3, HIGH);
  digitalWrite(inb4, LOW);
  delay(3000);
  digitalWrite(inb1, LOW);
  digitalWrite(inb2, LOW);
  delay(9000);
  digitalWrite(inb3, LOW);
  digitalWrite(inb4, LOW);
}

// ======================================================
// ## Helper Function ##
// ======================================================

// Stops all four motors
void stop_all_motors() {
  // Stop Gate 1 motors
  digitalWrite(ina1, LOW);
  digitalWrite(ina2, LOW);
  digitalWrite(ina3, LOW);
  digitalWrite(ina4, LOW);
  
  // Stop Gate 2 motors
  digitalWrite(inb1, LOW);
  digitalWrite(inb2, LOW);
  digitalWrite(inb3, LOW);
  digitalWrite(inb4, LOW);
}
