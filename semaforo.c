#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define led_green 11
#define led_blue 12
#define led_red 13

uint32_t idx = 13;

// Como a simulação será feita na placa BitDogLab, a qual não possui led amarelo,
// consideraremos o led_blue como o amarelo. 


bool repeating_timer_callback(struct repeating_timer *t) {
    switch (idx) {
        case 11: //verde
            gpio_put(led_blue,false);
            gpio_put(led_green,true);
            idx = 13;
            break;
        case 12: //amarelo
            gpio_put(led_red,false);
            gpio_put(led_blue,true);
            idx = 11;
            break;
        case 13: //vermelho
            gpio_put(led_green,false);
            gpio_put(led_red,true);
            idx = 12;
            break;
    }
    return true;
}

int main(){
    stdio_init_all();

    gpio_init(led_red);
    gpio_init(led_green);
    gpio_init(led_blue);

    gpio_set_dir(led_red,GPIO_OUT);
    gpio_set_dir(led_green,GPIO_OUT);
    gpio_set_dir(led_blue,GPIO_OUT);   
    
    
    gpio_put(led_red,true);
    idx = 12;

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while(true){
        sleep_ms(1000);
        printf("Se passou 1 segundo\n");
    }
}