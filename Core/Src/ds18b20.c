#include "ds18b20.h"
#include "usDelay.h"

void ds18b20_reset(void)
{
    DS18B20_DQ_OUT(0);
    delay_us(750);
    DS18B20_DQ_OUT(1);
    delay_us(15);

}

uint8_t ds18b20_check(void)
{
    uint8_t retry = 0;
    while(DS18B20_DQ_IN && retry < 200)
    {
        retry++;
        delay_us(1);
    }
    if (retry >= 200)
        return 1;
    else
        retry = 0;
    while(!DS18B20_DQ_IN && retry < 240)
    {
        retry++;
        delay_us(1);
    }
    if (retry >= 240)
        return 1;
    else
        return 0;
}

void ds18b20_write_0(void)
{
    DS18B20_DQ_OUT(0);
    delay_us(60);
    DS18B20_DQ_OUT(1);
    delay_us(5);
}

void ds18b20_write_1(void)
{
    DS18B20_DQ_OUT(0);
    delay_us(3);
    DS18B20_DQ_OUT(1);
    delay_us(60);
}

void ds18b20_write_byte(uint8_t dat)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (dat & 0x01)
            ds18b20_write_1();
        else
            ds18b20_write_0();
        dat >>= 1;
    }
}

uint8_t ds18b20_read_bit(void)
{
    uint8_t dat;
    DS18B20_DQ_OUT(0);
    delay_us(2);
    DS18B20_DQ_OUT(1);
    delay_us(12);
    if (DS18B20_DQ_IN)
        dat = 1;
    else
        dat = 0;
    delay_us(50);
    return dat;
}

uint8_t ds18b20_read_byte(void)
{
    uint8_t dat = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        dat >>= 1;
        if (ds18b20_read_bit())
            dat |= 0x80;
    }
    return dat;
}

float ds18b20_get_temp(void)
{
    uint8_t temp_l, temp_h;
    int16_t temp;
    float temperature;

    ds18b20_reset();
    ds18b20_check();
    ds18b20_write_byte(0xCC); // Skip ROM
    ds18b20_write_byte(0x44); // Convert T

    HAL_Delay(750); // Conversion must finish before reading; 750 ms is the 12-bit maximum.

    ds18b20_reset();
    ds18b20_check();
    ds18b20_write_byte(0xCC); // Skip ROM
    ds18b20_write_byte(0xBE); // Read Scratchpad

    temp_l = ds18b20_read_byte();
    temp_h = ds18b20_read_byte();

    temp = (temp_h << 8) | temp_l;
    temperature = (float)temp / 16.0;

    return temperature;
}