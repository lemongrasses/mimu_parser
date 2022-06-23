#include "mimu_parser.h"

int32_t readData(FILE* file, int len) {
    int count = 0;
    char readbuff;
    char data[len];
    int hexdata = 0;
    while(count != len) 
    {
        fread(&readbuff, 1, 1, file);
        if(readbuff == 32 || readbuff == 10 || readbuff == 13) {
            continue;
        }
        else {
            data[count] = readbuff;
            count++;
        }
    }
    hexdata = (int32_t)strtol(data, NULL, 16);
    memset(data,0,len);
    return hexdata;
}

float readFloatData(FILE* file, int len) {
    int count = 0;
    char readbuff;
    char data[len];
    int8_t concatdata[8];
    void  *concatresult;
    float floatdata;
    while(count != len) 
    {
        fread(&readbuff, 1, 1, file);
        if(readbuff == 32 || readbuff == 10 || readbuff == 13) {
            continue;
        }
        else {
            data[count] = readbuff;
            count++;
        }
    }
    for(int i=0;i<8;i++) {
        concatdata[i] = hex2int(data[i]);
    }
    *((int32_t *) (&concatresult)) = concat_32(concatdata[0], concatdata[1], concatdata[2], concatdata[3], concatdata[4], concatdata[5], concatdata[6], concatdata[7]);
    floatdata = (*((float *) (&concatresult)));
    memset(data,0,len);
    return floatdata;
}

void parseData(FILE* file, imuDataPointer result, int32_t len) {
    result->time = (float)((uint32_t)readData(file,8)) / (pow(16,6));
    result->pressure = (float)((int32_t)readData(file,8)) / (2 << 11);
    result->pressure_temp = (float)((int16_t)readData(file,4)) / 480 + 42.5;
    result->accx1 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->accy1 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->accz1 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->gyrox1 = (float)((int16_t)readData(file,4)) / 16.4;
    result->gyroy1 = (float)((int16_t)readData(file,4)) / 16.4;
    result->gyroz1 = (float)((int16_t)readData(file,4)) / 16.4;
    result->accx2 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->accy2 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->accz2 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->gyrox2 = (float)((int16_t)readData(file,4)) / 16.4;
    result->gyroy2 = (float)((int16_t)readData(file,4)) / 16.4;
    result->gyroz2 = (float)((int16_t)readData(file,4)) / 16.4;
    result->accx3 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->accy3 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->accz3 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->gyrox3 = (float)((int16_t)readData(file,4)) / 16.4;
    result->gyroy3 = (float)((int16_t)readData(file,4)) / 16.4;
    result->gyroz3 = (float)((int16_t)readData(file,4)) / 16.4;
    result->accx4 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->accy4 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->accz4 = (float)((int16_t)readData(file,4)) * 9.79 / (2 << 10);
    result->gyrox4 = (float)((int16_t)readData(file,4)) / 16.4;
    result->gyroy4 = (float)((int16_t)readData(file,4)) / 16.4;
    result->gyroz4 = (float)((int16_t)readData(file,4)) / 16.4;
    result->temp1 = (float)((int16_t)readData(file,4)) / 340 + 35;
    result->temp2 = (float)((int16_t)readData(file,4)) / 340 + 35;
    result->temp3 = (float)((int16_t)readData(file,4)) / 340 + 35;
    result->temp4 = (float)((int16_t)readData(file,4)) / 340 + 35;
    result->magx1 = readFloatData(file,8) *0.3;
    result->magy1 = readFloatData(file,8) *0.3;
    result->magz1 = readFloatData(file,8) *0.3;
    result->magx2 = readFloatData(file,8) *0.3;
    result->magy2 = readFloatData(file,8) *0.3;
    result->magz2 = readFloatData(file,8) *0.3;
    result->magx3 = readFloatData(file,8) *0.3;
    result->magy3 = readFloatData(file,8) *0.3;
    result->magz3 = readFloatData(file,8) *0.3;
    result->magx4 = readFloatData(file,8) *0.3;
    result->magy4 = readFloatData(file,8) *0.3;
    result->magz4 = readFloatData(file,8) *0.3;
    result->fumagx = readFloatData(file,8);
    result->fumagy = readFloatData(file,8);
    result->fumagz = readFloatData(file,8);
    result->checksum = (int16_t)readData(file,4);
}

int main(int argc, char *argv[])
{
    char *filename = argv[1];
    char parsed_file[255] = "parsed_";
    strcat(parsed_file,filename);
    FILE* inputfp = fopen(filename, "r");
    FILE* outputfp = fopen(parsed_file, "w");
    char readbuff;
    char data[2];
    char num_data[4];
    imuDataPointer result = (imuDataPointer)malloc(sizeof(imuData));
    int16_t head;
    int count = 0;
    int16_t num;
    int16_t num_prev = 0;
    int16_t len;
    while(!feof(inputfp))
    {
        fread(&readbuff,1,1,inputfp);
        if(readbuff == 32 || readbuff == 10 || readbuff == 13) {
            count = 0;
        }
        else {
            data[count] = readbuff;
            count++;
        }
        if(count == 2) {
            head = (int16_t)strtol(data, NULL, 16); // 轉hex
            if(head == 0xAA) {
                num = (int16_t)readData(inputfp,4);
            }
            if(num_prev != 0 && (num-num_prev) == 1){
                len = (int16_t)readData(inputfp,2);
                parseData(inputfp,result,len);
                
                dumpData(outputfp, result);
            }
            num_prev = num;
            count = 0;
        }
    }
    fclose(inputfp);
    fclose(outputfp);
}