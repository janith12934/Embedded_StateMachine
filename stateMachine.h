/*
 * stateMachine.h
 *
 *  Created on: Feb 28, 2024
 *  Author: Janith Wimalaratne
 */

#ifndef INC_STATEMACHINE_H_
#define INC_STATEMACHINE_H_

/**
 * @brief Enumeration for the various states of the state machine.
 */
typedef enum {
    STATE_1,
    STATE_2,
    STATE_3,
    STATE_4,
    STATE_5,
    STATE_6,
    STATE_MAX
} State_t;

/**
 * @brief Enumeration for the various events that trigger state transitions.
 */
typedef enum {
    EVENT_1,
    EVENT_2,
    EVENT_3,
    EVENT_4,
    EVENT_5,
    EVENT_MAX 
} Event;

struct StateMachine; // Forward declaration

/**
 * @brief Function pointer type for state functions.
 * @param sm Pointer to the state machine
 * @param event Event that triggers the state function
 */
typedef void (*StateFunction)(struct StateMachine* sm, Event event);

/**
 * @brief Structure representing the state machine.
 *        Holds the current state and an array of state functions.
 */
typedef struct StateMachine {
    State_t currentState;                  /**< Current state of the state machine */
    StateFunction stateFunctions[STATE_MAX]; /**< Array of state functions */
} StateMachine;

/**
 * @brief Initialize the state machine.
 * @param sm Pointer to the state machine structure to initialize
 */
void initStateMachine(struct StateMachine* sm);

/**
 * @brief Handle an event and transition to the appropriate state.
 * @param sm Pointer to the state machine structure
 * @param event Event that triggers the state transition
 */
void handleEvent(struct StateMachine* sm, Event event);

/**
 * @brief External declaration of the state machine.
 *        This state machine is used globally in the system.
 */
extern struct StateMachine sm;

/* Function prototypes for state-specific actions */
void STATE_1_func(void);
void STATE_2_func(void);
void STATE_3_func(void);
void STATE_4_func(void);
void STATE_5_func(void);
void STATE_6_func(void);

#endif /* INC_STATEMACHINE_H_ */