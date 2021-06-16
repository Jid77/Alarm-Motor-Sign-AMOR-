#include <SoftwareSerial.h>
#include <EEPROM.h>

SoftwareSerial A6Module(2, 3 ); //RX,TX
//char phone_no[]="085720300952"; //Nomorhp

//input
int SENKIRI = 12;
int SENKANAN = 9;
int RELAY1 = 4;
int RELAY2 = 6;
int RELAY3 = 7;
int eekiri  = 11;
int eekanan = 8;

int prog= A0;
int L1 = 0;
int L2 = 0;
int R1 = 0;
int R2 = 0;
//indikator
int tik=13;
int ctik=0;

int eeL1;
int eeR1;
int eeL2;
int eeR2;
//int eejsalah;
//eeprom
int eepL1=0;
int eepR1=1;
int eepL2=2;
int eepR2=3;
//int eepjsalah=4;

int modeprog=0;
int modekode=0;
int alarm=0;
String _buffer;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 A6Module.begin(115200);
 delay(500);


 pinMode(SENKIRI, INPUT);
 pinMode(SENKANAN, INPUT);
 pinMode(prog, INPUT);
 pinMode(eekiri, INPUT);
 pinMode(eekanan, INPUT);
 pinMode(tik, OUTPUT);
 digitalWrite(SENKIRI,HIGH);
 digitalWrite(SENKANAN,HIGH);
 digitalWrite(prog,HIGH);
 digitalWrite(eekanan,HIGH);
 digitalWrite(eekiri,HIGH);
 pinMode(RELAY1, OUTPUT);
 pinMode(RELAY2, OUTPUT);
 pinMode(RELAY3, OUTPUT);
 alarm=0;
// sms=0;
for (int i=0;i<5;i++)
    { 
    digitalWrite(tik,HIGH);
    delay(100);
    digitalWrite(tik,LOW);
    delay(100);
    }
    L1=0;    
    R1=0;
    L2=0;
    R2=0;
    
    eeL1=EEPROM.read(eepL1);
    delay(100);  
 
    eeR1=EEPROM.read(eepR1);
    delay(100);  
 
    eeL2=EEPROM.read(eepL2);
    delay(100);  
 
    eeR2=EEPROM.read(eepR2);
    delay(100);  
    
    //eejsalah=EEPROM.read(eepjsalah);
    //delay(100);  
    //eejsalah=0;
    modekode=0;
    modeprog=0;
    }

void loop() {
            
           /* Serial.print (cekpulsa());
             while(1){;}
             */
            ubahkode();
            
            if (modeprog==0){bacakode();}
            
            if (alarm)
              {
               //digitalWrite(RELAY2,HIGH); 
               
             
               while(1)
                    {
                     digitalWrite(RELAY2,HIGH); 
                     delay(500);
                     digitalWrite(RELAY2,LOW); 
                     delay(500);
                     }
                     
              }
            
            }
 
 
void SMS() 
          {
          A6Module.println("AT+CMGF=1");
          delay(2000);
          A6Module.print("AT+CMGS=\"0895383122321");//GANTI NO HP DISINI
          A6Module.print(char(34));  // "
          A6Module.print(char(13));  // CR
          A6Module.print('\r');  // hex equivalent of newline
          delay(2000);
          A6Module.print("MALING BOS!! DANGER");
          delay(500);
          A6Module.println (char(26));  //ctrl_z
          }

void CALL()
      {
          A6Module.println("AT");    //Sets the GSM Module in Text Mode
          delay(1000);  // Delay of 1000 milli seconds or 1 second
          A6Module.print("ATD"); // Replace x with mobile number
   //       A6Module.println(phone_no);
          delay(8000);
          A6Module.println("ATH");// ASCII code of CTRL+Z
      }   
/*
String cekpulsa()
          {
          A6Module.println("AT+CUSD=1,\"*123#\"");
     
          delay(5000);
          _buffer=bacagsm();
          Serial.println(_buffer);
          while(1){;}
          
          uint8_t _idx1=_buffer.indexOf("Rp");
          Serial.println(_idx1);
          
          return _buffer.substring(_idx1,_buffer.indexOf(".A",_idx1));
          }

String bacagsm()
          {
          int to=0;
          while  (!A6Module.available() && to < 12000  )
                {
                delay(13);
                to++;
                }
          if (A6Module.available()) 
                {
                return A6Module.readString();
                }
            else
                {
                return "no respon";
                }
            }*/
            
void ubahkode()
            {
            if (modeprog==0)
              {
            if (digitalRead(prog)==LOW)
                 {
                 delay(3000);
                 if (digitalRead(prog)==LOW)     
                    {modeprog=1;modekode=0;eeL1=0;eeR1=0;eeL2=0;eeR2=0;}
                 }
               }
            if (modeprog)
               {
                digitalWrite(tik,HIGH);
                
                if (modekode==0)
                  {
                  if(digitalRead(eekiri)==LOW)
                    {
                    eeL1++;

                    
                    Serial.print(eeL1);
                    Serial.print(eeR1);
                    Serial.print(eeL2);
                    Serial.println(eeR2);
                    
                    digitalWrite(13,LOW);
                    delay(500);
                    while(digitalRead(eekiri)==LOW){;}
                    digitalWrite(13,HIGH);
                    }
                  }

              if ((modekode==1)||(modekode==0))
                  {          
                  if(digitalRead(eekanan)==LOW)
                    {
                    modekode=1;
                    eeR1++;
                    Serial.print(eeL1);
                    Serial.print(eeR1);
                    Serial.print(eeL2);
                    Serial.println(eeR2);
                    digitalWrite(13,LOW);
                    delay(500);
                    while(digitalRead(eekanan)==LOW){;}
                    digitalWrite(13,HIGH);
                    }
                  }

                  if ((modekode==1)||(modekode==2))
                     {
                      if(digitalRead(eekiri)==LOW)
                       {
                       modekode=2;
                       eeL2++;
                    Serial.print(eeL1);
                    Serial.print(eeR1);
                    Serial.print(eeL2);
                    Serial.println(eeR2);
                       digitalWrite(13,LOW);
                       delay(500);
                       while(digitalRead(eekiri)==LOW){;}
                       digitalWrite(13,HIGH);
                       }
                     }

                   if (modekode==2)
                    {
                      if(digitalRead(eekanan)==LOW)
                      {
                      eeR2++;
                             Serial.print(eeL1);
                    Serial.print(eeR1);
                    Serial.print(eeL2);
                    Serial.println(eeR2);
                      digitalWrite(13,LOW);
                      delay(500);
                      while(digitalRead(eekanan)==LOW){;}
                      digitalWrite(13,HIGH);
                      }
                     }
             
             
            
             
             if (digitalRead(prog)==LOW)
                    {
                    delay(3000);
                    if (digitalRead(prog)==LOW)     
                        {
                        EEPROM.write(eepL1,eeL1);
                        delay(100);
                        EEPROM.write(eepR1,eeR1);
                        delay(100);
                        EEPROM.write(eepL2,eeL2);
                        delay(100);
                        EEPROM.write(eepR2,eeR2);
                        delay(100);
                        modekode=0;modeprog=0;digitalWrite(tik,LOW);delay(2000);
                        Serial.println("KeluarModeProg");
                        }
                    }
                }    
            }

    
  void bacakode()
            {      
            if (modekode==0)
            {
            if(digitalRead(SENKIRI)==LOW)
                {
                L1++;
                   Serial.print(L1);
                    Serial.print(R1);
                    Serial.print(L2);
                    Serial.println(R2);
                digitalWrite(13,HIGH);
                delay(500);
                while(digitalRead(SENKIRI)==LOW){;}
                digitalWrite(13,LOW);
                }
            }

            if ((modekode==0)||(modekode==1))
                {
                if(digitalRead(SENKANAN)==LOW)
                {
                modekode=1;
                R1++;
                  Serial.print(L1);
                    Serial.print(R1);
                    Serial.print(L2);
                    Serial.println(R2);
                digitalWrite(13,HIGH);
                delay(500);
                while(digitalRead(SENKANAN)==LOW){;}
                digitalWrite(13,LOW);
                }
                }
    
            if ((modekode==1)||(modekode==2))
                {
                if(digitalRead(SENKIRI)==LOW)
                {
                modekode=2;
                L2++;
                    Serial.print(L1);
                    Serial.print(R1);
                    Serial.print(L2);
                    Serial.println(R2);
                digitalWrite(13,HIGH);
                delay(500);
                while(digitalRead(SENKIRI)==LOW){;}
                digitalWrite(13,LOW);
                }
                } 

    if (modekode==2)
    {
    if(digitalRead(SENKANAN)==LOW)
    {
    R2++;
      Serial.print(L1);
              Serial.print(R1);
              Serial.print(L2);
              Serial.println(R2);
    digitalWrite(13,HIGH);
    delay(500);
    while(digitalRead(SENKANAN)==LOW){;}
    digitalWrite(13,LOW);
    }
    }
    





  
   if(((L1-1)==eeL1)&&(R1==eeR1)&&(L2==eeL2)&&(R2==eeR2))
      {
       digitalWrite(RELAY3,HIGH);
       Serial.println("ON MOTOR");
       while(1){;}
      }
      else
      {
       digitalWrite(RELAY3,LOW);
      }
        


    

   
   if(((L1-1) > eeL1)||(R1 > eeR1)||(L2 > eeL2)||(R2 > eeR2))
        {
          //digitalWrite(RELAY2,HIGH);
          // eejsalah++;
          //if (eejsalah>3)
             // {
                        alarm=1;  
          A6Module.println("AT+CMGF=1");
          delay(2000);
          A6Module.print("AT+CMGS=\"0895383122321");//GANTI NO HP DISINI
          A6Module.print(char(34));  // "
          A6Module.print(char(13));  // CR
          A6Module.print('\r');  // hex equivalent of newline
          delay(2000);
          A6Module.print("MALING BOS!! DANGER");
          delay(500);
          A6Module.println (char(26));  //ctrl_z                  
                Serial.println("ADA MALING");

                     //}               
          //else
           //{
          //L1=0;L2=0;R1=0;R2=0;
             
            // }
        }
   else 
        {
       digitalWrite(RELAY2,LOW);
       alarm=0;
       
        }
  
    }
    
