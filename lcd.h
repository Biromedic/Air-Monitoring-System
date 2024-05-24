#define LCD_ADDR 0x27

void LCD_send_nibble(uint8_t data) {
    data |= 0x08; // En yüksek biti 1 yaparak arka ışığı açık tut
    I2C_start();
    I2C_write(LCD_ADDR << 1); // Send the I2C address of the LCD with the R/W bit cleared (write)
    I2C_write(data | 0x04); // Send high nibble with E high
    I2C_write(data & ~0x04); // Send high nibble with E low
    I2C_stop();
    _delay_us(50); // Short delay to let LCD process the nibble
}

void LCD_send_byte(uint8_t data, uint8_t rs) {
    uint8_t high_nibble = (data & 0xF0) | rs;
    uint8_t low_nibble = ((data << 4) & 0xF0) | rs;
    LCD_send_nibble(high_nibble);
    LCD_send_nibble(low_nibble);
}

void LCD_send_command(uint8_t command) {
    LCD_send_byte(command, 0x00);
    _delay_ms(2); // Most commands take 40 us, but clear and home commands require more time
}

void LCD_send_data(uint8_t data) {
    LCD_send_byte(data, 0x01);
}

void LCD_init(void) {
    _delay_ms(50); // Wait for LCD to power up
    LCD_send_command(0x03);
    _delay_ms(5);
    LCD_send_command(0x03);
    _delay_us(150);
    LCD_send_command(0x03);
    LCD_send_command(0x02); // Switch to 4-bit mode
    LCD_send_command(0x28); // Function set: 4-bit mode, 2 line, 5x8 dots
    LCD_send_command(0x0C); // Display on, Cursor off, Blink off
    LCD_send_command(0x01); // Clear display
    _delay_ms(2); // Clear command needs more time
    LCD_send_command(0x06); // Entry mode set: Increment automatically, No display shift
}

void LCD_set_cursor(uint8_t col, uint8_t row) {
    uint8_t address = (row == 0) ? col : (col + 0x40);
    LCD_send_command(0x80 | address);
}

void LCD_print(char *str) {
    while (*str) {
        LCD_send_data(*str++);
    }
}
void LCD_clear(void) {
    LCD_send_command(0x01); // Clear display command
    _delay_ms(2); // Clear command requires more time
}