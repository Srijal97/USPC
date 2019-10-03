/* 
 * File:   Tasks.h
 * Author: Eshu
 *
 * Created on May 12, 2019, 1:03 PM
 */

#ifndef TASKS_H
#define	TASKS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Macros.h"
#include "projMacros.h"
#include "stdbool.h"
#include "motorFun.h"
#include "ISRs.h"
    
extern uINT eventRegister;

extern bool motor_started;

extern char startup_sensor_vector;
extern const char next_sensor_vector[];
    
// Functions    
void TimerCallBack          (void); 

void Timer1msTask           (void);
void Timer10msTask          (void);
void Timer25msTask          (void);
void MODBUSDecodeTask       (void);     // Event Based Task
void CANBUSDecodeTask       (void);     // Event Based Task
void EthernetDecodeTask     (void);     // Event Based Task


#ifdef	__cplusplus
}
#endif

#endif	/* TASKS_H */

