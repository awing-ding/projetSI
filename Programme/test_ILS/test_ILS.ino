#include <rgb_lcd.h>

/*******************************************************************************/
 
/*macro definitions of magnetic pin and LED pin*/
#define MAGNECTIC_SWITCH 2
#define COURSE 0.074 //mètre
#define FROTTEMENT_VISQUEUX 19554

float calculate_energy(float t);

String previous = "Eteint";

float energy = 0;
int last_time = 0;
int this_time = 0;
int duration = 0;
int pas = 0;

rgb_lcd lcd;

void setup()
{
    pinsInit();
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.setRGB(200, 200, 255);
}
 
void loop() 
{
    if (isNearMagnet())//if the magnetic switch is near the magnet?
    {
       if (previous == "Eteint") {
          previous = "Activé";

          if (millis() - this_time >= 1000) { //vérifie qu'il s'agit d'un pas et pas d'un parasite
            pas += 2; //incrémente le compteur de pas
            
            last_time = this_time; //vide la variable "temps actuel" de la dernière valeur et la met dans "ancien temps" 
            this_time = millis(); //met la variable "temps actuel" au temps écoulé depuis le début du programme
            duration = this_time - last_time; //calcule le temps qu'a duré le pas
            energy = energy + calculate_energy(duration/1000); //calcule l'energie dépensée depuis le début du programme grâce à la fonction dédiée
          
            lcd.setCursor(0, 0); //affiche le résultat à l'écran en écrasant l'ancienne écriture
            lcd.print(energy) ;
            lcd.print(" calories ");

            lcd.setCursor(0, 1);
            lcd.print(pas);
            lcd.print(" pas");
            Serial.print(pas);
        }
       }
    }
    else
    {
      if (previous == "Activé") {
          previous = "Eteint";
      }
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
    if (sensorValue == HIGH)//if the sensor value is HIGH?
    {
       
        return true;//yes,return ture
    }
    else
    {
      
        return false;//no,return false
    }
}

/*Calcule l'energie dépensée au cours d'un pas */
float calculate_energy(float t)
{
  
  float time_for_one_step = t / 2;
  float speed_a_step = COURSE / time_for_one_step;
  float power_a_step = FROTTEMENT_VISQUEUX * (speed_a_step * speed_a_step);
  float energy_a_step = power_a_step * t;
  float energy = energy_a_step * 2;
  float energy_in_Cal = energy / 4180;
  return energy_in_Cal;

}


