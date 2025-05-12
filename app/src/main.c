#include <zephyr/kernel.h>
#include "util.h"

int main(void)
{
        setup_led();
        setup_button();

        while (1)
        {
                bool state = read_button(UP);
                led_ctrl(RED, state);

                state = read_button(MID);
                led_ctrl(GREEN, state);

                state = read_button(LOW);
                led_ctrl(BLUE, state);

                k_msleep(2000);
        }

        return 0;
}
