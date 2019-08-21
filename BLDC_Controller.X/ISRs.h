/* 
 * File:   ISRs.h
 * Author: Eshu
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
    
void enableInterrupts(void);

void disableInterrupts(void);

void initInterrupts(void);

void __attribute__((__interrupt__,no_auto_psv)) _CNInterrupt(void);
    


#ifdef	__cplusplus
}
#endif

#endif	/* ISRS_H */

