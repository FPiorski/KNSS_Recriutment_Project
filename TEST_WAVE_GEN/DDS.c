// avr-gcc -g -Os -mmcu=atmega328p -c DDS.c
// avr-gcc -g -mmcu=atmega328p -o DDS.elf DDS.o
// avr-objcopy -j .text -j .data -O ihex DDS.elf DDS.hex

#define F_CPU 16000000UL
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>

const uint8_t tab[256] = {85,
                          86,
                          88,
                          89,
                          90,
                          91,
                          93,
                          94,
                          95,
                          96,
                          98,
                          99,
                          100,
                          101,
                          103,
                          104,
                          105,
                          106,
                          107,
                          108,
                          110,
                          111,
                          112,
                          113,
                          114,
                          115,
                          116,
                          117,
                          118,
                          119,
                          120,
                          121,
                          122,
                          123,
                          124,
                          124,
                          125,
                          126,
                          127,
                          128,
                          128,
                          129,
                          130,
                          130,
                          131,
                          131,
                          132,
                          133,
                          133,
                          134,
                          134,
                          134,
                          135,
                          135,
                          135,
                          136,
                          136,
                          136,
                          136,
                          137,
                          137,
                          137,
                          137,
                          137,
                          137,
                          137,
                          137,
                          137,
                          137,
                          137,
                          136,
                          136,
                          136,
                          136,
                          135,
                          135,
                          135,
                          134,
                          134,
                          134,
                          133,
                          133,
                          132,
                          131,
                          131,
                          130,
                          130,
                          129,
                          128,
                          128,
                          127,
                          126,
                          125,
                          124,
                          124,
                          123,
                          122,
                          121,
                          120,
                          119,
                          118,
                          117,
                          116,
                          115,
                          114,
                          113,
                          112,
                          111,
                          110,
                          108,
                          107,
                          106,
                          105,
                          104,
                          103,
                          101,
                          100,
                          99,
                          98,
                          96,
                          95,
                          94,
                          93,
                          91,
                          90,
                          89,
                          88,
                          86,
                          85,
                          84,
                          82,
                          81,
                          80,
                          79,
                          77,
                          76,
                          75,
                          74,
                          72,
                          71,
                          70,
                          69,
                          67,
                          66,
                          65,
                          64,
                          63,
                          62,
                          60,
                          59,
                          58,
                          57,
                          56,
                          55,
                          54,
                          53,
                          52,
                          51,
                          50,
                          49,
                          48,
                          47,
                          46,
                          46,
                          45,
                          44,
                          43,
                          42,
                          42,
                          41,
                          40,
                          40,
                          39,
                          39,
                          38,
                          37,
                          37,
                          36,
                          36,
                          36,
                          35,
                          35,
                          35,
                          34,
                          34,
                          34,
                          34,
                          33,
                          33,
                          33,
                          33,
                          33,
                          33,
                          33,
                          33,
                          33,
                          33,
                          33,
                          34,
                          34,
                          34,
                          34,
                          35,
                          35,
                          35,
                          36,
                          36,
                          36,
                          37,
                          37,
                          38,
                          39,
                          39,
                          40,
                          40,
                          41,
                          42,
                          42,
                          43,
                          44,
                          45,
                          46,
                          46,
                          47,
                          48,
                          49,
                          50,
                          51,
                          52,
                          53,
                          54,
                          55,
                          56,
                          57,
                          58,
                          59,
                          60,
                          62,
                          63,
                          64,
                          65,
                          66,
                          67,
                          69,
                          70,
                          71,
                          72,
                          74,
                          75,
                          76,
                          77,
                          79,
                          80,
                          81,
                          82,
                          84};

int main(void)
{
    uint8_t phase = 0;
    DDRD = 0xFF;
    while (1) {
        PORTD = tab[phase];
        phase++;
        _delay_us(4);
    }
}
