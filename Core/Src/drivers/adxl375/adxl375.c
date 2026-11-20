#include "adxl375.h"
#include "i2c.h"
#include <math.h>

#define ADXL375_ADDR 0x53
#define SENSOR_SCALE_FACTOR 0.049f
#define OFFSET_SCALE_FACTOR 0.196f
#define X_OFFSET 0
#define Y_OFFSET 0
#define Z_OFFSET 0

void adxl375_init()
{
    //Setup Data Format Register to set the range to +/- 16g and full resolution mode
    data_format_u data_format;
    data_format.value = 0;
    data_format.range = 3;
    data_format.full_res = 1;
    data_format.justify = 0;
    mem_write(DATA_FORMAT, &data_format.value, 1);

    //Step 1: enter device into measurement mode in POWER_CTL register
    power_config_u config;
    config.measure = 1;
    mem_write(POWER_CTL, &config.value, 1);

    int8_t offsets[3] = {
        (int8_t)round(X_OFFSET / OFFSET_SCALE_FACTOR),
        (int8_t)round(Y_OFFSET / OFFSET_SCALE_FACTOR),
        (int8_t)round(Z_OFFSET / OFFSET_SCALE_FACTOR)
    };

    mem_write(OFSX, (uint8_t *)offsets, 3);
}

void adxl375_read(adxl375_data_s *data) //correct
{
    uint8_t buff[6];
    mem_read(DATAX0, buff, 6);

    int16_t data_x = (int16_t)(uint16_t)buff[1] << 8 | buff[0];
    int16_t data_y = (int16_t)(uint16_t)buff[3] << 8 | buff[2];
    int16_t data_z = (int16_t)(uint16_t)buff[5] << 8 | buff[4];

    //Final Value should be in Gs
    data->data_x = data_x * SENSOR_SCALE_FACTOR;   
    data->data_y = data_y * SENSOR_SCALE_FACTOR;
    data->data_z = data_z * SENSOR_SCALE_FACTOR;
}

void mem_write(uint8_t reg, uint8_t *val, uint16_t size)
{
    HAL_I2C_Mem_Write(&hi2c1, ADXL375_ADDR << 1, reg, I2C_MEMADD_SIZE_8BIT, val, size, HAL_MAX_DELAY);
}

void mem_read(uint8_t reg, uint8_t *val, uint16_t size)
{
    HAL_I2C_Mem_Read(&hi2c1, ADXL375_ADDR << 1, reg, I2C_MEMADD_SIZE_8BIT, val, size, HAL_MAX_DELAY);
}