/**
 **************************************************
 *
 * @file        getControl.ino
 * @brief       Example for get swich data from Magellan IoT Platform
 *				please use payload with json format e.g. {"Temperature":25.5,"Humidity":90.4,"Light":45}
 *				and {"Location":"13.001,100.44"} for plot the location on MAP
 *								   |        |
 *								latitude  longitude 
 *
 *				and {"Lamp":0} or {"Lamp":1"} for show the Lamp status on dashboard
 *
 *
 *				product: www.solde.red/333072
 *
 * 				Modified by soldered.com
 *
 * @author		Device Innovation team     
 ***************************************************/

///  This is pinout for arduino UNO, for other board configuration check boards.h file
///    |  Do not use PIN  |
///    |  9 TX            |
///    |  8 RX            |
///    |  4 EINT          |
///    |  26 power key    |
///    |  5 reset         |

#include "SIM7020-NB-IoT-SOLDERED.h"
Magellan_SIM7020E magel;          

String sw_state;
String sw;
String payload;

void setup() 
{
  Serial.begin(115200);
  magel.begin();             //Init Magellan LIB
  payload="{\"sw\":0}";      //Please provide payload with json format
  magel.report(payload);     //Initial switch data to Magellan IoT Platform
}

void loop() 
{
  /*
    Example get swich data from Magellan IoT platform
  */
  sw_state=magel.getControl("sw"); //Get switch data from Magellan IoT platform
  
  if(sw_state.indexOf("40300")==-1) //Response data is not 40300
  {
    sw=sw_state;
  }

  Serial.print("sw ");
  Serial.println(sw);
}