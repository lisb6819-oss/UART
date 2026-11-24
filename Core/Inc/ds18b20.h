#ifndef __DS18B20_H
#define __DS18B20_H

#include "main.h"

#include "usDelay.h"

#define DS18B20_DQ_OUT(x)  do{x?HAL_GPIO_WritePin(DS18_GPIO_Port, DS18_Pin, GPIO_PIN_SET):HAL_GPIO_WritePin(DS18_GPIO_Port, DS18_Pin, GPIO_PIN_RESET);}while(0)
#define DS18B20_DQ_IN    HAL_GPIO_ReadPin(DS18_GPIO_Port, DS18_Pin)



float ds18b20_get_temp(void);

#endif // __DS18B20_H