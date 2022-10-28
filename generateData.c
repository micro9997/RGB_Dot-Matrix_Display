
#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t data[8][26] = {
{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00},
{0x0E, 0x1E, 0x0E, 0X1E, 0x1F, 0x1F, 0x0E, 0x11, 0x0E, 0x0F, 0X11, 0X10, 0X11, 0X11, 0X0E, 0X1E, 0X0E, 0X1E, 0X0E, 0X1F, 0X11, 0X11, 0X11, 0X11, 0X11, 0X1F},
{0x11, 0x11, 0x11, 0x11, 0x10, 0x10, 0x11, 0x11, 0x04, 0x02, 0X12, 0X10, 0X1B, 0X19, 0X11, 0X11, 0X11, 0X11, 0X11, 0X04, 0X11, 0X11, 0X11, 0X11, 0X11, 0X01},
{0x11, 0x11, 0x10, 0x11, 0x10, 0x10, 0x10, 0x11, 0x04, 0x02, 0X14, 0X10, 0X15, 0X15, 0X11, 0X11, 0X11, 0X11, 0X10, 0X04, 0X11, 0X11, 0X11, 0X0A, 0X11, 0X02},
{0x11, 0x1E, 0x10, 0x11, 0x1E, 0x1F, 0x10, 0x1F, 0x04, 0x02, 0X18, 0X10, 0X15, 0X13, 0X11, 0X1E, 0X11, 0X1E, 0X1E, 0X04, 0X11, 0X11, 0X11, 0X04, 0X0E, 0X04},
{0x1F, 0x11, 0x10, 0x11, 0x10, 0x10, 0x13, 0x11, 0x04, 0x02, 0X14, 0X10, 0X11, 0X11, 0X11, 0X10, 0X15, 0X14, 0X01, 0X04, 0X11, 0X11, 0X15, 0X0A, 0X04, 0X08},
{0x11, 0x11, 0x11, 0x11, 0x10, 0x10, 0x11, 0x11, 0x04, 0x12, 0X12, 0X10, 0X11, 0X11, 0X11, 0X10, 0X13, 0X12, 0X11, 0X04, 0X11, 0X0A, 0X15, 0X11, 0X04, 0X10},
{0x11, 0x1E, 0x0E, 0x1E, 0x1F, 0x10, 0x0E, 0x11, 0x0E, 0x0C, 0X11, 0X1F, 0X11, 0X11, 0X0E, 0X10, 0X0F, 0X11, 0X0E, 0X04, 0X0E, 0X04, 0X0A, 0X11, 0X04, 0X1F}};

void prepareData(FILE *fptr, uint8_t data, uint8_t index, uint8_t lastIndex) {
    static uint8_t temData = 0;
    static uint8_t temDataCount = 0;
    if(index == 0) {
        fprintf(fptr, "{0x00, ");
    }
    
    for(int i = 4; i >= 0; i--) {
        uint8_t mask = (1 << i);
        if((data & mask) != 0) {
            temData = temData << 1;
            temData = temData | 1;
            temDataCount++;
            if(temDataCount == 8) {
                fprintf(fptr, "0x%X, ", temData);
                temDataCount = 0;
            }
        } else {
            temData = temData << 1;
            temDataCount++;
            if(temDataCount == 8) {
                fprintf(fptr, "0x%X, ", temData);
                temDataCount = 0;
            }
        }
    }
    temData = temData << 1;
    temDataCount++;
    if(temDataCount == 8) {
        fprintf(fptr, "0x%X, ", temData);
        temDataCount = 0;
    }

    if(index == lastIndex) {
        if(temDataCount != 0) {
            temData = temData << (8 - temDataCount);
            temDataCount = 0;
            fprintf(fptr, "0x%X, ", temData);
        }
        fprintf(fptr, "0x00},\n");
    }
}

int main() {
    char ch[25];
    uint32_t moveTime = 250;
    printf("Enter the data: ");
    scanf("%s", ch);
    printf("Enter the time (ms) to move: ");
    scanf("%d", &moveTime);

    uint8_t dataSize = ((16 + (5 * strlen(ch)) + (strlen(ch) - 1)) / 8);
    if(((16 + (5 * strlen(ch)) + (strlen(ch) - 1)) % 8) != 0) {
        dataSize++;
    }

    uint16_t dataLen = 16 + (5 * strlen(ch)) + (strlen(ch) - 1);

    FILE *fptr = fopen("data.h", "w");
    if(fptr == NULL) {
        return -1;
    }

    fprintf(fptr, "uint8_t data[8][%d] = {\n", dataSize);

    for(int j = 0; j < 8; j++) {
        uint8_t i = 0;
        while(ch[i] != '\0') {
            if(ch[i] >= 65 && ch[i] <= 90) {
                prepareData(fptr, data[j][ch[i] - 65], i, (strlen(ch) - 1));
            } else if(ch[i] >= 97 && ch[i] <= 122) {
                prepareData(fptr, data[j][ch[i] - 97], i, (strlen(ch) - 1));
            } else {
                printf("Invalid input\n");
                printf("Maybe this feature can be improved in the next version\n");
                return 0;
            }
            i++;
        }
    }

    fputs("};\n", fptr);
    fprintf(fptr, "uint8_t dataSize = %d;\n", dataSize);
    fprintf(fptr, "uint16_t dataLen = %d;\n", dataLen);
    fprintf(fptr, "uint32_t moveTime = %d;", moveTime);

    fclose(fptr);

    return 0;
}
