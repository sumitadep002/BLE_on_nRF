#include "util.h"
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <stdio.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>

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

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, strlen(CONFIG_BT_DEVICE_NAME)),
};

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

static void (*gpio_callback)(uint8_t pin, bool state);

static struct gpio_callback gpio_cb;

static void gpio_isr(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
{
    if (gpio_callback)
    {
        for (uint8_t pin = 0; pin < 32; pin++)
        {
            if (pins & BIT(pin))
            {
                if (pin == sw_0.pin)
                    gpio_callback(UP, gpio_pin_get(port, pin));
                else if (pin == sw_1.pin)
                    gpio_callback(MID, gpio_pin_get(port, pin));
                else if (pin == sw_2.pin)
                    gpio_callback(LOW, gpio_pin_get(port, pin));
            }
        }
    }
}

void setup_button(void (*GpioCb)(uint8_t pin, bool state))
{
    if (!gpio_is_ready_dt(&sw_0))
    {
        printf("UP button not ready\n");
    }
    else
    {
        gpio_pin_configure_dt(&sw_0, GPIO_INPUT);
        gpio_pin_interrupt_configure_dt(&sw_0, GPIO_INT_EDGE_FALLING);
        printf("UP button configured\n");
    }

    if (!gpio_is_ready_dt(&sw_1))
    {
        printf("MID button not ready\n");
    }
    else
    {
        gpio_pin_configure_dt(&sw_1, GPIO_INPUT);
        gpio_pin_interrupt_configure_dt(&sw_1, GPIO_INT_EDGE_FALLING);
        printf("MID button configured\n");
    }

    if (!gpio_is_ready_dt(&sw_2))
    {
        printf("LOW button not ready\n");
    }
    else
    {
        gpio_pin_configure_dt(&sw_2, GPIO_INPUT);
        gpio_pin_interrupt_configure_dt(&sw_2, GPIO_INT_EDGE_FALLING);
        printf("LOW button configured\n");
    }

    gpio_callback = GpioCb;

    gpio_init_callback(&gpio_cb, gpio_isr, BIT(sw_0.pin) | BIT(sw_1.pin) | BIT(sw_2.pin));
    gpio_add_callback(sw_0.port, &gpio_cb);
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

void ble_init()
{
    int err = bt_enable(NULL);
    if (err)
    {
        printf("BLE-Init Failed (%d)\n", err);
    }
    else
    {
        printf("BLE-Intialized!!!\n");
    }
}

void ble_deinit()
{
    int err = bt_disable();
    if (err)
    {
        printf("BLE-DeInit Failed (%d)\n", err);
    }
    else
    {
        printf("BLE-DeIntialized!!!\n");
    }
}

void ble_start_adv()
{
    int err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err)
    {
        printf("Advertisement Failed to Start\n");
    }
    else
    {
        printf("Advertisement started...");
    }
}

void ble_stop_adv()
{
    int err = bt_le_adv_stop();
    if (err)
    {
        printf("Advertisement Failed to Stop\n");
    }
    else
    {
        printf("Advertisement stopped!!!");
    }
}