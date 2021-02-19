#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"

#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#include <mipea/gpio.h>

int gpio_loop(void){
    OS_printf("hello-uart.c entry point.\n:");

    if (gpio_map() < 0) { // map peripherals
        OS_printf("WARNING: Could not perform gpio_map().\n");
        return 1;
    }

    int out_pin = 26;
    gpio_out(out_pin);

    while(true) {
        gpio_set(out_pin);
        OS_printf("GPIO on\n");
        usleep(3 * 1000 * 1000);
        gpio_clr(out_pin);
        OS_printf("GPIO off\n");
        usleep(3 * 1000 * 1000);
    }
}
