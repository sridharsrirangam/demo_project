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
#include <stdio.h>
#include <math.h>
#include "gpio_defs.h"
#include "LEDs.h"
#include "i2c.h"
#include "mma8451.h"
#include "delay.h"
#include "timers.h"

unsigned LCD_update_delay = 100;
int i;
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
{ int j,k,l;
  InitPorts();
	Init_PIT(2400000); //real value should be 2400000
  i2c_init();
		if (!init_mma()) {												/* init mma peripheral */
		//Control_RGB_LEDs(1, 0, 0);							/* Light red error LED */
		while (1)			/* not able to initialize mma */
			;
	}
		Delay(1000);
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
   #if TSS_USE_FREEMASTER_GUI
      FMSTR_Poll();
    #endif 

    if (TSS_Task() == TSS_STATUS_OK)
    {
      #if (LOW_POWER_TSI)
        LowPowerControl();
      #endif
	}
	
		
    
#if 1
//Init_RGB_LEDs();
																	/* init i2c	*/

	
	
	
	//while (1) 
		
		read_full_xyz();
		convert_xyz_to_roll_pitch();
	
		// Light green LED if pitch > 10 degrees
		// Light blue LED if roll > 10 degrees
		/*Control_RGB_LEDs(0, (fabs(roll) > 30)? 1:0,(fabs(pitch) > 10)? 1:0);*/
if(fabs(roll)>33||fabs(pitch)>33)
	{
		while(i<cASlider1.Position)
		{
			SET_LED_RED(i);
			SET_LED_GREEN(i);
			SET_LED_BLUE(i);
			DelayMS(30);
			i++;
		}
		SET_LED_RED(cASlider1.Position);
			SET_LED_GREEN(cASlider1.Position);
			SET_LED_BLUE(cASlider1.Position);
		LCD_update_delay = 100;
		Start_PIT();
		//Control_RGB_LEDs(1,1,1);
		//Delay(200);
	}
	/*else
	{
	SET_LED_RED(0);
  SET_LED_GREEN(0);
	SET_LED_BLUE(0);
		//Control_RGB_LEDs(0,0,0);
	}*/
 
	#endif
	
    /* Write your code here ... */
  
}}
