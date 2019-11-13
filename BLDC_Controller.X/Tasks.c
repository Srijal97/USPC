//******************************************************************************
// Code developed for SPIT Mumbai
// This file includes all functions related to mutliTasking kernel
//******************************************************************************


#include "Tasks.h"
#include "mcc_generated_files/pin_manager.h"
#include "BizLogic.h"
#include "MODBUS.h"


uCHAR cnt1ms  = 0;
uCHAR cnt5ms  = 0;
uCHAR cnt10ms = 0;
uCHAR cnt25ms = 0;
uCHAR cnt100ms = 0;

//******************************************************************************
// TimerCallBack 
// Input - None
// This function is the callback of timer1 and called after every 1ms duration 
//******************************************************************************
void TimerCallBack (void)  
{
    volatile uINT lclEventReg = 0;

    // Read ADC is the 100us default Task
    readAllAnalogVariables();
    
    static uINT16 u_zcd_state = 0;
    static uINT16 v_zcd_state = 0;
    static uINT16 w_zcd_state = 0;
    
    static uINT time_to_wait = 70; // wait for 70x100us = 7msec from edge detected to commutation 
    
/* Gives rising edges on input pin at approx 500us delay with timer callback every 100us
    u_zcd_state = (0xFFC0 | !IO_RB3_U_ZCD_GetValue()) | (u_zcd_state << 1);  
    if(u_zcd_state == 0xFFE0) {     
        commutation_required = true;
        IO_RD5_BLDC_LED_SetHigh();
    } else{
        IO_RD5_BLDC_LED_SetLow();
    }
    
 * Gives falling edges on input pin at approx 500us delay with timer callback every 100us
    u_zcd_state = (0xFFE0 && IO_RB3_U_ZCD_GetValue()) | (u_zcd_state << 1);  
    if(u_zcd_state == 0xFFC0) {     
        commutation_required = true;
        IO_RD5_BLDC_LED_SetHigh();
    } else{
        IO_RD5_BLDC_LED_SetLow();
    }

 * based on switch debounce logic. refer: https://www.embedded.com/electronics-blogs/break-points/4024981/My-favorite-software-debouncers
 */  
    
    
    
    
    switch(startup_sensor_vector) {
        case 1:
             // check for W_ZCD_rising --> check falling edge on pin (input is inverted)
            
            w_zcd_state = (0xFFE0 && IO_RA11_W_ZCD_GetValue()) | (w_zcd_state << 1);  
            if(w_zcd_state == 0xFFC0) {     
                commutation_required = true;
                time_to_wait = 70;
                //IO_RD5_BLDC_LED_SetHigh();
                //IO_RC9_IM_LED_SetHigh();
            } else {
                //IO_RD5_BLDC_LED_SetLow();
                //IO_RC9_IM_LED_SetLow();
            }
            
            break;

        case 2:
            // check for V_ZCD_rising  --> falling edge on pin
            v_zcd_state = (0xFFE0 && IO_RC1_V_ZCD_GetValue()) | (v_zcd_state << 1);  
            if(v_zcd_state == 0xFFC0) {     
                commutation_required = true;
                time_to_wait = 70;
                //IO_RD5_BLDC_LED_SetHigh();
                //IO_RD6_PMSM_LED_SetHigh();
            } else {
                //IO_RD5_BLDC_LED_SetLow();
                //IO_RD6_PMSM_LED_SetLow();
            }
            
            break;

        case 3:
            // check for U_ZCD_falling  --> rising edge on pin
            u_zcd_state = (0xFFC0 | !IO_RB3_U_ZCD_GetValue()) | (u_zcd_state << 1);  
            if(u_zcd_state == 0xFFE0) {     
                commutation_required = true;
                time_to_wait = 70;
                //IO_RD5_BLDC_LED_SetHigh();
                //IO_RD5_BLDC_LED_SetHigh();
            } else{
                //IO_RD5_BLDC_LED_SetLow();
                //IO_RD5_BLDC_LED_SetLow();
            }
            
            break;
        case 4:
            // check for U_ZCD_rising --> falling edge on pin
            u_zcd_state = (0xFFE0 && IO_RB3_U_ZCD_GetValue()) | (u_zcd_state << 1);  
            if(u_zcd_state == 0xFFC0) {     
                commutation_required = true;
                time_to_wait = 70;
                //IO_RD5_BLDC_LED_SetHigh();
                //IO_RD5_BLDC_LED_SetHigh();
            } else{
                //IO_RD5_BLDC_LED_SetLow();
                //IO_RD5_BLDC_LED_SetLow();
            }
            
            break;

        case 5:
            // check for V_ZCD_falling --> rising edge on pin
            v_zcd_state = (0xFFC0 | !IO_RC1_V_ZCD_GetValue()) | (v_zcd_state << 1);  
            if(v_zcd_state == 0xFFE0) {     
                commutation_required = true;
                time_to_wait = 70;
                //IO_RD5_BLDC_LED_SetHigh();
                //IO_RD6_PMSM_LED_SetHigh();
            } else {
                //IO_RD5_BLDC_LED_SetLow();
                //IO_RD6_PMSM_LED_SetLow();
            }
            
            break;

        case 6:
            // check for W_ZCD_falling --> rising edge on pin
            w_zcd_state = (0xFFC0 | !IO_RA11_W_ZCD_GetValue()) | (w_zcd_state << 1);  
            if(w_zcd_state == 0xFFE0) {     
                commutation_required = true;
                time_to_wait = 70;
                //IO_RD5_BLDC_LED_SetHigh();
                //IO_RC9_IM_LED_SetHigh();
            } else {
                //IO_RD5_BLDC_LED_SetLow();
                //IO_RC9_IM_LED_SetLow();
            }
            
            break;
    }
    
    time_to_wait--;
    
    if (commutation_required && motor_started && (time_to_wait < 1)) {
        startup_sensor_vector = next_sensor_vector[startup_sensor_vector - 1];
        write_switching_vector(startup_sensor_vector, 1);
        commutation_required = false;
        IO_RD5_BLDC_LED_SetHigh();
    } else {
        IO_RD5_BLDC_LED_SetLow();
    }
    
    
    
    if(++cnt1ms > 9)
    {
        cnt1ms = 0;
        eventRegister |= EVENT_TIMER_1ms_TASK;
    }
        
    if(++cnt10ms > 99)
    {        
        cnt10ms = 0;
        eventRegister |= EVENT_TIMER_10ms_TASK;
    }
        
    if(++cnt25ms > 249)
    {
        cnt25ms = 0;
        eventRegister |= EVENT_TIMER_25ms_TASK;
    }    
   
    lclEventReg = eventRegister;    // Must be atomic 
    
    if(lclEventReg & EVENT_MODBUS_TASK)
    {
        lclEventReg &= ~EVENT_MODBUS_TASK; // Reset the Event Bit
        //MODBUSDecodeTask();
    }
    
    if(lclEventReg & EVENT_CAN_COM_TASK)
    {
        lclEventReg &= ~EVENT_CAN_COM_TASK; // Reset the Event Bit
        //CANBUSDecodeTask();
    } 
    
    if(lclEventReg & EVENT_ETHERNATE_TASK)
    {
        lclEventReg &= ~EVENT_ETHERNATE_TASK; // Reset the Event Bit
        //EthernetDecodeTask();
    } 
    
    if(lclEventReg & EVENT_TIMER_1ms_TASK)
    {
        lclEventReg &= ~EVENT_TIMER_1ms_TASK; // Reset the Event Bit
        Timer1msTask();
    } 
    
    if(lclEventReg & EVENT_TIMER_10ms_TASK)
    {
        lclEventReg &= ~EVENT_TIMER_10ms_TASK; // Reset the Event Bit
        Timer10msTask();
    }  
    
    if(lclEventReg & EVENT_TIMER_25ms_TASK)
    {
        lclEventReg &= ~EVENT_TIMER_25ms_TASK; // Reset the Event Bit
        Timer25msTask();
    }     
    eventRegister = lclEventReg;    // Must be atomic
}
//******************************************************************************


//******************************************************************************
// Timer1msTask 
// Input - None
// This function will execute the functions which requires 1ms duration 
//******************************************************************************
void Timer1msTask (void)
{
    if(++cnt5ms > 4){
        
        static int startup_step_count = 0;
        
        if (startup_step_count < STARTUP_STEP_COUNT_LIMIT) {
            startup_sensor_vector = next_sensor_vector[startup_sensor_vector - 1];
            write_switching_vector(startup_sensor_vector, 1);

            startup_step_count++;
        } else {
            motor_started = true;
        }
        cnt5ms = 0;
    }
}
//******************************************************************************


//******************************************************************************
// Timer10msTask 
// Input - None 
// This function will execute the functions which requires 10ms duration 
//******************************************************************************
void Timer10msTask (void)
{
//    static int startup_step_count = 0;
        
   // if (startup_step_count < STARTUP_STEP_COUNT_LIMIT || 1) {
//        volatile char sensor_vector = (IO_RB3_U_ZCD_GetValue() << 2) 
//                    + (IO_RC1_V_ZCD_GetValue() << 1) 
//                    + (IO_RA11_W_ZCD_GetValue());
//        write_switching_vector(sensor_vector, 1);
//        write_switching_vector(startup_sensor_vector, 1);
//
//        startup_sensor_vector = next_sensor_vector[startup_sensor_vector - 1];
//        startup_step_count++;
   // }
}
//******************************************************************************


//******************************************************************************
// Timer25msTask 
// Input - None
// This function will execute the functions which requires 25ms duration 
//******************************************************************************
void Timer25msTask (void)
{
//    static int startup_step_count = 0;
//        
//    if (startup_step_count < STARTUP_STEP_COUNT_LIMIT || 1) {
////        volatile char sensor_vector = (IO_RB3_U_ZCD_GetValue() << 2) 
////                    + (IO_RC1_V_ZCD_GetValue() << 1) 
////                    + (IO_RA11_W_ZCD_GetValue());
////        write_switching_vector(sensor_vector, 1);
//        write_switching_vector(startup_sensor_vector, 1);
//
//        startup_sensor_vector = next_sensor_vector[startup_sensor_vector - 1];
//        startup_step_count++;
//    } else if (!motor_started){
//        initInterrupts();
//    }
   //IO_RD5_HB_LED_Toggle();   
    
//    write_switching_vector(startup_sensor_vector, 1);
//
//    startup_sensor_vector = next_sensor_vector[startup_sensor_vector - 1];
    
    cnt100ms++;
    if(cnt100ms > 3){
        //runMotorWithControl();
        //IO_RD5_BLDC_LED_Toggle();
        cnt100ms = 0;
    }
    
}
//******************************************************************************


//******************************************************************************
// Timer1msTask 
// Input - None
// This function is event based function 
//******************************************************************************
void MODBUSDecodeTask (void)
{
    //decodeRecieveMessage();
} 
//******************************************************************************


//******************************************************************************
// CANBUSDecodeTask 
// Input - None
// This function is event based function 
//******************************************************************************
void CANBUSDecodeTask (void)
{
    
}
//******************************************************************************


//******************************************************************************
// CANBUSDecodeTask 
// Input - None
// This function is event based function 
//******************************************************************************
void EthernetDecodeTask (void)
{
    
}
//******************************************************************************
