/**
 **************************************************
 *
 * @file        AdvancePUBUSB.ino
 * @brief       This is an example for DEVIO NB-DEVKIT I.
 *
 *
 *				      product: www.solde.red/333072
 *
 * 				      Modified by soldered.com
 *
 * @author		  Device Innovation team     
 ***************************************************/

//Connection diagram for Dasduino Core(or any other ATMega328P board),
//for other boards check boards.h file in this library
//Breakout      Arduino
//|-------------|
//VCC-----------5V
//RXD-----------4
//TXD-----------2
//PWRKEY--------5
//ADC-----------NOT CONNECTED
//UARTRI--------NOT CONNECTED
//GND-----------GND

#include "SIM7020-NB-IoT-API-SOLDERED.h"
String address    = "";               //Your IPaddress or mqtt server url
String serverPort = "";               //Your server port
String clientID   = "";               //Your client id < 120 characters
String topic      = "";               //Your topic     < 128 characters
String payload    = "HelloWorld!";    //Your payload   < 500 characters
String username   = "";               //username for mqtt server, username <= 100 characters
String password   = "";               //password for mqtt server, password <= 100 characters 
int keepalive     = 60;               //keepalive time (second)
int version       = 3;                //MQTT veresion 3(3.1), 4(3.1.1)
int cleansession  = 1;                //cleanssion : 0, 1
int willflag      = 1;                //willflag : 0, 1
unsigned int subQoS       = 0;          
unsigned int pubQoS       = 0;
unsigned int will_qos     = 0;
unsigned int will_retain  = 0;
unsigned int pubRetained  = 0;
unsigned int pubDuplicate = 0;

const long interval = 5000;           //time in millisecond 
unsigned long previousMillis = 0;

AIS_SIM7020E_API nb;
  /*  This part is for setupAdvanceMQTT.
   *  parameter for will option (Last will and Testament)
   *  will_topic : String
   *  will_qos   : unsinged int : 0, 1, 2
   *  will_retain: unsinged int : 0, 1
   *  will_msg   : String */
String willOption = nb.willConfig("will_topic",will_qos,will_retain,"will_msg");
int cnt = 0;

void setup()
{
  Serial.begin(115200); //Begin serial communication with PC using baud rate of 115200 bauds/s
  nb.begin();                   // Initialize SIM7020
  setupMQTT();                  // Initialize MQTT server
  nb.setCallback(callback);     // Set callback
  previousMillis = millis();    // Take timestamp
}

void loop()
{   
  nb.MQTTresponse();            // Check if SIM7020 have response
  unsigned long currentMillis = millis(); // Take current timestamp
  if (currentMillis - previousMillis >= interval) 
  {
        cnt++;  // Count responses
        connectStatus();  // Check 
        // QoS = 0, 1, or 2, retained = 0 or 1, dup = 0 or 1
        nb.publish(topic, payload+String(cnt), pubQoS, pubRetained, pubDuplicate); //Publish payload within  1000 characters.
        previousMillis = currentMillis;  
  }
}

//=========== MQTT Function ================
void setupMQTT(){
  /*  parameter for setup advance MQTT
   *  version    : MQTT veresion 3(3.1), 4(3.1.1)
   *  cleanssion : 0, 1
   *  willflag   : 0, 1
   *  **PLEASE ADD PARAMETER IN willOption** */
   if(!nb.connectAdvanceMQTT(address,serverPort,clientID,username,password,
                              keepalive,version,cleansession,willflag,willOption))
   // Setup module to use MQTT include serverIP, port, clientID, username, password, keep alive 
   {
     Serial.println("\nconnectMQTT");
    }
    nb.subscribe(topic,subQoS); // Subscribe to the topic to receive data
//    nb.unsubscribe(topic); 
}

void connectStatus()
{
    if(!nb.MQTTstatus())  //Check MQTT connection status.
    {
        if(!nb.NBstatus())  //Check NB connection status.
        {
           Serial.println("reconnectNB ");
           nb.begin();
        }
       Serial.println("reconnectMQ ");
       setupMQTT(); //Initialize MQTT 
    }   
}

//Call this function when data is received
void callback(String &topic,String &payload, String &QoS,String &retained)
{
  Serial.println("-------------------------------"); //Print received data
  Serial.println("# Message from Topic \""+topic+"\" : "+nb.toString(payload));   //Decode payload
  Serial.println("# QoS = "+QoS);
  if(retained.indexOf(F("1"))!=-1)
  {
    Serial.println("# Retained = " + retained);
  }
}
