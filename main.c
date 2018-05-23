/*
 * File:   main.c
 * Author: Phil
 *
 * Created on 04 May 2018, 21:28
 */


#include <xc.h>
#include "config.h"
#include <stdio.h>
#include <stdbool.h>

#include "main.h"
#include "init_ports.h"
#include "config_osc.h"
#include "write_command.h"
#include "config_oled.h"
#include "set_page.h"
#include "set_columns.h"
#include "write_data.h"
#include "clear_oled.h"
#include "putch.h"
#include "set_usart.h"
#include "ioc_enable.h"
#include "init_TMR1.h"
#include "init_TMR0.h"
#include "get_digit.h"
#include "write_character.h"
#include "splash_screen.h"
#include "setup_vol_scrn.h"
#include "bar_graph.h"
#include "split_digits.h"
#include "state_of_machine.h"
#include "fsm.h"

void main(void) 
{
    init_ports();       // set port directions and SPI setup
    config_osc();       // set osccon bits to generate a 4MHz internal clock
    set_usart();        // setup USART for serial comms with the PC terminal
    //init_TMR1();
    //init_TMR0();
    //ioc_enable();
    config_oled();      // oled now talking to PIC, but with garbage pixels illuminated on oled
    clear_oled();
    splash_screen();
    __delay_ms(1000);
    clear_oled();
     setup_vol_scrn();
    printf (" Hello world!\n");
    int current_state = VOL;
    count = 1;          // initial volume set to -94dB
    state_of_machine(&current_state);   // FSM for Preamp functions of VOL, MUTE, INPUT, IP_SELECT   
    while(1)
    {          
       fsm(kurrent_state);
       if(CW_Flag)
       {
           count++;
           up_down = HI;
           CW_Flag = LO;
           //printf("CW_Flag = %d, ACW_Flag = %d\n",CW_Flag, ACW_Flag);
            //printf("right\n");
           printf("count++ = %d\n", count);
       }
       else if(ACW_Flag)
       
       {
           count--;
           up_down = LO;
           ACW_Flag == LO;
           //printf("CW_Flag = %d, ACW_Flag = %d\n",CW_Flag, ACW_Flag);
           //printf("left\n");
           printf("count-- = %d\n", count);
       }
       ACW_Flag = LO;
       CW_Flag = LO;
       if (count >= COUNT_MAX)
        {
            count = COUNT_MAX;
        }
        if(count <= COUNT_MIN)
        {
            count = COUNT_MIN;
        }
       
       bar_graph();
       split_digits();
       if(count >=0 && count <95)
       {
           write_character(&minus[0], 0x0f,0xb3);
       }
       else
       {
           write_character(&space[0],0x0f,0xb3);
       }   
       get_digit(tens, 0x1f);
       get_digit(units, 0x2f); 
       write_character(&d[0],0x3f,0xb3);
       write_character(&B[0],0x4f,0xb3);
       }
    }   
    

