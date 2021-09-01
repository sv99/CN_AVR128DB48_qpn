/*
 * qpn_blinker.c
 *
 * Created: 11.08.2021 10:57:12
 * Author : user
 */

#include "qpn.h"    /* QP-nano API           */
#include "bsp.h"    /* Board Support Package */
#include "blinky.h" /* Application interface */

//============================================================================
static QEvt l_blinkyQSto[10]; // Event queue storage for Blinky
//...

//============================================================================
// QF_active[] array defines all active object control blocks ----------------
QActiveCB const Q_ROM QF_active[] = {{(QActive*)0, (QEvt*)0, 0U},
                                     {(QActive*)&AO_Blinky, l_blinkyQSto, Q_DIM(l_blinkyQSto)}};

int main(void)
{
    // initialize the QF-nano framework
    BSP_initSetup();
    QF_init(Q_DIM(QF_active));

    // initialize all AOs...
    Blinky_ctor();

    return QF_run(); /* transfer control to QF-nano          */
}

/* interrupts */

/*********************************************************************
 * system timer
 *********************************************************************/
ISR(Q_TIMER_vect)
{
    QF_tickXISR(0U); /* process time events for rate 0 */
    // QF_tickXISR(1U); /* process time events for rate 1 */
    Q_TIMER.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

/* Logger Data Register Empty */
ISR(LOGGER_DRE_vect)
{
    BSP_LOGGER_dre_isr();
}

/*********************************************************************
 * ISR BSP_buttonPressed()
 *********************************************************************/
void ISR_buttonPressed()
{
    QACTIVE_POST_ISR((QActive*)&AO_Blinky, Q_BUTTON_PRESSED_SIG, 0U);
};
