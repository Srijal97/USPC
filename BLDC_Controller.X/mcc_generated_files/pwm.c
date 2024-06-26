/**
  PWM Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    pwm.c

  @Summary
    This is the generated driver implementation file for the PWM driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for PWM.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.95-b-SNAPSHOT
        Device            :  dsPIC33EP64MC506      
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.36
        MPLAB 	          :  MPLAB X v5.10
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "pwm.h"

/**
  Section: Driver Interface
*/




void PWM_Initialize (void)
{
    // PCLKDIV 1; 
    PTCON2 = 0x06;
    // PTPER 0; 
    PTPER = 148;
    // SEVTCMP 0; 
    SEVTCMP = 0x00;
    // MDC 0; 
    MDC = 0x0000;
    // CHOPCLK 0; CHPCLKEN disabled; 
    CHOP = 0x000; //0x8049;
    // PWMKEY 0; 
    PWMKEY = 0x00;
    // MDCS Primary; FLTIEN disabled; CAM Center Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Primary; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON1 = 0x0000;
    // MDCS Primary; FLTIEN disabled; CAM Center Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Primary; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON2 = 0x0000;
    // MDCS Primary; FLTIEN disabled; CAM Edge Aligned; DTC Positive dead time for all Output modes; TRGIEN disabled; XPRES disabled; ITB Master; IUE disabled; CLIEN disabled; MTBS disabled; DTCP disabled; 
    PWMCON3 = 0x0000;
    
    //FLTDAT PWM1L Low, PWM1H Low; SWAP disabled; OVRENH disabled; PENL enabled; PMOD Complementary Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM1L Low, PWM1H Low; OVRDAT PWM1L Low, PWM1H Low; POLH disabled; 
    __builtin_write_PWMSFR(&IOCON1, 0xF300, &PWMKEY);
    //FLTDAT PWM2L Low, PWM2H Low; SWAP disabled; OVRENH disabled; PENL enabled; PMOD Complementary Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH enabled; CLDAT PWM2L Low, PWM2H Low; OVRDAT PWM2L Low, PWM2H Low; POLH disabled; 
    __builtin_write_PWMSFR(&IOCON2, 0xF300, &PWMKEY);
    //FLTDAT PWM3L Low, PWM3H Low; SWAP disabled; OVRENH disabled; PENL disabled; PMOD Complementary Output Mode; OVRENL disabled; OSYNC disabled; POLL disabled; PENH disabled; CLDAT PWM3L Low, PWM3H Low; OVRDAT PWM3L Low, PWM3H Low; POLH disabled; 
    __builtin_write_PWMSFR(&IOCON3, 0xF300, &PWMKEY);
    
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM1H, PWM1L pins to FLTDAT values- Latched; FLTSRC FLT1; 
    __builtin_write_PWMSFR(&FCLCON1, 0x03, &PWMKEY);
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD PWM2H, PWM2L pins to FLTDAT values- Latched; FLTSRC FLT32; 
    __builtin_write_PWMSFR(&FCLCON2, 0x03, &PWMKEY);
    //FLTPOL disabled; CLPOL disabled; CLSRC FLT1; CLMOD disabled; FLTMOD Fault input is disabled; FLTSRC FLT1; 
    __builtin_write_PWMSFR(&FCLCON3, 0x03, &PWMKEY);
    
    // PDC1 1234; 
    PDC1 = 74;
    // PDC2 1800; 
    PDC2 = 74;
    // PDC3 0; 
    PDC3 = 74;
    // PHASE1 2400; 
    PHASE1 = 0;
    // PHASE2 2400; 
    PHASE2 = 0;
    // PHASE3 0; 
    PHASE3 = 0;
    
    // DTR1 80; 
    DTR1 = 5;  // DTR Value = 5 then dead time = 2us
    // DTR2 80; 
    DTR2 = 5;
    // DTR3 0; 
    DTR3 = 5;
    // ALTDTR1 80; 
    ALTDTR1 = 5;
    // ALTDTR2 80; 
    ALTDTR2 = 5;
    // ALTDTR3 0; 
    ALTDTR3 = 5;
    // TRGCMP 0; 
    TRIG1 = 0x00;
    // TRGCMP 0; 
    TRIG2 = 0x00;
    // TRGCMP 0; 
    TRIG3 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON1 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON2 = 0x00;
    // TRGDIV 1; TRGSTRT 0; 
    TRGCON3 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON1 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON2 = 0x00;
    // BPLL disabled; BPHH disabled; BPLH disabled; BCH disabled; FLTLEBEN disabled; PLR disabled; CLLEBEN disabled; BCL disabled; PLF disabled; PHR disabled; BPHL disabled; PHF disabled; 
    LEBCON3 = 0x00;
    // LEB 0; 
    LEBDLY1 = 0x00;
    // LEB 0; 
    LEBDLY2 = 0x00;
    // LEB 0; 
    LEBDLY3 = 0x00;

    AUXCON1 = 0x0000;

    AUXCON2 = 0x0000;

    AUXCON3 = 0x0000;
    

    // SYNCOEN disabled; SEIEN disabled; SESTAT disabled; SEVTPS 1; SYNCSRC SYNCI1; SYNCEN disabled; PTSIDL disabled; PTEN enabled; EIPU disabled; SYNCPOL disabled; 
    PTCON = 0x8000;
}

void __attribute__ ((weak)) PWM_SpecialEvent_CallBack(void)
{
    // Add your custom callback code here
}

void PWM_SpecialEvent_Tasks ( void )
{
	if(IFS3bits.PSEMIF)
	{
		// PWM SpecialEvent callback function 
		PWM_SpecialEvent_CallBack();
		
		// clear the PWM SpecialEvent interrupt flag
		IFS3bits.PSEMIF = 0;
	}
}

void __attribute__ ((weak)) PWM_Generator1_CallBack(void)
{
    // Add your custom callback code here
}

void PWM_Generator1_Tasks ( void )
{
	if(IFS3bits.PSEMIF)
	{
		// PWM Generator1 callback function 
		PWM_Generator1_CallBack();
		
		// clear the PWM Generator1 interrupt flag
		IFS5bits.PWM1IF = 0;
	}
}
void __attribute__ ((weak)) PWM_Generator2_CallBack(void)
{
    // Add your custom callback code here
}

void PWM_Generator2_Tasks ( void )
{
	if(IFS3bits.PSEMIF)
	{
		// PWM Generator2 callback function 
		PWM_Generator2_CallBack();
		
		// clear the PWM Generator2 interrupt flag
		IFS5bits.PWM2IF = 0;
	}
}
void __attribute__ ((weak)) PWM_Generator3_CallBack(void)
{
    // Add your custom callback code here
}

void PWM_Generator3_Tasks ( void )
{
	if(IFS3bits.PSEMIF)
	{
		// PWM Generator3 callback function 
		PWM_Generator3_CallBack();
		
		// clear the PWM Generator3 interrupt flag
		IFS6bits.PWM3IF = 0;
	}
}

/**
 End of File
*/
