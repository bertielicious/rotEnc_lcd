/*
 * File:   mute.c
 * Author: philip
 *
 * Created on 26 February 2018, 18:52
 */


#include <xc.h>
#include "config.h"
#include "write_character.h"


void mute(void) 
{
    write_character(&m[0],0x1f,0xb3);  //do this
    write_character(&u[0],0x2f, 0xb3); 
    write_character(&t[0],0x3f, 0xb3);
    write_character(&e[0],0x4f,0xb3);  
    return;
}
