#include <stdio.h>
#include "pico/stdlib.h"

 
#define LATCH_PIN 13
#define CLOCK_PIN 14
#define DATA_PIN 15

#define BTN_B 0
#define BTN_Y 1
#define BTN_SELECT 2
#define BTN_START 3
#define BTN_UP 4
#define BTN_DOWN 5
#define BTN_LEFT 6
#define BTN_RIGHT 7
#define BTN_A 8
#define BTN_X 9
#define BTN_L 10
#define BTN_R 11

uint16_t buttons;

bool get_button(int btn) {
    return (buttons >> btn) & 0x1;
}

int main(void) 
{
    stdio_init_all();

    printf("Pico SNES joypad\n");

    gpio_init(LATCH_PIN);
    gpio_init(CLOCK_PIN);
    gpio_init(DATA_PIN);

    gpio_set_dir(LATCH_PIN, 1); // Output
    gpio_set_dir(CLOCK_PIN, 1); // Output
    gpio_set_dir(DATA_PIN, 0);  // Input

    gpio_put(LATCH_PIN, 0);
    gpio_put(CLOCK_PIN, 1);
    gpio_pull_up(DATA_PIN);
    
    while (true)
    {
        // TODO Use PIO to free CPU
        // Read controller every 16 milliseconds
        sleep_us(16000);

        buttons = 0;

        // Latch buttons state
        gpio_put(LATCH_PIN, 1);
        sleep_us(12);
        gpio_put(LATCH_PIN, 0);

        // Read all 16 positions
        for (int i=0; i<16; i++) {
            sleep_us(6);
            gpio_put(CLOCK_PIN, 0);

            buttons |= (gpio_get(DATA_PIN) & 1) << i;

            sleep_us(6);
            gpio_put(CLOCK_PIN, 1);
        }

        printf("Joypad: A=%d B=%d X=%d Y=%d / 0x%04x\n", get_button(BTN_A), get_button(BTN_B), get_button(BTN_X), get_button(BTN_Y), buttons);
    }

    return 0;
}
