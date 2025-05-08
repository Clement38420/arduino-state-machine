#include <fsm.h>

FSM::FSM(State *initial_state, Transition transitions[]) {
  current_state_ = initial_state;
  transitions_ = transitions;
  number_of_transitions_ = sizeof(transitions) / sizeof(Transition);
}

State *FSM::ProcessStateTransitions() {
  for (int i = 0; i < number_of_transitions_; i++) {
    const Transition &t = transitions_[i];
    if (t.current_state == current_state_ && t.condition()) {
      ApplyTransition(t);
      break;
    }
  }
  return current_state_;
}

void FSM::ApplyTransition(const Transition &t) {
  if (current_state_->on_exit_action) {
    current_state_->on_exit_action;
  }

  if (t.action) {
    t.action();
  }

  current_state_ = t.next_state;

  if (current_state_->on_entry_action) {
    current_state_->on_entry_action;
  }
}

