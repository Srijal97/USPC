/* 
 * File:   ISRs.h
 * Author: Srijal
 *
 * Created on May 12, 2019, 1:07 PM
 */

#ifndef ISRS_H
#define	ISRS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Macros.h"
#include "projMacros.h"
#include "stdbool.h"
#include "motorFun.h"

    
void enableInterrupts(void);

void disableInterrupts(void);

void initInterrupts(void);

void __attribute__((__interrupt__,no_auto_psv)) _CNInterrupt(void);

extern bool motor_started;

#ifdef	__cplusplus
}
#endif

#endif	/* ISRS_H */

