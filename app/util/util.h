#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stdbool.h>

#define RED 0
#define GREEN 1
#define BLUE 2

#define UP 0
#define MID 1
#define LOW 2

void setup_led(void);
void led_ctrl(uint8_t led, bool state);

void setup_button(void);
bool read_button(uint8_t button);

#endif // UTIL_H
