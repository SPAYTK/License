
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define PI 3.141592653589793
#define ENTRADAS 16
#define FREQ_BASE_HZ 0.0014
#define ENERGIA_JULIOS 6.98

int entrada_digital[ENTRADAS] = {1,0,1,1,0,1,1,0,1,0,1,1,1,0,1,1};
uint8_t salida_digital[ENTRADAS];

void uart_init(void) {
    UBRR0H = 0;
    UBRR0L = 103;
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_print(const char *str) {
    while (*str) uart_transmit(*str++);
}

void uart_print_num(uint8_t num) {
    char buf[4];
    snprintf(buf, sizeof(buf), "%d", num);
    uart_print(buf);
}

void inicializar_chip() {
    uart_print("Chip Cuantico Iniciado\r\n");
}

double excitar_iones(int valor) {
    double determinante = (double)valor;
    double arcoc = acos(determinante > 1.0 ? 1.0 : determinante);
    double superposicion = atan(PI) * atan(fabs(-pow(arcoc, 2)));
    return superposicion;
}

uint8_t medir_qubit(double estado) {
    return (uint8_t)(((int)(estado * 1000)) % 2);
}

void procesar_datos() {
    for (int i = 0; i < ENTRADAS; i++) {
        double estado = excitar_iones(entrada_digital[i]);
        salida_digital[i] = medir_qubit(estado);
    }
}

void exportar_salida() {
    uart_print("Salida digital:\r\n");
    for (int i = 0; i < ENTRADAS; i++) {
        uart_print_num(salida_digital[i]);
        uart_transmit(' ');
    }
    uart_print("\r\n");
}

int main(void) {
    uart_init();
    inicializar_chip();
    procesar_datos();
    exportar_salida();
    while (1) {}
    return 0;
}
