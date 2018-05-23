/* FINAL CODE
 * File:   state_of_machine.c
 * Author: philip
 * version 16.4.18.1
 * Created on 16 April 2018, 14:44
 */
#include <xc.h>
#include "config.h"
#include "clear_oled.h"
#include "write_character.h"
#include "bar_graph.h"
#include "get_digit.h"
#include "split_digits.h"
#include "mute.h"
#include "setup_vol_scrn.h"
#include "input.h"
#include "select_ip.h"
#include "state_of_machine.h"



void state_of_machine(int *c_state) // *c_state is initially == VOL state
{ 
    
    switch (*c_state)
    {
        case VOL:
            if (SWIP == HI)
        {
           time_out = 0;
                T1CONbits.TMR1ON = 0; 
               // bar_graph();
                split_digits();
              /*  if(count >=0 && count <95)
                {
                    write_character(&minus[0], 0x0f,0xb3);
                }*/
            /*else
                {
                    write_character(&space[0],0x0f,0xb3);
                }   
            get_digit(tens, 0x1f);
            get_digit(units, 0x2f); 
            write_character(&d[0],0x3f,0xb3);
            write_character(&B[0],0x4f,0xb3); */
            break;
        }
    }
        
}
           

