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
