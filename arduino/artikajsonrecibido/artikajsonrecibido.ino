#include <ArduinoJson.h>
#include <math.h>

double Sensor(int analog) {
 double Temp;
 Temp = log(10000.0*((1024.0/analog-1)));
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp *
 Temp ))* Temp );
 Temp = Temp - 273.15;
 return Temp;
}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
  }
}

void loop() {
  if (Serial.available() > 0) {
    delay(50);
    StaticJsonBuffer<200> jsonBuffer;
    String bufferString = "";

    while (Serial.available() > 0) {
      bufferString += (char)Serial.read();
    }

    // Length (with one extra character for the null terminator)
    int str_len = bufferString.length() + 1; 

    // Prepare the character array (the buffer) 
    char jsonS[str_len];

    // Copy it over 
    bufferString.toCharArray(jsonS, str_len);
    JsonObject& json = jsonBuffer.parseObject(jsonS);
  
    if (!json.success()) {
      Serial.println("error");
      return;
    }

    String tipo = json["tipo"];
    int pin1 = json["pin1"];
    int pin2 = json["pin2"];
    int orden = json["orden"];
    int value2;

    if (tipo == "A") {
      Serial.println("Analógico");
    } else if (tipo == "S") {
      StaticJsonBuffer<500> jsonResp;

      JsonObject& root = jsonResp.createObject();
      // Create the "analog" array
      JsonArray& values = root.createNestedArray("values");
      for (int pin = 0; pin < 6; pin++) {
        // Read the analog input
        int value = analogRead(pin);
        double temp= Sensor(value);
        
        value2 = (int) temp;
        // Add the value at the end of the array
        values.add(value2);
      }
      for (int pin = 2; pin < 14; pin++) {
        // Read the digital input
        int value = digitalRead(pin);
        
        // Add the value at the end of the array
        values.add(value);
      }
    
      root.printTo(Serial);
    } else if (tipo == "D") {
      if (orden == 0) {
        digitalWrite(pin1, 0);
        if (pin2 != 0) {
          digitalWrite(pin2, 0);
        }
      } else if (orden == 1) {
        if (pin2 != 0) {
          digitalWrite(pin2, 0);
        }
        digitalWrite(pin1, 1);
      } else if (orden == 2) {
        digitalWrite(pin1, 0);
        digitalWrite(pin2, 1);
      } else {
        Serial.print(-1);
      }

      Serial.print(orden);
    }
  }
}

