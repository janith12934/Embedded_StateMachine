/*
 * stateMachine.c
 *
 *  Created on: Feb 28, 2024
 *  Author: Janith Wimalaratne
 */

/*----------------------------------------------------------------------------
 * 						External variables
 *----------------------------------------------------------------------------*/

StateMachine sm;
State_t stateTx;

/*----------------------------------------------------------------------------
 * 						Function prototypes
 *----------------------------------------------------------------------------*/

static inline void handleIdle(struct StateMachine* sm, Event event);
static inline void handleStart(struct StateMachine* sm, Event event);
static inline void handleCooling(struct StateMachine* sm, Event event);
static inline void handleStop(struct StateMachine* sm, Event event);
static inline void handleError(struct StateMachine* sm, Event event);
static inline void handleReset(struct StateMachine* sm, Event event);
extern void blinkIndicator(uint8_t mode, uint32_t delayMs);


/*----------------------------------------------------------------------------
 * 						State Machine Function
 *----------------------------------------------------------------------------*/

/**
 * @brief Initialize the state machine with the initial state and function pointers.
 * @param sm: Pointer to the state machine structure
 */
void initStateMachine(StateMachine* sm) {
    sm->currentState = STATE_IDLE;
    sm->stateFunctions[STATE_IDLE] 		= handleIdle;
    sm->stateFunctions[STATE_START] 	= handleStart;
    sm->stateFunctions[STATE_COOLING] 	= handleCooling;
    sm->stateFunctions[STATE_STOP] 		= handleStop;
    sm->stateFunctions[STATE_ERROR] 	= handleError;
    sm->stateFunctions[STATE_RESET] 	= handleReset;
}

/**
 * @brief Handle the given event based on the current state of the state machine.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
void handleEvent(StateMachine* sm, Event event) {
    if (sm->currentState < STATE_MAX) {
        sm->stateFunctions[sm->currentState](sm, event);
    }
}


/*----------------------------------------------------------------------------
 * 						State Machine Handlers
 *----------------------------------------------------------------------------*/

/**
 * @brief Handle events in the Idle state.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleIdle(struct StateMachine* sm, Event event) {
    setTX(&rs485Data, &rs485Data.readyTX, READY);
    switch (event) {
        case EVENT_ERROR_COM:
        case EVENT_ERROR_MOD:
            sm->currentState = STATE_ERROR;
            error_func(event);
            break;
        case EVENT_HOT:
            sm->currentState = STATE_COOLING;
            cool_func();
            break;
        case EVENT_START:
            sm->currentState = STATE_START;
            start_func();
            break;

        // Ignored events
        case EVENT_STOP:
        case EVENT_ERROR_HW:
        case EVENT_RESET:
        case EVENT_COOL:
        case EVENT_MAX:
        default:
            idle_func();
            break;
    }
}


/**
 * @brief Handle events in the Start state.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleStart(struct StateMachine* sm, Event event) {
    setTX(&rs485Data, &rs485Data.readyTX, READY);
    switch (event) {
        case EVENT_ERROR_COM:
        case EVENT_ERROR_MOD:
        case EVENT_ERROR_HW:
            sm->currentState = STATE_ERROR;
            error_func(event);
            break;
        case EVENT_HOT:
            sm->currentState = STATE_COOLING;
            cool_func();
            break;
        case EVENT_STOP:
            sm->currentState = STATE_STOP;
            stop_func();
            break;

        // Ignored events
        case EVENT_START:
        case EVENT_RESET:
        case EVENT_COOL:
        case EVENT_MAX:
        default:
            start_func();
            break;
    }
}


/**
 * @brief Handle events in the Cooling state.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleCooling(struct StateMachine* sm, Event event) {
    setTX(&rs485Data, &rs485Data.readyTX, READY);
    switch (event) {
        case EVENT_ERROR_COM:
        case EVENT_ERROR_HW:
        case EVENT_ERROR_MOD:
            sm->currentState = STATE_ERROR;
            error_func(event);
            break;
        case EVENT_START:
            sm->currentState = STATE_START;
            start_func();
            break;
        case EVENT_STOP:
            sm->currentState = STATE_STOP;
            stop_func();
            break;
        case EVENT_MAX:
            sm->currentState = STATE_IDLE;
            idle_func();
            break;

        // Ignored events
        case EVENT_HOT:
        case EVENT_COOL:
        case EVENT_RESET:
        default:
            cool_func();
            break;
    }
}


/**
 * @brief Handle events in the Stop state.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleStop(struct StateMachine* sm, Event event) {
    setTX(&rs485Data, &rs485Data.readyTX, READY);
    switch (event) {
        case EVENT_ERROR_COM:
        case EVENT_ERROR_MOD:
            sm->currentState = STATE_ERROR;
            error_func(event);
            break;

        // Ignored events
        case EVENT_STOP:
        case EVENT_START:
        case EVENT_ERROR_HW:
        case EVENT_RESET:
        case EVENT_COOL:
        case EVENT_HOT:
        case EVENT_MAX:
        default:
            stop_func();
            sm->currentState = STATE_IDLE;
            break;
    }
}

/**
 * @brief Handle events in the Error state.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleError(struct StateMachine* sm, Event event) {
    switch (event) {
        case EVENT_RESET:
            sm->currentState = STATE_RESET;
            break;
        case EVENT_MAX:
            sm->currentState = STATE_IDLE;
            idle_func();
            break;

        // Ignored events
        case EVENT_START:
        case EVENT_STOP:
        case EVENT_ERROR_HW:
        case EVENT_COOL:
        case EVENT_HOT:
        case EVENT_ERROR_COM:
        case EVENT_ERROR_MOD:
        default:
            error_func(event);
            break;
    }
}


/**
 * @brief Handle events in the Reset state.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleReset(struct StateMachine* sm, Event event) {
    setTX(&rs485Data, &rs485Data.readyTX, NOT_READY);
    switch (event) {
        case EVENT_MAX:
            sm->currentState = STATE_IDLE;
            idle_func();
            break;

        // Silently ignored events
        case EVENT_START:
        case EVENT_STOP:
        case EVENT_ERROR_HW:
        case EVENT_RESET:
        case EVENT_COOL:
        case EVENT_HOT:
        case EVENT_ERROR_COM:
        case EVENT_ERROR_MOD:
        default:
            break;
    }
}
/*----------------------------------------------------------------------------
 * 						State Handler Functions
 *----------------------------------------------------------------------------*/

/**
 * @brief Perform actions for the Idle state.
 */
void idle_func(void) {
    ActuatorOff();
}

/**
 * @brief Perform actions for the Start state.
 */
void start_func(void) {
    ActuatorOn();
}

/**
 * @brief Perform actions for the Cooling state.
 */
void cool_func(void) {
    ActuatorOn();
}

/**
 * @brief Perform actions for the Stop state.
 */
void stop_func(void) {
	ActuatorOff();
}

/**
 * @brief Perform actions for the Reset state.
 */
void reset_func() {
    // Handle null state
	ActuatorOff();
}


/**
 * @brief Handle errors based on the event.
 * @param event: The event that triggered the error
 */
void error_func(int event) {
    setTX(&rs485Data, &rs485Data.readyTX, NOT_READY);

    if (event == EVENT_ERROR_COM) {
    	blinkIndicator(LED_MODE_ON, 0);
        setTX(&rs485Data, &rs485Data.readyTX, NOT_READY);
        CheckCanaries(&CSMS_Queue); // Check for com buffer overflow
        ActuatorOff();

        // Check whether error is resolved
        if (rs485Data.charging == CHARGING || rs485Data.charging == NOT_CHARGING) {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
            handleEvent(&sm, EVENT_MAX);
        }

    } else if (event == EVENT_ERROR_MOD) {

        // Current Leak Check
        while (rs485Data.moduleCurrent > CURRENT_ERROR && rs485Data.charging == NOT_CHARGING) {
            ActuatorOff();
            setTX(&rs485Data, &rs485Data.ModuleError, SET_CURRENT_LEAK);  // current leak
            CSMS_functions();
            transmitSerial();
            blinkIndicator(LED_MODE_BLINK, 3000);
            HAL_IWDG_Refresh(&hiwdg);
        }

        // Overheat Check
        while (rs485Data.moduleTemperature > TEMPHIGH_THRESHOLD) {
            ActuatorOn();
            setTX(&rs485Data, &rs485Data.ModuleError, SET_MODULE_OVERHEAT);  // module overheat
            CSMS_functions();
            transmitSerial();
            blinkIndicator(LED_MODE_BLINK, 1000);
            HAL_IWDG_Refresh(&hiwdg);  // Watchdog timer reset at 1000ms
        }

    } else {
        setTX(&rs485Data, &rs485Data.ActuatorError, SET_NO_ERROR);
        setTX(&rs485Data, &rs485Data.ModuleError, SET_NO_ERROR);
        handleEvent(&sm, EVENT_MAX);
    }

    blinkIndicator(LED_MODE_OFF, 0);
}
