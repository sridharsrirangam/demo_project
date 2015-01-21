#ifndef TIMERS_H
#define TIMERS_H
#include "MKL25Z4s.h"

#define USE_PIT (0)

void Init_PIT(unsigned period);
void Start_PIT(void);
void Stop_PIT(void);

void Init_TPM(unsigned period_ms);
void Start_TPM(void);

void Init_LPTMR(void);
void Start_LPTMR(void);
void Stop_LPTMR(void);

#endif
// *******************************ARM University Program Copyright � ARM Ltd 2013*************************************   
