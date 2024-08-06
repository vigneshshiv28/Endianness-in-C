#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


uint8_t* integerToByteArrayInLE(uint32_t num)
{
    uint8_t *arr = (uint8_t*)malloc(sizeof(uint8_t) * 4);
    for(int i=0;i < 4;i++)
    {
        uint8_t b = num & 0x000000FF;
        arr[i] = b;
        num >>= 8;
    }
    return arr;
}

uint8_t* integerToByteArrayInBE(uint32_t num)
{
    uint8_t *arr = (uint8_t*)malloc(sizeof(uint8_t) * 4);
    for(int i=3;i >= 0;i--)
    {
        uint8_t b = num & 0x000000FF;
        arr[i] = b;
        num >>= 8;
    }
    return arr;
}

uint32_t bigEndianRead(uint8_t arr[])
{
    uint32_t num = 0;
    for(int i=0;i < 4;i++)
    {
        num = num | arr[i]<<(8*(4-i-1)); 
    }
    return num;
}

uint32_t littleEndianRead(uint8_t arr[])
{
    uint32_t num = 0;
    for(int i=0;i < 4;i++)
    {
        num = num | ((uint32_t)arr[i]<<(8*i)); 
    }
    return num;
}

int main()
{
    uint32_t num = 0x4035892F;
    
    printf("Data: %d\n",num);
    uint8_t *leWrite = integerToByteArrayInLE(num);
    
    printf("Data Written in LE and Read in LE: %d\n",littleEndianRead(leWrite));
    printf("Data Written in LE and Read in BE: %d\n",bigEndianRead(leWrite));

    uint8_t *beWrite = integerToByteArrayInBE(num);

    printf("Data Written in BE and Read in LE: %d\n",littleEndianRead(beWrite));
    printf("Data Written in BE and Read in BE: %d\n",bigEndianRead(beWrite));

    return 0;
}