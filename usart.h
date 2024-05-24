void USART_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void USART_print(const char *str) {
    while (*str) {
        USART_transmit(*str++);
    }
}

void USART_println(const char *str) {
    USART_print(str);
    USART_transmit('\n');
}
