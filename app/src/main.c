#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#define RED 0
#define GREEN 1
#define BLUE 2

#define UP 0
#define MID 1
#define LOW 2

#define RED_LED DT_ALIAS(redled)
#define BLUE_LED DT_ALIAS(blueled)
#define GREEN_LED DT_ALIAS(greenled)

static const struct gpio_dt_spec led_0 = GPIO_DT_SPEC_GET(RED_LED, gpios);
static const struct gpio_dt_spec led_1 = GPIO_DT_SPEC_GET(GREEN_LED, gpios);
static const struct gpio_dt_spec led_2 = GPIO_DT_SPEC_GET(BLUE_LED, gpios);

void setup_led();
void led_ctrl(uint8_t led, bool state);

#define UP_BUTTON DT_ALIAS(upbutton)
#define MID_BUTTON DT_ALIAS(midbutton)
#define LOW_BUTTON DT_ALIAS(lowbutton)

static const struct gpio_dt_spec sw_0 = GPIO_DT_SPEC_GET(UP_BUTTON, gpios);
static const struct gpio_dt_spec sw_1 = GPIO_DT_SPEC_GET(MID_BUTTON, gpios);
static const struct gpio_dt_spec sw_2 = GPIO_DT_SPEC_GET(LOW_BUTTON, gpios);

void setup_led();
void led_ctrl(uint8_t led, bool state);

void setup_button();
bool read_button(uint8_t button);

int main(void)
{
        setup_led();
        setup_button();
        bool state = false;
        while (1)
        {
                state = read_button(UP);
                led_ctrl(RED, state);

                state = read_button(MID);
                led_ctrl(GREEN, state);

                state = read_button(LOW);
                led_ctrl(BLUE, state);
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

void setup_button()
{
        // setup up-button
        if (!gpio_is_ready_dt(&sw_0))
        {
                printf("MID-BUTTON GPIO device not ready\n");
        }
        else if (gpio_pin_configure_dt(&sw_0, GPIO_INPUT) != 0)
        {
                printf("Failed to configure UP-BUTTON pin\n");
        }
        else
        {
                printf("UP-BUTTON initialized successfully\n");
        }

        // setup mid-button
        if (!gpio_is_ready_dt(&sw_1))
        {
                printf("MID-BUTTON GPIO device not ready\n");
        }
        else if (gpio_pin_configure_dt(&sw_1, GPIO_INPUT) != 0)
        {
                printf("Failed to configure MID-BUTTON pin\n");
        }
        else
        {
                printf("MID-BUTTON initialized successfully\n");
        }

        // setup low-button
        if (!gpio_is_ready_dt(&sw_2))
        {
                printf("LOW-BUTTON GPIO device not ready\n");
        }
        else if (gpio_pin_configure_dt(&sw_2, GPIO_INPUT) != 0)
        {
                printf("Failed to configure LOW-BUTTON pin\n");
        }
        else
        {
                printf("LOW-BUTTON initialized successfully\n");
        }
}
bool read_button(uint8_t button)
{
        int ret = false;

        if (button == UP)
        {
                ret = gpio_pin_get_dt(&sw_0);
                if (ret != 0 && ret != 1)
                {
                        printf("Error while reading UP-Button\n");
                        return false;
                }
                else
                {
                        printf("Reading UP-Button -> %d\n", ret);
                }
        }

        else if (button == MID)
        {
                ret = gpio_pin_get_dt(&sw_1);
                if (ret != 0 && ret != 1)
                {
                        printf("Error while reading MID-Button\n");
                        return false;
                }
                else
                {
                        printf("Reading UP-Button -> %d\n", ret);
                }
        }

        else if (button == LOW)
        {
                ret = gpio_pin_get_dt(&sw_2);
                if (ret != 0 && ret != 1)
                {
                        printf("Error while reading LOW-Button\n");
                        return false;
                }
                else
                {
                        printf("Reading UP-Button -> %d\n", ret);
                }
        }

        return ret;
}