#ifndef DHT11_H
#define DHT11_H

#include "main.h"

#define DHT11_DQ_OUT(x)  do{x?HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_SET):HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, GPIO_PIN_RESET);}while(0)
#define DHT11_DQ_IN    HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)


uint8_t dht11_read_data(uint8_t *temperature, uint8_t *humidity);

#endif // DHT11_H