/*HEADER********************************************************************
*
* Copyright (c) 2013 Freescale Semiconductor;
* All Rights Reserved
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* Comments:
*
*   This file contains the source for the TSS example program.
*
*END************************************************************************/
#include "TSS_API.h"
#include "freemaster.h"
#include "app_init.h"
#include "events.h"
#include "main.h"
#include "board.h"


uint16_t u16LPcounter = 0u;

/*********************** GUI - FreeMASTER TSA table ************************/

#if FMSTR_USE_TSA
  /* Example of FreeMASTER User Application Table */
  FMSTR_TSA_TABLE_BEGIN(UserAppTable)
    FMSTR_TSA_RW_VAR(u16LPcounter, FMSTR_TSA_UINT8)
  FMSTR_TSA_TABLE_END()

  /* FreeMASTER Global Table List definition */
  FMSTR_TSA_TABLE_LIST_BEGIN()
    #if TSS_USE_FREEMASTER_GUI
      FMSTR_TSA_TABLE(TSS_Table)
    #endif
    FMSTR_TSA_TABLE(UserAppTable)
  FMSTR_TSA_TABLE_LIST_END()
#endif

/**
 * \brief  Main function
 *
 * \param  void
 *
 * \return int
 */
int main (void)
{ int i,j,k,l;
  InitPorts();
  /* Default TSS init */
  TSS_Init_ASlider();
  /* Init PWM for LED control */
  PWM_init();
  #if TSS_USE_FREEMASTER_GUI
    FreeMASTER_Init();
  #endif
  /* Enable Interrupts globally */
  EnableInterrupts();
  /* Reset Low Power Counter flag */
  u16LPcounter = 0u;

for(i=0;i<100;i++)
	{
  SET_LED_RED(i);
  SET_LED_GREEN(i);
	
  SET_LED_BLUE(i);
		DelayMS(20);
 
}
	
	for(i=100;i>=0;i--)
	{
  SET_LED_RED(i);
	SET_LED_GREEN(i);
	SET_LED_BLUE(i);
		DelayMS(20);
		if (TSS_Task() == TSS_STATUS_OK)
    {
      #if (LOW_POWER_TSI)
        LowPowerControl();
      #endif
		
	}

}
  for(;;)
  {
   /* #if TSS_USE_FREEMASTER_GUI
      FMSTR_Poll();
    #endif */

    if (TSS_Task() == TSS_STATUS_OK)
    {
      #if (LOW_POWER_TSI)
        LowPowerControl();
      #endif
	
		}
    

	
    /* Write your code here ... */
  
}}
