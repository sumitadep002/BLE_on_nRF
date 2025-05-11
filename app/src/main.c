#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#define RED 0
#define GREEN 1
#define BLUE 2

#define RED_LED DT_ALIAS(redled)
#define BLUE_LED DT_ALIAS(blueled)
#define GREEN_LED DT_ALIAS(greenled)

static const struct gpio_dt_spec led_0 = GPIO_DT_SPEC_GET(RED_LED, gpios);
static const struct gpio_dt_spec led_1 = GPIO_DT_SPEC_GET(GREEN_LED, gpios);
static const struct gpio_dt_spec led_2 = GPIO_DT_SPEC_GET(BLUE_LED, gpios);

void setup_led();
void led_ctrl(uint8_t led, bool state);

int main(void)
{
        setup_led();
        while (1)
        {
                led_ctrl(RED, true);
                k_msleep(250);
                led_ctrl(RED, false);
                k_msleep(250);

                led_ctrl(GREEN, true);
                k_msleep(250);
                led_ctrl(GREEN, false);
                k_msleep(250);

                led_ctrl(BLUE, true);
                k_msleep(250);
                led_ctrl(BLUE, false);
                k_msleep(250);
        }
        return 0;
}

void setup_led()
{
        // setup red-led
        if (!gpio_is_ready_dt(&led_0))
        {
                printf("Red LED GPIO device not ready\n");
        }
        else if (gpio_pin_configure_dt(&led_0, GPIO_OUTPUT_INACTIVE) != 0)
        {
                printf("Failed to configure Red LED pin\n");
        }
        else
        {
                printf("Red LED initialized successfully\n");
        }

        // setup green-led
        if (!gpio_is_ready_dt(&led_1))
        {
                printf("Greened LED GPIO device not ready\n");
        }
        else if (gpio_pin_configure_dt(&led_1, GPIO_OUTPUT_INACTIVE) != 0)
        {
                printf("Failed to configure Green LED pin\n");
        }
        else
        {
                printf("Green LED initialized successfully\n");
        }

        // setup blue-led
        if (!gpio_is_ready_dt(&led_2))
        {
                printf("Blue LED GPIO device not ready\n");
        }
        else if (gpio_pin_configure_dt(&led_2, GPIO_OUTPUT_INACTIVE) != 0)
        {
                printf("Failed to configure Blue LED pin\n");
        }
        else
        {
                printf("Blue LED initialized successfully\n");
        }
}

void led_ctrl(uint8_t led, bool state)
{
        if (led == RED)
        {
                gpio_pin_set_dt(&led_0, state);
                printf("Red-LED %d\n", state);
        }
        else if (led == GREEN)
        {
                gpio_pin_set_dt(&led_1, state);
                printf("Green-LED %d\n", state);
        }
        else if (led == BLUE)
        {
                gpio_pin_set_dt(&led_2, state);
                printf("Blue-LED %d\n", state);
        }
}
