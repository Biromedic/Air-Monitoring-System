bool is_msb_set(uint16_t number) {
    // The 0x8000 mask is a 16-bit unsigned integer with a leftmost bit of 1
  return (number & 0x8000) ? 1 : 0;
}

void buzzer_beep() {
  for (int i = 0; i < 100; i++) { // Buzzer'ı belirli bir süre açıp kapat
    PORTD |= (1 << PD7); // Buzzer ON
    _delay_us(500);     
    PORTD &= ~(1 << PD7); // Buzzer OFF
    _delay_us(500);   
  }
}

void DigitalWrite(uint8_t pin, uint8_t value) {
    if (pin >= 0 && pin <= 7) { // Port D
        if (value == LOW) {
            PORTD &= ~(1 << pin); // Clear the corresponding bit in PORTD to set the pin LOW
        } else if (value == HIGH) {
            PORTD |= (1 << pin);  // Set the corresponding bit in PORTD to set the pin HIGH
        }
    } else if (pin >= 8 && pin <= 13) { // Port B
        pin -= 8; // Adjust pin number for Port B
        if (value == LOW) {
            PORTB &= ~(1 << pin); // Clear the corresponding bit in PORTB to set the pin LOW
        } else if (value == HIGH) {
            PORTB |= (1 << pin);  // Set the corresponding bit in PORTB to set the pin HIGH
        }
    } else if (pin >= 14 && pin <= 19) { // Port C (analog pins)
        pin -= 14; // Adjust pin number for Port C
        if (value == LOW) {
            PORTC &= ~(1 << pin); // Clear the corresponding bit in PORTC to set the pin LOW
        } else if (value == HIGH) {
            PORTC |= (1 << pin);  // Set the corresponding bit in PORTC to set the pin HIGH
        }
    }
}

uint8_t DigitalRead(uint8_t pin) {
  if (pin >= 0 && pin <= 7) { // Port D
      return (PIND & (1 << pin)) ? 1 : 0; // Read the corresponding bit in PIND
  } else if (pin >= 8 && pin <= 13) { // Port B
      pin -= 8; // adjust 
      return (PINB & (1 << pin)) ? 1 : 0; // Read the corresponding bit in PINB
  } else if (pin >= 14 && pin <= 19) { // Port C (analog pins)
      pin -= 14; // Adjust pin number for Port C
      return (PINC & (1 << pin)) ? 1 : 0; // Read the corresponding bit in PINC
  }
  return 0; // Return 0 if pin number is out of range
}

void PinMode(uint8_t pin, uint8_t mode) {
  if (pin >= 0 && pin <= 7) { // Port D
    if (mode == INPUT) {
      DDRD &= ~(1 << pin); // Clear the corresponding bit in DDRD to set the pin as input
      PORTD &= ~(1 << pin); // Clear the corresponding bit in PORTD to disable pull-up
    } else if (mode == OUTPUT) {
      DDRD |= (1 << pin);  // Set the corresponding bit in DDRD to set the pin as output
    } else if (mode == INPUT_PULLUP) {
      DDRD &= ~(1 << pin); // Clear the corresponding bit in DDRD to set the pin as input
      PORTD |= (1 << pin);  // Set the corresponding bit in PORTD to enable pull-up
    }
  } else if (pin >= 8 && pin <= 13) {// Port B
    pin -= 8; // adjust 
    if (mode == INPUT) {
      DDRB &= ~(1 << pin); // Clear the corresponding bit in DDRB to set the pin as input
      PORTB &= ~(1 << pin); // Clear the corresponding bit in PORTB to disable pull-up
    } else if (mode == OUTPUT) {
      DDRB |= (1 << pin);  // Set the corresponding bit in DDRB to set the pin as output
    } else if (mode == INPUT_PULLUP) {
      DDRB &= ~(1 << pin); // Clear the corresponding bit in DDRB to set the pin as input
      PORTB |= (1 << pin);  // Set the corresponding bit in PORTB to enable pull-up
    }
  } else if (pin >= 14 && pin <= 19) { // Port C 
    pin -= 14; // adjust 
    if (mode == INPUT) {
      DDRC &= ~(1 << pin); // Clear the corresponding bit in DDRC to set the pin as input
      PORTC &= ~(1 << pin); // Clear the corresponding bit in PORTC to disable pull-up
    } else if (mode == OUTPUT) {
      DDRC |= (1 << pin);  // Set the corresponding bit in DDRC to set the pin as output
    } else if (mode == INPUT_PULLUP) {
      DDRC &= ~(1 << pin); // Clear the corresponding bit in DDRC to set the pin as input
      PORTC |= (1 << pin);  // Set the corresponding bit in PORTC to enable pull-up
    }
  }
}

void delay_us(uint16_t us) {
    // Calibrate the inner loop to achieve approximately 1 microsecond delay
    // This example assumes an 8 MHz clock, 1 clock cycle = 0.125 microseconds
    // Adjust the number of NOP instructions accordingly
    while (us--) {
        // Each NOP (No Operation) takes 1 clock cycle
        // Assuming an 8 MHz clock, 1 clock cycle = 0.125 microseconds
        // 8 NOP instructions will make approximately 1 microsecond delay
        for (uint8_t i = 0; i < 8; i++) {
            __asm__ __volatile__("nop");
        }
    }
}

void delay_ms(uint16_t ms) {
    // Each loop iteration takes approximately 1 millisecond
    // This calibration may need adjustment based on your clock speed
    while (ms--) {
        delay_us(1000); // 1000 microseconds = 1 millisecond
    }
}


