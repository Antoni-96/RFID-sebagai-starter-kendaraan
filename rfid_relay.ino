#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           
#define SS_PIN          10          

MFRC522 mfrc522(SS_PIN, RST_PIN);   

String read_rfid;                   
String ok_rfid_1="c66121f9";       
String ok_rfid_2="2bc540c";        
int relay1 = 7;                      
int relay2 = 6; 
int led_on = 8;

void setup() {
    Serial.begin(9600);         
    while (!Serial);            
    SPI.begin();               
    mfrc522.PCD_Init();         

    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);
    pinMode(led_on, OUTPUT);   
}

void dump_byte_array(byte *buffer, byte bufferSize) {
    read_rfid="";
    for (byte i = 0; i < bufferSize; i++) {
        read_rfid=read_rfid + String(buffer[i], HEX);
    }
}

void led() {
  digitalWrite(led_on,HIGH);
  delay(200);
  digitalWrite(led_on,LOW);
  delay(200);
  digitalWrite(led_on,HIGH);
  delay(200);
  digitalWrite(led_on,LOW);
}

void start() {  
  digitalWrite(relay1,LOW);
  delay(200);                
  digitalWrite(relay2,LOW);
  delay(900);                
  digitalWrite(relay2,HIGH);
}

void loop() {
    if ( ! mfrc522.PICC_IsNewCardPresent())
        return;
    if ( ! mfrc522.PICC_ReadCardSerial())
        return;

    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println(read_rfid);
    led();
    if (read_rfid==ok_rfid_1) {
      start();
    }

    Serial.println(read_rfid);
    if (read_rfid==ok_rfid_2) {
      start();
    }
}
