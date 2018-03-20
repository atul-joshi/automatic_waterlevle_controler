#include <SPI.h>
#include <RH_NRF24.h>
const int trigpin =5;
const int echopin=4;
long duration;
int distance;


// Singleton instance of the radio driver

RH_NRF24 nrf24(2, 10); // For RFM73 on Anarduino Mini

void setup() 
{
  Serial.begin(9600); 
  pinMode(trigpin,OUTPUT);
 pinMode(echopin,INPUT);
  
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");   
}

void loop(){
  Sensor();
}
  
void Sensor(){
  digitalWrite(trigpin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigpin,HIGH);
 delayMicroseconds(10);
 duration = pulseIn(echopin,HIGH);
 distance =duration*0.034/2;
 digitalWrite(trigpin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigpin,HIGH);
 delayMicroseconds(10);
 duration = pulseIn(echopin,HIGH);
 distance =duration*0.034/2;
  Serial.print("\nDistance in centimeters: ");
  Serial.print(distance);
  delay(500);  

  Send_Data();
}

void Send_Data(){
  
  nrf24.send(distance, sizeof(distance));
  nrf24.waitPacketSent(); 
}

