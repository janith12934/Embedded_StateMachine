# State Machine Implementation

This repository provides a robust, modular, and scalable finite state machine (FSM) implementation in C. It is designed for embedded systems but can be adapted to any C application requiring structured state transitions.

## Features

- Simple and clear state management using enums.
- Event-driven state transitions.
- Easy to initialize and extend.
- Modular and testable state handler design.
- Supports multiple independent state machines.

---

## 🧠 Overview

The FSM is structured around two core enums:
- `State_t`: Represents all possible states (`STATE_1` to `STATE_6`).
- `Event`: Represents all triggering events (`EVENT_1` to `EVENT_5`).

Each state has a corresponding handler that checks the current event and executes transitions accordingly.

---

## 🚀 Getting Started

### 1. Initialization

In your `main.c`, initialize the state machine with:

```c
int main(void)
{
    initStateMachine(&sm); // State machine initialization
    while (1)
    {

    }
}
```

To create multiple independent state machines:

```c
StateMachine sm1, sm2;
initStateMachine(&sm1);
initStateMachine(&sm2);
```

Each instance will maintain its own current state and transitions.

---

### 2. Triggering State Transitions

Trigger a transition based on an event using:

```c
handleEvent(&sm, EVENT_X);
```

Where `EVENT_X` is one of:
- `EVENT_1`
- `EVENT_2`
- `EVENT_3`
- `EVENT_4`
- `EVENT_5`

The FSM will execute the function mapped to the current state and perform the appropriate transition and action.

---

## 🧩 Adding or Modifying States

### To Add a New State:
1. Add a new value to the `State_t` enum.
2. Add a new handler function similar to `handleSTATE_X()`.
3. Register it inside `initStateMachine()`.

### To Add a New Event:
1. Add a new value to the `Event` enum.
2. Update all relevant `handleSTATE_X()` functions to process the new event.

---

## 📁 File Structure

```
├── stateMachine.h   // FSM declarations and prototypes
├── stateMachine.c   // FSM logic and event handlers
└── README.md         // You're here!
```

---

## 🛠️ Example

If the FSM is currently in `STATE_1` and `EVENT_3` is received:
```c
handleEvent(&sm, EVENT_3);
```
It transitions to `STATE_3` and executes `STATE_3_func()`.

---

## 🔄 Reusability

This FSM can be reused across different modules by:
- Declaring separate state machines for different purposes.
- Customizing state handlers as per module needs.

---

## 📬 Contributing

Feel free to fork and improve the FSM. PRs are welcome!

---

## 📄 License

MIT License. See `LICENSE` file for details.

