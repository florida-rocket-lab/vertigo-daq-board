#ifndef ADXL_375
#define ADXL_375
#include <stdint.h>

enum adxl375_regs
{
    DEVID = 0x00,
    THRESH_SHOCK = 0x1D,
    OFSX = 0x1E,
    OFSY = 0x1F,
    OFSZ = 0x20,
    DUR = 0x21,
    Latent = 0x22,
    Window = 0x23,
    THRESH_ACT = 0x24,
    THRESH_INACT = 0x25,
    TIME_INACT = 0x26,
    ACT_INACT_CTL = 0x27,
    SHOCK_AXES = 0x2A,
    ACT_SHOCK_STATUS = 0x2B,
    BW_RATE = 0x2C,
    POWER_CTL = 0x2D,
    INT_ENABLE = 0x2E,
    INT_MAP = 0x2F,
    INT_SOURCE = 0x30,
    DATA_FORMAT = 0x31,
    DATAX0 = 0x32,
    DATAX1 = 0x33,
    DATAY0 = 0x34,
    DATAY1 = 0x35,
    DATAZ0 = 0x36,
    DATAZ1 = 0x37,
    FIFO_CTL = 0x38,
    FIFO_STATUS = 0x39
};

typedef union
{
    uint8_t value;
    struct
    {
        uint8_t wakeup : 2;
        uint8_t sleep : 1;
        uint8_t measure : 1;
        uint8_t auto_sleep : 1;
        uint8_t link : 1;
        uint8_t reserved : 2;
    };
} power_config_u;

typedef union
{
    uint8_t value;

    struct
    {
        uint8_t range : 2;
        uint8_t justify : 1;
        uint8_t full_res : 1;
        uint8_t reserved : 1;
        uint8_t int_invert : 1;
        uint8_t spi : 1;
        uint8_t self_test : 1;
    };
} data_format_u;

typedef struct
{
    float data_x;
    float data_y;
    float data_z;
} adxl375_data_s;

void adxl375_init();

void adxl375_read(adxl375_data_s *data);

void mem_write(uint8_t reg, uint8_t *val, uint16_t size);

void mem_read(uint8_t reg, uint8_t *val, uint16_t size);

#endif