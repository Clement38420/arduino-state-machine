#ifndef FSM_H
#define FSM_H

typedef void (*ActionFunc)();

typedef bool (*Condition)();

/**
 * Represents a state in the finite state machine.
 */
struct State {
  ActionFunc on_entry_action;
  ActionFunc periodic_action;
  ActionFunc on_exit_action;
  char name[20];
};

/**
 * Represents a transition between two states in the finite state machine.
 */
struct Transition {
  State *current_state;
  Condition condition; /**< Pointer to a function which evaluate the condition to apply the transition. */
  ActionFunc action; /**< Action to execute during the transition. After exit and before entry actions. */
  State *next_state;
};

class FSM {
  public:
    /**
     * Constructs an FSM with an initial state and a set of transitions.
     * @param initial_state The initial state of the FSM.
     * @param transitions The array of transitions for the FSM.
     */
    FSM(State *initial_state, Transition transitions[]);

    /**
     * Gets the current state of the FSM.
     * @return A pointer to the current state.
     */
    State *GetCurrentState() const { return current_state_; };

    /**
     * Processes state transitions by evaluating conditions and applying the first valid transition.
     * @return A pointer to the current state after processing transitions.
     */
    State *ProcessStateTransitions();

  private:
    State *current_state_;
    Transition *transitions_; /**< The array of transitions for the FSM. */
    int number_of_transitions_;

    /**
     * Applies a transition by executing its actions and updating the current state.
     * @param t The transition to apply.
     */
    void ApplyTransition(const Transition &t);
};

#endif
