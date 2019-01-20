#include <Mirf.h>
#include <MirfHardwareSpiDriver.h>
#include <MirfSpiDriver.h>
#include <nRF24L01.h>
//
//#include <SPI.h>
//#include <Mirf.h>
//#include <nRF24L01.h>
//#include <MirfHardwareSpiDriver.h>
 
 
void setup() {
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = sizeof(unsigned long);
  Mirf.config();
  Serial.println("Listening...");
}
 
void loop() {
  byte sendData[Mirf.payload]; // 最大32bit, byteの行列なので要素数は4
 
  if (!Mirf.isSending() && Mirf.dataReady()) {
    Serial.println("Got packet");
    Mirf.getData(sendData);  // 適当な信号を受信
    Mirf.setTADDR((byte *)"clie1");
    
      sendData[0] = 10;
    Mirf.send(sendData);
    Serial.println("Reply sent.");
  }
}

