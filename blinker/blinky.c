/*.$file${.::blinky.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: blinky_bsp.qm
* File:  ${.::blinky.c}
*
* This code has been generated by QM 5.1.1 <www.state-machine.com/qm/>.
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*/
/*.$endhead${.::blinky.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#include "qpn.h"       // QP-nano framework
#include "blinky.h"  // Blinky interface
#include "bsp.h"     // BSP for this application
#include "logger.h"

const Q_ROM char LOG_MSG_LED_OFF[] = "Led Off";
const Q_ROM char LOG_MSG_LED_ON[] = "Led On";

//============================================================================
// declare all AO classes...
/*.$declare${AOs::Blinky} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${AOs::Blinky} ..........................................................*/
typedef struct Blinky {
/* protected: */
    QActive super;
} Blinky;

/* protected: */
static QState Blinky_initial(Blinky * const me);
static QState Blinky_off(Blinky * const me);
static QState Blinky_on(Blinky * const me);
/*.$enddecl${AOs::Blinky} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
//...

// AO instances and event queue buffers for them...
struct Blinky AO_Blinky;

//============================================================================
void Blinky_ctor(void) {
    Blinky * const me = &AO_Blinky;
    QActive_ctor(&me->super, Q_STATE_CAST(&Blinky_initial));
}

//============================================================================
// define all AO classes (state machine)...
/*.$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*. Check for the minimum required QP version */
#if (QP_VERSION < 690U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpn version 6.9.0 or higher required
#endif
/*.$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*.$define${AOs::Blinky} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*.${AOs::Blinky} ..........................................................*/
/*.${AOs::Blinky::SM} ......................................................*/
static QState Blinky_initial(Blinky * const me) {
    /*.${AOs::Blinky::SM::initial} */
    QActive_armX((QActive *)me, 0U,
      BSP_TICKS_PER_SEC/2U, BSP_TICKS_PER_SEC);
    logger("Start");
    return Q_TRAN(&Blinky_off);
}
/*.${AOs::Blinky::SM::off} .................................................*/
static QState Blinky_off(Blinky * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${AOs::Blinky::SM::off} */
        case Q_ENTRY_SIG: {
            logger_P(LOG_MSG_LED_ON);
            BSP_onboardLedOff ();
            status_ = Q_HANDLED();
            break;
        }
        /*.${AOs::Blinky::SM::off::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            status_ = Q_TRAN(&Blinky_on);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*.${AOs::Blinky::SM::on} ..................................................*/
static QState Blinky_on(Blinky * const me) {
    QState status_;
    switch (Q_SIG(me)) {
        /*.${AOs::Blinky::SM::on} */
        case Q_ENTRY_SIG: {
            logger_P(LOG_MSG_LED_OFF);
            //logger("LED OFF");
            BSP_onboardLedOn ();
            status_ = Q_HANDLED();
            break;
        }
        /*.${AOs::Blinky::SM::on::Q_BUTTON_PRESSED} */
        case Q_BUTTON_PRESSED_SIG: {
            status_ = Q_TRAN(&Blinky_off);
            break;
        }
        /*.${AOs::Blinky::SM::on::Q_TIMEOUT} */
        case Q_TIMEOUT_SIG: {
            status_ = Q_TRAN(&Blinky_off);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*.$enddef${AOs::Blinky} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
//...
