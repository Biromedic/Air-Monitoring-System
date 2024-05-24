#define DHT22_PIN 2
uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void Request() {
    DDRB |= (1<<DHT22_PIN);
    PORTB &= ~(1<<DHT22_PIN);
    _delay_ms(20);
    PORTB |= (1<<DHT22_PIN);
}

void Response() {
    DDRB &= ~(1<<DHT22_PIN);
    while(PINB & (1<<DHT22_PIN));
    while((PINB & (1<<DHT22_PIN))==0);
    while(PINB & (1<<DHT22_PIN));
}

uint8_t Receive_data() {
    uint8_t data = 0;
    for (int q=0; q<8; q++) {
        while((PINB & (1<<DHT22_PIN)) == 0);
        _delay_us(30);
        if(PINB & (1<<DHT22_PIN))
            data = (data<<1)|(0x01);
        else
            data = (data<<1);
        while(PINB & (1<<DHT22_PIN));
    }
    return data;
}
