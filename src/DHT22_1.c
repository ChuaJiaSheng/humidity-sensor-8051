#include "SM59R16A5.h"

unsigned char avalue[5]; // Array to store values read from the sensor
unsigned int hex_temp, hex_hum; // Variables to store raw temperature and humidity values
unsigned int x = 0, y = 0; // Timer counters
extern unsigned int dec_hum, dec_temp; // External variables for decimal humidity and temperature
extern unsigned long adc_hum; // External variables for decimal humidity and temperature

sbit dht_data = P3^0; // Connect DHT22 data pin to P30

void setup(void)
{
    // Timer 0 and 1 initialisation for mode 0 (13bit timer)
    TH0 = (8192 - 1850) / 32; // Set Timer 0 high byte for 1850 count (ms)
    TL0 = (8192 - 1850) % 32; // Set Timer 0 low byte for 1850 count (ms)
    TH1 = (8192 - 14) / 32; // Set Timer 1 high byte for 14 count (us)
    TL1 = (8192 - 14) % 32; // Set Timer 1 low byte for 14 count (us)
    TMOD = 0X00; // Timer/Counter 0 in mode 0

    ET0 = 1; // Enable Timer 0 interrupts
    ET1 = 1; // Enable Timer 1 interrupts
    EA = 1; // Enable global interrupts

    // Initialisation for ADC
    ADCC1 = 0x01;
    ADCC2 = 0x00;
}

void timer0_ms(void) interrupt 1 using 2
{
    x--;
    TH0 = (8192 - 1850) / 32;
    TL0 = (8192 - 1850) % 32;
    // Toggle P0_0 to generate a square wave for observing the timer period
    P0_0 ^= 1;
}

void timer1_us(void) interrupt 3
{
    y--;
    TH1 = (8192 - 14) / 32;
    TL1 = (8192 - 14) % 32;
    // Toggle P0_0 to generate a square wave for observing the timer period
    P0_0 ^= 1;
}

void timer_ms(unsigned int ms)
{
    x = ms;
    TR0 = 1; // Start Timer 0
    while (x); // Wait for x to reach 0
    TR0 = 0; // Stop Timer 0
}

void timer_us(unsigned int us) // 10us
{
    y = us;
    TR1 = 1; // Start Timer 1
    while (y); // Wait for y to reach 0
    TR1 = 0; // Stop Timer 1
}

void Read_value(void)
{
    unsigned char a, b = 0, mask;

    dht_data = 0; // Pull down for at least 20ms
    timer_ms(5); // Wait for 5ms
    dht_data = 1; // Pull up for at least 20us
    timer_us(3); // Wait for 30us
    while (!dht_data); // Wait for low

    while (dht_data); // Wait for high
    while (b < 5) {
        mask = 0x80;
        for (a = 0; a < 8; a++) {
            while (!dht_data); // Wait for low
            timer_us(2);
            timer_us(2);
            if (dht_data == 0) {
                avalue[b] &= (~mask); // Clear bit
            } else {
                avalue[b] |= mask; // Set bit
            }
            mask >>= 1; // Shift mask right
            while (dht_data); // Wait for high
        }
        b++;
    }
}

void readht(void)
{
    Read_value();
    hex_hum = avalue[0] * 256 + avalue[1]; // Convert humidity to hex
    dec_hum = hex_hum * 10; // Convert to decimal
    hex_temp = (avalue[2] & 0x7f) * 256 + avalue[3]; // Convert temperature to hex, ignoring sign bit
    dec_temp = hex_temp * 10; // Convert to decimal
}

void adcc(void)
{
    // Setting: 5V DC 4.7k ohm
    float v, h, r;
    unsigned int adcH, adcL, adcV;
    float a = 5. / 1023.;
    float b = 1. / (10. * 10. * 10. * 10. * 10. * 10. * 10.);
    float stdR = 89.400;

    ADCC2 |= 0x80; // Start ADC convertion
    while (!IRCON && 0x04);
    adcH = ADCDH;
    adcL = ADCDL;
    adcV = adcH * 4 + adcL;

    v = a * adcV; // Calculate voltage at the sensor
    r = ((v * stdR) / (5. - v)); // Calculate the resistance
    h = (0.0033 * (r * r)) - (0.827 * r) + 52.493; // Calculate huminity
    adc_hum = (h * 1000);
}
