#include "timers.h"
#include "MKL25Z4s.h"

#include "TSS_API.h"
#include "board.h"
#include "app_init.h"
#include "events.h"

volatile unsigned PIT_interrupt_counter = 0;
volatile unsigned LCD_update_requested = 0;
	extern unsigned LCD_update_delay;
	extern int i;
void Init_PIT(unsigned period) {
	// Enable clock to PIT module
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	// Enable module, freeze timers in debug mode
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	PIT->MCR |= PIT_MCR_FRZ_MASK;
	
	// Initialize PIT0 to count down from argument 
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(period);

	// No chaining
	PIT->CHANNEL[0].TCTRL &= PIT_TCTRL_CHN_MASK;
	
	// Generate interrupts
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;

	/* Enable Interrupts */
	NVIC_SetPriority(PIT_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PIT_IRQn); 
	NVIC_EnableIRQ(PIT_IRQn);	
}


void Start_PIT(void) {
// Enable counter
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void Stop_PIT(void) {
// Enable counter
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}


void PIT_IRQHandler() {
int j;
	//clear pending IRQ
	NVIC_ClearPendingIRQ(PIT_IRQn);
	
	// check to see which channel triggered interrupt 
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		// clear status flag for timer channel 0
		PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;
		
		// Do ISR work
		PIT_interrupt_counter++;
		LCD_update_delay--;
		if (LCD_update_delay == 0) 
			{
				/*SET_LED_RED(0);
			SET_LED_GREEN(0);
			SET_LED_BLUE(0);*/
			for(j=cASlider1.Position;j>=0;j--)				
		{
			SET_LED_RED(j);
			SET_LED_GREEN(j);
			SET_LED_BLUE(j);
				DelayMS(20);
		}
	i=0;	
			
			
		}
	} else if (PIT->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK) {
		// clear status flag for timer channel 1
		PIT->CHANNEL[1].TFLG &= PIT_TFLG_TIF_MASK;
	} 
}

// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
