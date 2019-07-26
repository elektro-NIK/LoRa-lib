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
    while(1) {
        uint8_t packetSize = parsePacket(0);
        if (packetSize) {
            uart_print_P("Received packet '");
            while(available()) {
                char c = read();
                uart_send(c);
            }
            uart_print_P("' with RSSI ");
            int8_t rssi = packetRssi();
            itoa(rssi, buffer, 10);
            uart_println(buffer, 4);
        }
    }
}
