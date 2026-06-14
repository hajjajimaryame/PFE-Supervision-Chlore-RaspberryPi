#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;
int led = 9;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  while (!Serial);

  // init 
  if (!rf95.init()) {
    Serial.println("init failed");
    while (1);
  }

  // setFrequency  
  if (!rf95.setFrequency(868.0)) {
    Serial.println("frequency failed");
    while (1);
  }

  Serial.println("RF95 ready");
}

void loop() {
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      digitalWrite(led, HIGH);

      // Print data 
      Serial.print("DATA:");         
      Serial.write(buf, len);
      Serial.println();              

      
      uint8_t data[] = "OK";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();

      digitalWrite(led, LOW);
    }
    else {
      Serial.println("recv failed");
    }
  }
}
