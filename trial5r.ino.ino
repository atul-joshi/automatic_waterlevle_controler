#include <SPI.h>
#include <RH_NRF24.h>
#define motor 8
// Singleton instance of the radio driver

 RH_NRF24 nrf24(2, 10); // use this to be electrically compatible with Mirf
int temp=0;

void setup() 
{
  pinMode(motor, OUTPUT);
  Serial.begin(9600);
  while (!Serial) 
     // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}

void loop()
{
  if (nrf24.available())
  {
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
//      NRF24::printBuffer("request: ", buf, len);
      Serial.print("tank is: ");
      Serial.println((char*)buf);
       Serial.print("cm empty ");

      delay(2000);
if((char*)buf<12 && temp==0)
{
digitalWrite(motor, LOW);


Serial.println("Water Tank Full ");

Serial.println("Motor Turned OFF");
delay(2000);
temp=1;
    }
    else if((char*)buf<12 && temp==1)
{
digitalWrite(motor, LOW);

Serial.print("Water Tank Full ");
Serial.println("Motor Turned OFF");
delay(5000);
temp=0;
}
    
    else
    {
      Serial.println("recv failed");
    }
  }
  }
}

