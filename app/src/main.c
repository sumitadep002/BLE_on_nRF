#include <zephyr/kernel.h>
#include "util.h"

bool ble_adv = false;

bool sw_0 = false;
bool sw_1 = false;

uint32_t time_stamp = 0;

static void gpio_callback(uint8_t pin, bool pressed)
{
        if (pin == UP && pressed == true)
        {
                ble_adv = true;
                sw_0 = true;
        }
        else if (pin == MID && pressed == true)
        {
                ble_adv = false;
                sw_1 = true;
        }
        else if (pin == LOW && pressed == true)
        {
        }
}

int main(void)
{
        setup_led();
        setup_button(gpio_callback);

        ble_init();

        while (1)
        {
                if (sw_0)
                {
                        sw_0 = false;
                        ble_start_adv();
                        ble_adv = true;

                        led_ctrl(GREEN, true);
                        k_msleep(250);
                        led_ctrl(GREEN, false);
                        k_msleep(250);
                        led_ctrl(GREEN, true);
                        k_msleep(250);
                        led_ctrl(GREEN, false);
                        k_msleep(250);
                }

                if (sw_1)
                {
                        ble_adv = false;
                        sw_1 = false;
                        ble_stop_adv();
                        ble_adv = false;

                        led_ctrl(RED, true);
                        k_msleep(250);
                        led_ctrl(RED, false);
                        k_msleep(250);
                        led_ctrl(RED, true);
                        k_msleep(250);
                        led_ctrl(RED, false);
                        k_msleep(250);
                }

                if ((sw_0 == false && ble_adv == true) && (k_uptime_get_32() - time_stamp > 250))
                {
                        time_stamp = k_uptime_get_32();

                        led_ctrl(BLUE, true);
                        k_msleep(250);
                        led_ctrl(BLUE, false);
                        k_msleep(250);
                }
        }

        return 0;
}
