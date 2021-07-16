#include <LiquidCrystal.h>


#define SENSOR A0
#define HEATER 10


LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

int value;
int i;

float tension;
float temperature;
float temperatureSumm;
float oldTemp;
float supLimit;
float infLimit;


void readInput(){
  
  for(i=0; i<20;i++){
      
      value = analogRead(SENSOR);
      tension = value*5 /1023.0;
     
      temperatureSumm+= tension/0.010;  //armazena o valore de temperaturas somando 20 vezes
      
    }
    
    temperature = temperatureSumm/20;  // faz uma média das 20 leituras de temperatura
    temperatureSumm = 0;  // zera temperatureSumm pára evitar leituras infinitas
    
    if(temperature != oldTemp){ // só atualiza o lcd se o valor atual for diferente do salvo
      lcd.clear();
      lcd.print ("Temp: "+ String(temperature));
      oldTemp = temperature;
     
    }
}


void checkTemperature(){
  // essa logica funciona bem
  if(temperature>supLimit){
    activateHeater(false);
  }
  if(temperature<infLimit){
    activateHeater(true);
  }
  
}


void activateHeater(bool option){ //função que ativa ou desativa heater
  if(option){
    analogWrite(HEATER, 255);
  }
  else{
    analogWrite(HEATER, 0);
  }
  
}




void setup () {
  //set variables
  temperatureSumm=0;
  oldTemp = 0;
  supLimit= 58.0;
  infLimit = 48.4;
  
  pinMode(HEATER, OUTPUT);
 
  lcd.begin (16, 2);
  lcd.print ("Temp: ");

}

void loop () {
  
  readInput();
  checkTemperature();
  delay(100);
}
