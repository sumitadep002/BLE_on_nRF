#include "util.h"
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <stdio.h>

#define RED_LED DT_ALIAS(redled)
#define GREEN_LED DT_ALIAS(greenled)
#define BLUE_LED DT_ALIAS(blueled)

#define UP_BUTTON DT_ALIAS(upbutton)
#define MID_BUTTON DT_ALIAS(midbutton)
#define LOW_BUTTON DT_ALIAS(lowbutton)

static const struct gpio_dt_spec led_0 = GPIO_DT_SPEC_GET(RED_LED, gpios);
static const struct gpio_dt_spec led_1 = GPIO_DT_SPEC_GET(GREEN_LED, gpios);
static const struct gpio_dt_spec led_2 = GPIO_DT_SPEC_GET(BLUE_LED, gpios);

static const struct gpio_dt_spec sw_0 = GPIO_DT_SPEC_GET(UP_BUTTON, gpios);
static const struct gpio_dt_spec sw_1 = GPIO_DT_SPEC_GET(MID_BUTTON, gpios);
static const struct gpio_dt_spec sw_2 = GPIO_DT_SPEC_GET(LOW_BUTTON, gpios);

void setup_led(void)
{
    if (!gpio_is_ready_dt(&led_0))
    {
        printf("Red LED not ready\n");
    }
    else
    {
        gpio_pin_configure_dt(&led_0, GPIO_OUTPUT_INACTIVE);
        printf("Red LED configured\n");
    }

    if (!gpio_is_ready_dt(&led_1))
    {
        printf("Green LED not ready\n");
    }
    else
    {
        gpio_pin_configure_dt(&led_1, GPIO_OUTPUT_INACTIVE);
        printf("Green LED configured\n");
    }

    if (!gpio_is_ready_dt(&led_2))
    {
        printf("Blue LED not ready\n");
    }
    else
    {
        gpio_pin_configure_dt(&led_2, GPIO_OUTPUT_INACTIVE);
        printf("Blue LED configured\n");
    }
}

void led_ctrl(uint8_t led, bool state)
{
    switch (led)
    {
    case RED:
        gpio_pin_set_dt(&led_0, state);
        printf("RED LED -> %d\n", state);
        break;
    case GREEN:
        gpio_pin_set_dt(&led_1, state);
        printf("GREEN LED -> %d\n", state);
        break;
    case BLUE:
        gpio_pin_set_dt(&led_2, state);
        printf("BLUE LED -> %d\n", state);
        break;
    default:
        break;
    }
}

void setup_button(void)
{
    if (!gpio_is_ready_dt(&sw_0))
    {
        printf("UP button not ready\n");
    }
    else
    {
        gpio_pin_configure_dt(&sw_0, GPIO_INPUT);
        printf("UP button configured\n");
    }

    if (!gpio_is_ready_dt(&sw_1))
    {
        printf("MID button not ready\n");
    }
    else
    {
        gpio_pin_configure_dt(&sw_1, GPIO_INPUT);
        printf("MID button configured\n");
    }

    if (!gpio_is_ready_dt(&sw_2))
    {
        printf("LOW button not ready\n");
    }
    else
    {
        gpio_pin_configure_dt(&sw_2, GPIO_INPUT);
        printf("LOW button configured\n");
    }
}

bool read_button(uint8_t button)
{
    int value = 0;

    switch (button)
    {
    case UP:
        value = gpio_pin_get_dt(&sw_0);
        printf("Reading UP button -> %d\n", value);
        break;
    case MID:
        value = gpio_pin_get_dt(&sw_1);
        printf("Reading MID button -> %d\n", value);
        break;
    case LOW:
        value = gpio_pin_get_dt(&sw_2);
        printf("Reading LOW button -> %d\n", value);
        break;
    default:
        return false;
    }

    return value == 1;
}
