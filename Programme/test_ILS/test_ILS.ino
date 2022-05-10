/*******************************************************************************/
 
/*macro definitions of magnetic pin and LED pin*/
#define MAGNECTIC_SWITCH 2

void setup()
{
    pinsInit();
}
 
void loop() 
{
    if(isNearMagnet())//if the magnetic switch is near the magnet?
    {
        Serial.print ("Activé") ;
    }
    else
    {
        Serial.print("éteint");
    }
}
void pinsInit()
{
    pinMode(MAGNECTIC_SWITCH, INPUT);
}
 
/*If the magnetic switch is near the magnet, it will return ture, */
/*otherwise it will return false                                */
boolean isNearMagnet()
{
    int sensorValue = digitalRead(MAGNECTIC_SWITCH);
    if(sensorValue == HIGH)//if the sensor value is HIGH?
    {
        return true;//yes,return ture
    }
    else
    {
        return false;//no,return false
    }
}



