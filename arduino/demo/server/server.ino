#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>
#include <MirfSpiDriver.h>
#include <nRF24L01.h>


void setup() {
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = sizeof(unsigned long);
  Mirf.config();
  Serial.println("Beginning ... ");
}

void loop() {
  byte sendData[Mirf.payload]; // 最大32bit, byteの行列なので要素数は4

  if (Serial.available() >= 2) { // 受信したデータが存在する
    Serial.println(Serial.available());
    sendData[0] = Serial.read();
    sendData[1] = Serial.read();
    Mirf.setTADDR((byte *)"clie1");
    Mirf.send(sendData);
    Serial.print(sendData[0]);
    Serial.println(sendData[1]);


  }
}

