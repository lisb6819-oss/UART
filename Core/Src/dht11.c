#include "dht11.h"
#include "stm32f1xx_hal.h"
#include "usDelay.h"
#include <stdint.h>

void dht11_reset(void)
{
    DHT11_DQ_OUT(0);
    HAL_Delay(20);
    DHT11_DQ_OUT(1);
    delay_us(13);
}

uint8_t dht11_check(void)
{
    uint8_t retry = 0;
    while(DHT11_DQ_IN && retry < 100)
    {
        retry++;
        delay_us(1);
    }
    if (retry >= 100)
        return 1;
    else
        retry = 0;
    while(!DHT11_DQ_IN && retry < 100)
    {
        retry++;
        delay_us(1);
    }
    if (retry >= 100)
        return 1;
    else
        return 0;
}

uint8_t dht11_read_bit(void)
{
    uint8_t retry = 0;
    while(DHT11_DQ_IN && retry < 100)
    {
        retry++;
        delay_us(1);
    }
    retry = 0;
    while(!DHT11_DQ_IN && retry < 100)
    {
        retry++;
        delay_us(1);
    }
    delay_us(40);
    if(DHT11_DQ_IN)
        return 1;
    else
        return 0;
}

uint8_t dht11_read_byte(void)
{
    uint8_t i, dat = 0;
    for(i = 0; i < 8; i++)
    {
        dat <<= 1;
        dat |= dht11_read_bit();
    }
    return dat;
}

uint8_t dht11_read_data(uint8_t *temperature, uint8_t *humidity)
{
    uint8_t i;
    uint8_t data[5] = {0};

    dht11_reset();
    if(dht11_check())
        return 1;

    for(i = 0; i < 5; i++)
    {
        data[i] = dht11_read_byte();
    }

    if(data[4] == (data[0] + data[1] + data[2] + data[3]))
    {
        *humidity = data[0];
        *temperature = data[2];
        return 0;
    }
    else
    {
        return 1;
    }
}