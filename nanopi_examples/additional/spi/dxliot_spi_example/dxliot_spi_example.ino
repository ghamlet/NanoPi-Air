#include<SPI.h> // библиотека для работы с шиной SPI
#define LEDpin 7  // Установка пина, к которому подключен светодиод
volatile boolean received; // переменная состояния получения данных
volatile byte Slavereceived,Slavesend; // переменная для хранения данных

void setup()
{
  pinMode(LEDpin,OUTPUT);   // Установка пин 7 на вывод
  pinMode(MISO,OUTPUT);     // Установка MISO на вывод
  SPCR |= _BV(SPE);         // Установка SPI в режим ведомого
  received = false;
  SPI.attachInterrupt();   // включение прерывания для протокола SPI
  
}
ISR (SPI_STC_vect)         // функция обработки прерывания 
{
  Slavereceived = SPDR;    // сохранение полученных данных в переменную
  received = true;                     
}
void loop()
{ if(received)                            
   {
      if (Slavereceived==1) // Если полученное значение равно 1
      {
        digitalWrite(LEDpin,HIGH);         //включение светодиода
      }else                // Если полученное значение не равно 1
      {
        digitalWrite(LEDpin,LOW);          //выключение светодиода
      }
    
   }
}
