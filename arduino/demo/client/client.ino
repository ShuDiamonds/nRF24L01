#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

const int ssrpin = 9;

void setup() {
  pinMode(ssrpin, OUTPUT);
  digitalWrite(ssrpin, LOW);
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(unsigned long);
  Mirf.config();
  Serial.println("Listening...");
}

void loop() {
  byte recvData[Mirf.payload];  // 最大32bit, byteの行列なので要素数は4

  Mirf.setTADDR((byte *)"serv1");

  if (Mirf.dataReady()) {
    Mirf.getData(recvData);
    if (recvData[0] == 'A') {
      if (recvData[1] == '1') digitalWrite(ssrpin, HIGH);
      else digitalWrite(ssrpin, LOW);
    }
    //debug
    Serial.print("recvData: ");
    for (int i = 0; i < Mirf.payload; i++) {
      Serial.print(recvData[i]);
      Serial.print(" ");
    }
    Serial.println();
  }



  delay(100);
}

