/*
 * File:	start.c
 * Purpose:	Kinetis start up routines.
 *
 * Notes:		
 */

#include "start.h"
#include "common.h"
#include "sysinit.h"
#include "wdog.h"

/********************************************************************/
/*!
 * \brief   Kinetis Start
 * \return  None
 *
 * This function calls all of the needed starup routines and then
 * branches to the main process.
 */
void start(void)
{
    /* Disable the watchdog timer */
    wdog_disable();
    /* Copy any vector or data sections that need to be in RAM */
    common_startup();
    /* Perform processor initialization */
    sysinit();

    /* Determine specific Kinetis device and revision */
    
    /* Jump to main process */
    main();

    /* No actions to perform after this so wait forever */
    while(1);
}
/********************************************************************/

