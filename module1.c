#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "avr-libs-master/uart/uart.h"
#include "avr-libs-master/spi/spi.h"
#include "LoRa.h"

#define BUFF_LEN        64

/*@{*/ // Global variables
char buffer[BUFF_LEN];
/*@}*/

void Init() {
    uart_init();
    spi_init(0, 1, 0, 0, 1);                // MSB, master, mode0, F/4, x2
    if (!begin(868E6)) {
        uart_println_P("Starting LoRa failed!");
        while(1);
    }
}

int main() {
    Init();
    uint8_t counter = 0;
    while(1) {
        itoa(counter, buffer, 10);
        uart_print_P("Sending packet: ");
        uart_println(buffer, 3);

        beginPacket(0);
        itoa(counter, buffer, 10);
        write("hello ", 7);
        write(buffer, 3);
        endPacket();
        counter++;
        _delay_ms(5000);
    }
}
