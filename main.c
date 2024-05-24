#include <avr/io.h>
#include <util/delay.h>
#include "functions.h"
#include "i2c.h"
#include "lcd.h"
#include "dht.h"
#include "usart.h"

void setup() {
  USART_init(103); // 9600 baud rate for 16 MHz clock
  I2C_init();
  LCD_init();
  LCD_set_cursor(0, 0);
  LCD_print("Initializing");

  // LED pinlerini çıkış olarak ayarla
  DDRD |= (1 << PD5); // LED 1
  DDRD |= (1 << PD6); // LED 2
  DDRD |= (1 << PD7); // Buzzer

  TCCR1A = (1 << COM1A0) | (1 << WGM10); // Toggle OC1A on Compare Match, Fast PWM 8-bit
  TCCR1B = (1 << WGM12) | (1 << CS10); // No prescaler
}

void loop() {
  char data[5];
  _delay_ms(1000);

  Request(); /* send start pulse */
  Response(); /* receive response */
  I_RH = Receive_data(); /* store first eight bit in I_RH */
  D_RH = Receive_data(); /* store next eight bit in D_RH */
  I_Temp = Receive_data(); /* store next eight bit in I_Temp */
  D_Temp = Receive_data(); /* store next eight bit in D_Temp */
  CheckSum = Receive_data(); /* store next eight bit in CheckSum */

  uint16_t humidity = (I_RH << 8) + D_RH;
  uint16_t temperature = ((I_Temp << 8) | D_Temp);
  int16_t temperature_real;
  uint8_t calculated_sum = I_RH + D_RH + I_Temp + D_Temp;
  if(is_msb_set(temperature)){
    temperature = temperature & 0x7FFF;
    temperature_real=temperature*(-1);
    }else {
        temperature_real = temperature;
    }

  int tmp=humidity / 10;
    LCD_set_cursor(0, 0);
    LCD_print("Humidity: ");
    itoa(tmp,data,10);
    LCD_print(data);
    LCD_print(".");
    tmp=humidity % 10;
    itoa(tmp,data,10);
    LCD_print(data);

    // *-*- *-*-*-*-*--*---*-*-*-*-*-*-*-*-- 

    tmp=temperature_real / 10;
    LCD_set_cursor(0, 1);
    LCD_print("Temp: ");
    itoa(tmp,data,10);
    LCD_set_cursor(7,1);
    LCD_print(data);
    LCD_print(".");
    tmp=temperature % 10;
    itoa(tmp,data,10);
    LCD_print(data);

    if (temperature_real < 200) {
        PORTD |= (1 << PD5);  // LED 1 ON
        PORTD &= ~(1 << PD6); // LED 2 OFF
    } else if (temperature_real >= 200 && temperature_real < 350) {
        PORTD &= ~(1 << PD5); // LED 1 OFF
        PORTD |= (1 << PD6);  // LED 2 ON
    } else {
        PORTD &= ~(1 << PD5); // LED 1 OFF
        PORTD &= ~(1 << PD6); // LED 2 OFF
        buzzer_beep();        // Buzzer bip sesi
    }

  // Nem ve sıcaklık değerlerini seri port üzerinden yazdır
  char buffer[16];
  snprintf(buffer, sizeof(buffer), "%d.%d %u.%u", temperature_real / 10, tmp, humidity / 10, humidity % 10);
  USART_println(buffer);


  _delay_ms(1000); 
}
