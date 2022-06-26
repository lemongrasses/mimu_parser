#ifndef mimu22BL_parser_mimu_parser_H_
#define mimu22BL_parser_mimu_parser_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <math.h>

typedef struct imuData *imuDataPointer;
struct imuData {
    float time;
    float pressure;
    float pressure_temp;
    float accx1;
    float accy1;
    float accz1;
    float gyrox1;
    float gyroy1;
    float gyroz1;
    float accx2;
    float accy2;
    float accz2;
    float gyrox2;
    float gyroy2;
    float gyroz2;
    float accx3;
    float accy3;
    float accz3;
    float gyrox3;
    float gyroy3;
    float gyroz3;
    float accx4;
    float accy4;
    float accz4;
    float gyrox4;
    float gyroy4;
    float gyroz4;
    float temp1;
    float temp2;
    float temp3;
    float temp4;
    float magx1;
    float magy1;
    float magz1;
    float magx2;
    float magy2;
    float magz2;
    float magx3;
    float magy3;
    float magz3;
    float magx4;
    float magy4;
    float magz4;
    float fumagx;
    float fumagy;
    float fumagz;
    int16_t checksum;
}imuData;

char *base_name(char *pathname)
{
    char *lastsep = strrchr(pathname, '/');
    return lastsep ? lastsep+1 : pathname;
}

int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

int16_t concat_8(int8_t a, int8_t b)
{

    return a << 4 | (b & 0x0f);
}

int32_t concat_16(int8_t a, int8_t b, int8_t c, int8_t d)
{
    return concat_8(a, b) << 8 | (concat_8(c, d) & 0x00ff);
}

int64_t concat_32(int8_t a1, int8_t b1, int8_t c1, int8_t d1, int8_t a2, int8_t b2, int8_t c2, int8_t d2)
{
    return (int32_t)concat_16(a1, b1, c1, d1) << 16 | ((int32_t)concat_16(a2, b2, c2, d2) & 0x0000ffff);
}

int32_t readData(FILE* file, int len, int16_t *cal_checksum);

int32_t readChecksum(FILE* file, int len);

float readFloatData(FILE* file, int len, int16_t *cal_checksum);

int16_t parseData(FILE* file, imuDataPointer result, int32_t len, int16_t *cal_checksum);

void dumpData(FILE* file, imuDataPointer result) {
    fprintf(file, "%f, %f, %f, %f, %f, %f, %f, %f, %f, \
%f, %f, %f, %f, %f, %f, \
%f, %f, %f, %f, %f, %f, \
%f, %f, %f, %f, %f, %f, \
%f, %f, %f, %f, \
%f, %f, %f, %f, %f, %f, \
%f, %f, %f, %f, %f, %f, %f, %f, %f\n",
    result->time, result->pressure, result->pressure_temp, 
    result->accx1, result->accy1, result->accz1, result->gyrox1, result->gyroy1, result->gyroz1,
    result->accx2, result->accy2, result->accz2, result->gyrox2, result->gyroy2, result->gyroz2, 
    result->accx3, result->accy3, result->accz3, result->gyrox3, result->gyroy3, result->gyroz3, 
    result->accx4, result->accy4, result->accz4, result->gyrox4, result->gyroy4, result->gyroz4, 
    result->temp1, result->temp2, result->temp3, result->temp4, 
    result->magx1, result->magy1, result->magz1, result->magx2, result->magy2, result->magz2, 
    result->magx3, result->magy3, result->magz3, result->magx4, result->magy4, result->magz4, 
    result->fumagx, result->fumagy, result->fumagz);
}

#endif // mimu22BL_parser_mimu_parser_H_