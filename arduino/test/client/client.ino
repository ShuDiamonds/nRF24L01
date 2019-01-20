#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
 
const int ssrpin = 9;
 
void setup(){
  pinMode(ssrpin, OUTPUT);
  digitalWrite(ssrpin, LOW);
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(unsigned long);
  Mirf.config();
  Serial.println("Beginning ... ");
}
 
void loop(){
  const byte buttonOpen = 10;
  const byte buttonClose = 20;
  unsigned long time = millis();
  byte recvData[Mirf.payload];  // 最大32bit, byteの行列なので要素数は4
 
  Mirf.setTADDR((byte *)"serv1");
  Mirf.send(recvData);  // 適当な信号を送信
  while(Mirf.isSending()) {
  }
  while (!Mirf.dataReady()) {
    if ((millis() - time) > 2000 ) {
      Serial.println("Timeout on response from server!");
      return;
    }
  }
  Mirf.getData(recvData);
  if (recvData[0] == 'A') {  
    if(recvData[1]) digitalWrite(ssrpin,HIGH);
    else digitalWrite(ssrpin,LOW);
  }
  Serial.print("recvData: ");
  for (int i = 0;i < Mirf.payload;i++) {
    Serial.print(recvData[i]);
    Serial.print(" ");
  }
  Serial.println();
  delay(100);
}

