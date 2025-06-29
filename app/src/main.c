#include <zephyr/kernel.h>
#include "util.h"

static volatile uint8_t led_state = GREEN;
static volatile bool ble_adv_state = false;

// Global static function declarations
static void gpio_callback(uint8_t pin, bool pressed);
static void ble_work_handler(struct k_work *work);
static void ble_timer_callback(struct k_timer *timer);

// global variable/structure declarations/defintions
K_WORK_DEFINE(ble_work, ble_work_handler);
K_TIMER_DEFINE(ble_timer, ble_timer_callback, NULL);

// global macros
#define BLE_TIMER_PERIOD 1
#define BLE_TIMER_DELAY (BLE_TIMER_PERIOD / 2)

int main(void)
{
        setup_led();
        setup_button(gpio_callback);

        ble_init();
        adc_init();

        while (1)
        {
        }

        return 0;
}

// Global static function declarations
void gpio_callback(uint8_t pin, bool pressed)
{
        if (pin == UP && pressed == true)
        {

                // invert state of ble advertising
                ble_adv_state = (!ble_adv_state);

                // start the advertising timer if advertising state is true
                if (ble_adv_state == true)
                {
                        // indicate green-led
                        led_state = GREEN;

                        // submit ble-work
                        k_work_submit(&ble_work);

                        k_timer_start(&ble_timer, K_SECONDS(BLE_TIMER_DELAY), K_SECONDS(BLE_TIMER_PERIOD));
                }
                else
                {
                        k_timer_stop(&ble_timer);

                        // indicate red-led
                        led_state = RED;

                        // submit ble-work
                        k_work_submit(&ble_work);
                }
        }
}

void ble_work_handler(struct k_work *work)
{
        // indicate green-led when advertising starts
        if (led_state == GREEN && ble_adv_state == true)
        {
                ble_start_adv();

                led_ctrl(GREEN, true);
                k_msleep(250);
                led_ctrl(GREEN, false);
                k_msleep(250);
                led_ctrl(GREEN, true);
                k_msleep(250);
                led_ctrl(GREEN, false);
                k_msleep(250);
        }

        // indicate red-led when advertising stops
        else if (led_state == RED && ble_adv_state == false)
        {
                ble_stop_adv();

                led_ctrl(RED, true);
                k_msleep(250);
                led_ctrl(RED, false);
                k_msleep(250);
                led_ctrl(RED, true);
                k_msleep(250);
                led_ctrl(RED, false);
                k_msleep(250);
        }

        // indicate blue-led when advertising is in process
        else if (led_state == BLUE)
        {
                // read battery voltage
                uint32_t voltage = get_device_voltage();

                // update ble-advertising packet
                ble_update_data(voltage);

                // indicate advertising
                led_ctrl(BLUE, true);
                k_msleep(250);
                led_ctrl(BLUE, false);
                k_msleep(250);
        }
}

void ble_timer_callback(struct k_timer *timer)
{
        if (ble_adv_state == true)
        {
                led_state = BLUE;

                k_work_submit(&ble_work);
        }
}