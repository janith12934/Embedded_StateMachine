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

static inline void handleSTATE_1(struct StateMachine* sm, Event event);
static inline void handleSTATE_2(struct StateMachine* sm, Event event);
static inline void handleSTATE_3(struct StateMachine* sm, Event event);
static inline void handleSTATE_4(struct StateMachine* sm, Event event);
static inline void handleSTATE_5(struct StateMachine* sm, Event event);
static inline void handleSTATE_6(struct StateMachine* sm, Event event);


/*----------------------------------------------------------------------------
 * 						State Machine Function
 *----------------------------------------------------------------------------*/

/**
 * @brief Initialize the state machine with the initial state and function pointers.
 * @param sm: Pointer to the state machine structure
 */
void initStateMachine(StateMachine* sm) {
    sm->currentState = STATE_1;
    sm->stateFunctions[STATE_1] 	= handleSTATE_1;
    sm->stateFunctions[STATE_2] 	= handleSTATE_2;
    sm->stateFunctions[STATE_3] 	= handleSTATE_3;
    sm->stateFunctions[STATE_4] 	= handleSTATE_4;
    sm->stateFunctions[STATE_5] 	= handleSTATE_5;
    sm->stateFunctions[STATE_6] 	= handleSTATE_6;
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
 * @brief Handle events in the State 1.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleSTATE_1(struct StateMachine* sm, Event event) {
    switch (event) {
        case EVENT_1:
        case EVENT_2:
            sm->currentState = STATE_6;
            STATE_6_func(void);
            break;
        case EVENT_3:
            sm->currentState = STATE_3;
            STATE_3_func();
            break;
        case EVENT_4:
            sm->currentState = STATE_5;
            STATE_5_func();
            break;

        // Ignored events
        case EVENT_MAX:
        case EVENT_5:
        default:
            STATE_1_func();
            break;
    }
}


/**
 * @brief Handle events in the State 2.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleSTATE_2(struct StateMachine* sm, Event event) {
    switch (event) {
        case EVENT_1:
        case EVENT_2:
        case EVENT_3:
            sm->currentState = STATE_6;
            STATE_6_func(void);
            break;
        case EVENT_4:
            sm->currentState = STATE_5;
            STATE_5_func();
            break;
        // Ignored events
        case EVENT_5:
        case EVENT_MAX:
        default:
            STATE_2_func();
            break;
    }
}


/**
 * @brief Handle events in the State 3.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleSTATE_3(struct StateMachine* sm, Event event) {
    setTX(&rs485Data, &rs485Data.readyTX, READY);
    switch (event) {
        case EVENT_4:
        case EVENT_2:
        case EVENT_5:
            sm->currentState = STATE_3;
            STATE_3_func(event);
            break;
        // Ignored events
        case EVENT_1:
        case EVENT_3:
        case EVENT_MAX:
        default:
            STATE_3_func();
            break;
    }
}


/**
 * @brief Handle events in the State 4.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleSTATE_4(struct StateMachine* sm, Event event) {
    setTX(&rs485Data, &rs485Data.readyTX, READY);
    switch (event) {
        case EVENT_4:
        case EVENT_2:
        case EVENT_5:
            sm->currentState = STATE_3;
            STATE_3_func(event);
            break;
        // Ignored events
        case EVENT_1:
        case EVENT_3:
        case EVENT_MAX:
        default:
            STATE_4_func();
            sm->currentState = STATE_IDLE;
            break;
    }
}

/**
 * @brief Handle events in the State 5.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleSTATE_5(struct StateMachine* sm, Event event) {
    switch (event) {
        case EVENT_1:
        case EVENT_2:
        case EVENT_3:
            sm->currentState = STATE_6;
            STATE_6_func(void);
            break;

        // Ignored events
        case EVENT_4:
        case EVENT_5:
        case EVENT_MAX:
        default:
            STATE_5_func(event);
            break;
    }
}


/**
 * @brief Handle events in the State 6.
 * @param sm: Pointer to the state machine structure
 * @param event: Event to be handled
 */
static inline void handleSTATE_6(struct StateMachine* sm, Event event) {
    setTX(&rs485Data, &rs485Data.readyTX, NOT_READY);
    switch (event) {
        case EVENT_1:
        case EVENT_2:
        case EVENT_3:
            sm->currentState = STATE_6;
            STATE_6_func(void);
            break;

        // Ignored events
        case EVENT_4:
        case EVENT_5:
        case EVENT_MAX:
        default:
        STATE_6_func();
            break;
    }
}
/*----------------------------------------------------------------------------
 * 						State Handler Functions
 *----------------------------------------------------------------------------*/

/**
 * @brief Perform actions for the State 1.
 */
void STATE_1_func(void) {
    //Include desired functions
}

/**
 * @brief Perform actions for the State 2.
 */
void STATE_2_func(void) {
   //Include desired functions
}

/**
 * @brief Perform actions for the State 3.
 */
void STATE_3_func(void) {
    //Include desired functions
}

/**
 * @brief Perform actions for the State 4.
 */
void STATE_4_func(void) {
	//Include desired functions
}

/**
 * @brief Perform actions for the State 5.
 */
void STATE_5_func() {
	//Include desired functions
}

/**
 * @brief Perform actions for the State 6.
 */
void STATE_6_func() {
    //Include desired functions
}