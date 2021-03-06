/**
 **************************************************
 *
 * @file        reportUsreButton.ino
 * @brief       This is an example for DEVIO NB-DEVKIT I. That has read sensor on board and report data to Magellan IoT Platform.
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

#include "SIM7020-NB-IoT-SOLDERED.h"
Magellan_SIM7020E magel;          

String payload;
const int userButton = 12;

void setup() 
{
  Serial.begin(115200); //Begin serial communication with PC using baud rate of 115200 bauds/s
  magel.begin();               //Init Magellan LIB
  pinMode(userButton,INPUT);   //User switch
}

void loop() 
{
  /*
    Example report the user button to Magellan IoT platform
  */
  String struserButton="0";
  if(!digitalRead(userButton))              //Read button state
  {
    struserButton="1";
  }
  payload="{\"button\":"+struserButton+"}"; //Please provide payload with json format
  magel.report(payload);                    //Report Userbutton state
}
