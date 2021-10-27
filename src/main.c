#include <stdio.h>
#include <stdlib.h>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/can.h>  // just put this here to show the driver for canbus protokol built into esp32 libraries
#include <driver/uart.h>


#define LED1 18
#define LED2 19

TaskHandle_t mytask1handle = NULL;

void task1(void *arg)
{
    while(1)
    {
        gpio_set_level(LED1,1);
        printf("core%d  %dHz \n",xPortGetCoreID(),ets_get_cpu_frequency());
        vTaskDelay(1000/portTICK_PERIOD_MS);
        gpio_set_level(LED1,0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
     
}

void task2(void *arg)
{
    while(1)
    {
        gpio_set_level(LED2,1);
        printf("core%d  %dHz \n",xPortGetCoreID(),ets_get_cpu_frequency());
        vTaskDelay(300/portTICK_PERIOD_MS);
        gpio_set_level(LED2,0);
        vTaskDelay(300/portTICK_PERIOD_MS);
    }
    
}

void app_main() {

    uart_set_stop_bits(0,1);

    gpio_set_direction(LED1,GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    xTaskCreatePinnedToCore(task1,"task 1",1024*2,NULL,2,NULL,0);
    //xTaskCreate(task2,"task 2",1024*2,NULL,2,NULL);
    xTaskCreatePinnedToCore(task2,"task 2",1024*2,NULL,2,NULL,1);
    
    while(1)
    {

    }
}