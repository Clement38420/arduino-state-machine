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
     * @param number_of_transitions The size of the array of transitions.
     */
    FSM(State *initial_state, Transition transitions[], int number_of_transitions);

    /**
     * Gets the current state of the FSM.
     * @return A pointer to the current state.
     */
    State *GetCurrentState() const { return current_state_; }
    void SetCurrentState(State *state) { current_state_ = state; }

    /**
     * @brief Execute periodic action and processes state transitions.
     *
     * Transitions are processed by evaluating conditions and applying the first valid transition.
     *
     * @return A pointer to the current state after processing transitions.
     */
    State *RunFSM();

    /**
     * @brief Launches the state machine.
     *
     * It actually executes the current state entry action.
     */
    void Begin() const;

  private:
    State *current_state_;
    Transition *transitions_; /**< The array of transitions for the FSM. */
    int number_of_transitions_;

    /**
     * Applies a transition by executing its actions and updating the current state.
     * @param t The transition to apply.
     */
    void ApplyTransition(const Transition &t);

    /**
     * Execute an action if it exists.
     * @param action The action to check and execute.
     */
    static void ExecuteAction(ActionFunc action);
};

#endif
