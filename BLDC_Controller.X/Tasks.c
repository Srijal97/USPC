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
        write_switching_vector(startup_sensor_vector, 1);
        startup_sensor_vector = next_sensor_vector[startup_sensor_vector - 1];
           
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
