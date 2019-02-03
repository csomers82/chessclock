#ifndef __BASIC_H
#define __BASIC_H
#include "stm32f0xx_hal.h"

// basic debug lcd commands
#define CURMOV  0xFE
#define LCDON   0x0F
#define TWOLINE 0x38
#define LCDCLR  0x01
#define LINE1   0x80
#define LINE2   0xC0

// simple utilities
#define BIT0             (1)
#define BIT1             (2)
#define BIT2             (4)
#define BIT3             (8)
#define BIT4             (0x10)
#define BIT5             (0x20)
#define BIT6             (0x40)
#define BIT7             (0x80)
#define BIT8             (0x100)
#define BIT9             (0x200)
#define BIT10            (0x400)
#define BIT11            (0x800)
#define BIT12            (0x1000)
#define BIT13            (0x2000)
#define BIT14            (0x4000)
#define BIT15            (0x8000)

// basic debug lcd function
void shiftout(unsigned char x);
//void lcdwait();
void spinwaiting(char loops);
void itoa_intoBuffer(int32_t in);
void blink(uint16_t t);
void wink(uint16_t t);

#endif//__BASIC_H