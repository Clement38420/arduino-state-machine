#pragma once

typedef void (*ActionFunc)();

typedef bool (*Condition)();

struct State {
  ActionFunc on_entry_action;
  ActionFunc periodic_action;
  ActionFunc on_exit_action;
  char name[20];
};

struct Transition {
  State *current_state;
  Condition condition;
  ActionFunc action;
  State *next_state;
};

class FSM {
  public:
    FSM(State *initial_state, Transition *transitions);
    State *GetCurrentState() const { return current_state_; };
    State *ProcessStateTransitions();

  private:
    State *current_state_;
    Transition *transitions_;
    int number_of_transitions_;

    void ApplyTransition(const Transition &t);
};
