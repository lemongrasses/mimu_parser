#include "mimu_parser.h"

int32_t readData(FILE* file, int len, int16_t *cal_checksum) {
    int count = 0;
    char readbuff;
    char *data = (char*)malloc(sizeof(char)*len);
    int8_t *concatdata = (int8_t*) malloc(sizeof(int8_t)*len);
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
    for(int i=0;i<len;i++) {
        concatdata[i] = hex2int(data[i]);
    }
    for(int i=0;i<len;i+=2) {
        int16_t temp = concat_8(concatdata[i],concatdata[i+1]);
        *cal_checksum += temp & 0xFF;
    }
    free(data);
    free(concatdata);
    data = NULL;
    return hexdata;
}

int32_t readChecksum(FILE* file, int len) {
    int count = 0;
    char readbuff;
    char *data = (char*)malloc(sizeof(char)*len);
    int8_t *concatdata = (int8_t*) malloc(sizeof(int8_t)*len);
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
    free(data);
    free(concatdata);
    data = NULL;
    return hexdata;
}

float readFloatData(FILE* file, int len, int16_t *cal_checksum) {
    int count = 0;
    char readbuff;
    char *data = (char*)malloc(sizeof(char)*len);
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
    for(int i=0;i<len;i+=2) {
        int16_t temp = concat_8(concatdata[i],concatdata[i+1]);
        *cal_checksum += temp & 0xFF;
    }
    *((int32_t *) (&concatresult)) = concat_32(concatdata[0], concatdata[1], concatdata[2], concatdata[3], concatdata[4], concatdata[5], concatdata[6], concatdata[7]);
    floatdata = (*((float *) (&concatresult)));
    memset(data,0,len);
    free(data);
    data = NULL;
    return floatdata;
}

int16_t parseData(FILE* file, imuDataPointer result, int32_t len, int16_t *cal_checksum) {
    result->time = (float)((uint32_t)readData(file,8,cal_checksum)) / (pow(16,6));
    result->pressure = (float)((int32_t)readData(file,8,cal_checksum)) / (2 << 11);
    result->pressure_temp = (float)((int16_t)readData(file,4,cal_checksum)) / 480 + 42.5;
    result->accx1 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->accy1 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->accz1 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->gyrox1 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->gyroy1 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->gyroz1 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->accx2 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->accy2 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->accz2 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->gyrox2 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->gyroy2 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->gyroz2 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->accx3 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->accy3 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->accz3 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->gyrox3 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->gyroy3 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->gyroz3 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->accx4 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->accy4 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->accz4 = (float)((int16_t)readData(file,4,cal_checksum)) * 9.79 / (2 << 10);
    result->gyrox4 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->gyroy4 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->gyroz4 = (float)((int16_t)readData(file,4,cal_checksum)) / 16.4;
    result->temp1 = (float)((int16_t)readData(file,4,cal_checksum)) / 340 + 35;
    result->temp2 = (float)((int16_t)readData(file,4,cal_checksum)) / 340 + 35;
    result->temp3 = (float)((int16_t)readData(file,4,cal_checksum)) / 340 + 35;
    result->temp4 = (float)((int16_t)readData(file,4,cal_checksum)) / 340 + 35;
    result->magx1 = readFloatData(file,8,cal_checksum) *0.3;
    result->magy1 = readFloatData(file,8,cal_checksum) *0.3;
    result->magz1 = readFloatData(file,8,cal_checksum) *0.3;
    result->magx2 = readFloatData(file,8,cal_checksum) *0.3;
    result->magy2 = readFloatData(file,8,cal_checksum) *0.3;
    result->magz2 = readFloatData(file,8,cal_checksum) *0.3;
    result->magx3 = readFloatData(file,8,cal_checksum) *0.3;
    result->magy3 = readFloatData(file,8,cal_checksum) *0.3;
    result->magz3 = readFloatData(file,8,cal_checksum) *0.3;
    result->magx4 = readFloatData(file,8,cal_checksum) *0.3;
    result->magy4 = readFloatData(file,8,cal_checksum) *0.3;
    result->magz4 = readFloatData(file,8,cal_checksum) *0.3;
    result->fumagx = readFloatData(file,8,cal_checksum);
    result->fumagy = readFloatData(file,8,cal_checksum);
    result->fumagz = readFloatData(file,8,cal_checksum);
    result->checksum = (int16_t)readChecksum(file,4);
    return result->checksum;
}

int main(int argc, char *argv[])
{
    char *filename_fullpath = argv[1];
    char *filename = (char*) malloc(255);
    char parsed_file[255] = "parsed_";
    filename = base_name(filename_fullpath);
    strcat(parsed_file,filename);
    FILE* inputfp = fopen(filename_fullpath, "r");
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
    int16_t pack_checksum;
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
                int16_t *cal_checksum = (int16_t*) malloc(sizeof(int16_t));
                *cal_checksum = 0;
                *cal_checksum += head & 0xFF;
                num = (int16_t)readData(inputfp,4, cal_checksum);
                if(num_prev != 0 || (num-num_prev) == 1){
                    len = (int16_t)readData(inputfp,2,cal_checksum);
                    pack_checksum = parseData(inputfp,result,len,cal_checksum);
                    *cal_checksum = *cal_checksum % 65536;
                    if(pack_checksum == *cal_checksum)
                        dumpData(outputfp, result);
                }
                free(cal_checksum);
            }
            num_prev = num;
            count = 0;
        }
        
    }
    
    free(result);
    fclose(inputfp);
    fclose(outputfp);

    return 0;
}