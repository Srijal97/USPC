//******************************************************************************
// Code developed for SPIT Mumbai
// This file includes all ISR functions
//******************************************************************************
#include <p33EP64MC506.h>

#include "ISRs.h"
#include "mcc_generated_files/pin_manager.h"
#include "motorFun.h"
 

void enableInterrupts(void)
{
    /* Enable level 1-7 interrupts */
    /* No restoring of previous CPU IPL state performed here */
    INTCON2bits.GIE = 1;
    return;
}

void disableInterrupts(void)
{
    /* Disable level 1-7 interrupts */
    /* No saving of current CPU IPL setting performed here */
    INTCON2bits.GIE = 0;
    return;
}

void initInterrupts(void)
{

    /* Enable CN interrupts */
    IEC1bits.CNIE = 1;
    
    IFS1bits.CNIF = 0; // Reset CN interrupt
    
    return;

    
}

void __attribute__((__interrupt__,no_auto_psv)) _CNInterrupt(void)
{
/* Insert ISR Code Here*/
    
    if(!motor_started) {
        motor_started = true;
    }
    
    volatile char sensor_vector = (IO_RB3_U_ZCD_GetValue() << 2) 
                        + (IO_RC1_V_ZCD_GetValue() << 1) 
                        + (IO_RA11_W_ZCD_GetValue());
    
    //sensor_vector = 6;
    write_switching_vector(sensor_vector, 1);
    

/* Clear CN interrupt */
    IFS1bits.CNIF = 0;
}