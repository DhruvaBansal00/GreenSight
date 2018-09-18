#include <DataCoder.h>
#include <VirtualWire.h>

const int rx_pin = 11;
const int led_pin = 9;
const int led_pin2 = 8;
const int transmit_pin = 12;

float var;
int inr;
float vro;


void setup()

{
 
 Serial.begin(9600);
 
 pinMode(led_pin,OUTPUT);
 pinMode(led_pin2,OUTPUT);

 vw_set_tx_pin(transmit_pin);
 vw_set_rx_pin(rx_pin);
 vw_setup(1000);
 vw_rx_start(); 
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  union RFData inDataSeq;

  float inArray[RF_DATA_ARRAY_SIZE];

  if(vw_get_message(buf,&buflen))
  {
    digitalWrite(led_pin, HIGH);

    for(int i =0;i< buflen; i++)
    {
      inDataSeq.s[i] = buf[i];
      
    }
     Serial.println();
     
     digitalWrite(led_pin, LOW);

     DecodeRFData(inArray, inDataSeq);

     Serial.print("Incoming data : ");

     for (int i=0;i<RF_DATA_ARRAY_SIZE;i++)
     {
      Serial.print(inArray[i]);
      Serial.print(", ");
     }
     
     var = inArray[0];
     
  
        if((var == 10) && (inArray[1] == 0.00))
     
         {
          //Transmitting
          for(int j=0;j<5;j++)
          {
          transmit();
          
          }
     
          }
             
  }
  
}

void transmit()
{
  float outArray[RF_DATA_ARRAY_SIZE];

  outArray[0] = 101;
  

  union RFData outDataSeq;

  EncodeRFData(outArray, outDataSeq);

  TransmitRFData(outDataSeq);
  Serial.println("here");
}
