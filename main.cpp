/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "HDC1080.h"
#include "MPL3115A2.h"
#include "OPT3001.h"
#include "VEML6075.h"

DigitalOut led(LED1);
HDC1080 hdc1080(I2C_SDA, I2C_SCL);
MPL3115A2 mpl3115a2(I2C_SDA, I2C_SCL, (0x60 << 1));
OPT3001 opt3001(I2C_SDA, I2C_SCL);
VEML6075 veml6075(I2C_SDA, I2C_SCL, 0x10);

int main(void)
{
    float sensor_data[2], delta[2];
    printf("\n*** MM-ENV01 sensor test program ***\n\n");

    veml6075.setUVConf(0x00);
    mpl3115a2.Oversample_Ratio(OVERSAMPLE_RATIO_128);
    mpl3115a2.Barometric_Mode();

    while(1) {
        printf("HDC1080  : temp = %5.2f DegC, hum = %5.2f %%\n", hdc1080.readTemperature(), hdc1080.readHumidity());
        if ( mpl3115a2.getAllData(sensor_data, delta)) {
            printf("MPL3115A2: temp = %5.2f DegC, press = %7.2f hPa\n", sensor_data[1], sensor_data[0]/100);
        }
        printf("OPT3001  : light = %d lux\n", opt3001.readSensor());
        printf("VEML6075 : UVA = %f, UVB = %f, UVI = %5.2f\n", veml6075.getUVA(), veml6075.getUVB(), veml6075.UVI());
        printf("\n");

        led = !led;
        thread_sleep_for(2000);
    }
}