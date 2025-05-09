#include <fsm.h>

FSM::FSM(State *initial_state, Transition transitions[], const int number_of_transitions) {
  current_state_ = initial_state;
  transitions_ = transitions;
  number_of_transitions_ = number_of_transitions;
}

void FSM::Begin() const {
  ExecuteAction(GetCurrentState()->on_entry_action);
}

void FSM::ExecuteAction(const ActionFunc action) {
  if (action) {
    action();
  }
}

State *FSM::RunFSM() {
  ExecuteAction(GetCurrentState()->periodic_action);

  for (int i = 0; i < number_of_transitions_; i++) {
    const Transition &t = transitions_[i];
    if (t.current_state == GetCurrentState() && t.condition()) {
      ApplyTransition(t);
      break;
    }
  }
  return GetCurrentState();
}

void FSM::ApplyTransition(const Transition &t) {
  ExecuteAction(GetCurrentState()->on_exit_action);
  ExecuteAction(t.action);

  SetCurrentState(t.next_state);

  ExecuteAction(GetCurrentState()->on_entry_action);
}

