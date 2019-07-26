#include <inttypes.h>                           //for uint8_t, etc
#include <avr/pgmspace.h>                       //for accessing program memory
#include "uart.h"

//UART constants
const uint8_t UART = 0;                         //which UART to use
const unsigned long BAUD_RATE = 300;            //the baud rate in bits/sec
const uint8_t BUFF_LEN = 64;
const uint8_t ECHO = 1;                         //echo when getting user input. 1=echo on, 0=echo off

//some text to display
const char PROGMEM welcome_text[] = "An example string";

int main(){
  //declare a buffer
  char buffer[BUFF_LEN];

  //initialize the UART
  uart_init();

  //print the welcome text
  uart_println_P("Hello world!");

  //print the prompt
  uart_print_P("Type some characters, then press Enter: ");
  //get the input from the user
  uart_getln(buffer, BUFF_LEN, ECHO);

  //print the result message
  uart_print_P("You typed: ");
  //print the buffer
  uart_println(buffer, BUFF_LEN);

  return 0;
}
