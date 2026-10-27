#include "dht22_1.h"
#include "SM59R16A5.h"
#include "IIC LCD.h"

unsigned long hum;
unsigned int temp;
unsigned char i = 0;
unsigned int sec = 0;
unsigned int min = 0;
unsigned int dec_hum, dec_temp;
unsigned long adc_hum, error;

main()
{
    setup();
    lcd_initial();
    lcd_clr();
    lcd_write_command(HIDE_CSR);

    while (1) {
        timer_ms(1000);
        readht();
        adcc();
        error = dec_hum - adc_hum;
        if (error < 0) {
            error = -error;
        }
        if (error >= 10) {
            hum = dec_hum;
        } else {
            hum = adc_hum;
        }
        lcd_set_cursor(0x02);
        lcd_print_string("RH:");
        lcd_print_int_2p2(hum);
        lcd_print_string("%");
        lcd_set_cursor(0x10);
        lcd_print_string("Temp:");
        lcd_print_int_2p2(dec_temp);
        lcd_print_string("*C");

        timer_ms(2);
    }
}
