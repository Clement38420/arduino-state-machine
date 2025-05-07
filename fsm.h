#pragma once

typedef void (*ActionFunc)();

struct State {
  ActionFunc on_entry_action;
  ActionFunc periodic_action;
  ActionFunc on_exit_action;
  char name[20];
};
