/*
 * File:   interrupt isr.c
 * Author: philip
 *
 * Created on 30 March 2018, 20:08
 */
#include <xc.h>
#include "config.h"
#include <stdio.h>
#include "debounce.h"
#include "fsm.h"
#include "interrupt isr.h"


void interrupt isr(void) 
{
    unsigned char clear_port_a = 0;
    
    if(PIR1bits.TMR1IF == 1)
    {
        
        TMR1H = 0x00;                       // 85ms interrupt
        TMR1L = 0x00;
        time_out++;                         // at least 85ms has expired
        //printf(" time_out = %d\n", time_out);
    }
    PIR1bits.TMR1IF = 0;
    /************************************************************************/
    if(INTCONbits.TMR0IF == 1)
    {
        
        TMR0 = 0x00;            // 1ms interrupt tick
    }
    if(IOCAFbits.IOCAF1 == 1)
    {
        
        
        fsm(kurrent_state);                 // FSM for rotary encoder detecting debounced CW and ACW rotations to provide volume control
        DIAGNOSTIC_LED =  CW_Flag;      //diagnostic led  pin 13
        if(CW_Flag == HI && ACW_Flag == LO)       // clockwise movement of the knob
        { 
            count++;
            up_down = HI;
            CW_Flag == LO;
        }
        
        else if (ACW_Flag == HI && CW_Flag == LO) // anti-clockwise movement of the knob
        {
            count--;
            up_down = LO;
            ACW_Flag == LO;
        }
        
     
    if (count >= COUNT_MAX)
    {
        count = COUNT_MAX;
    }
    if(count <= COUNT_MIN)
    {
        count = COUNT_MIN;
    }
        
    
        
    
    
    
  /*  if(IOCAFbits.IOCAF1 == 1)
    {
        if(DT == HI)       // clockwise movement of the knob
        { 
            count++;
            up_down = HI;
        }
        else if (DT == LO) // anti-clockwise movement of the knob
        {
            count--;
            up_down = LO;
        }
     
    if (count >= COUNT_MAX)
    {
        count = COUNT_MAX;
    }
    if(count <= COUNT_MIN)
    {
        count = COUNT_MIN;
    }
        if((previous_count != count) && (count != COUNT_MAX) && (count != COUNT_MIN))
        {
            printf("volume position = %d\n", count);  // display latest value of count via serial monitor
        }
        
        previous_count = count;
        printf("DT = %d, CLK = %d\n", DT, CLK);  // display latest value of DT and CLK via serial monitor*/
    }
    clear_port_a = PORTA;
    INTCONbits.IOCIF == 0;
    IOCAFbits.IOCAF1 = 0;
    INTCONbits.TMR0IF = 0;
}