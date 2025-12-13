#include "logs.h"
#include "panic.h"

#pragma once

const char *_mod_fn_failed_start = "The module ";
const char *_mod_fn_failed_end = " failed to ";
const char *_start_msg = "start";
const char *_exit_msg = "exit";

const char *_starting_mod = "Starting module ";
const char *_started = "Started ";

typedef struct kernel_module {
  const char *name;
  int (*init)();
  int (*exit)();
} kernel_module_t;

inline int _load_mod(const kernel_module_t mod) {
  if (!mod.init || !mod.exit || !mod.name) {
    panic("Attempted to load undefined module");
    return 1;
  }

  size_t starting_mod_msg_len =
      strlen(_starting_mod) + strlen(mod.name) + strlen("...");

  char starting_mod_msg[starting_mod_msg_len];
  starting_mod_msg[0] = '\0';

  strcat(starting_mod_msg, _starting_mod);
  strcat(starting_mod_msg, mod.name);
  strcat(starting_mod_msg, "...");

  puts_status(status_map[STATUS_WAIT], starting_mod_msg);

  const int init_status = mod.init();

  size_t started_mod_msg_len =
      strlen(_started) + strlen(mod.name) + strlen(".");

  char started_mod_msg[started_mod_msg_len];
  started_mod_msg[0] = '\0';

  strcat(started_mod_msg, _started);
  strcat(started_mod_msg, mod.name);
  strcat(started_mod_msg, ".");

  puts_status(status_map[init_status != 0 ? STATUS_FAIL : STATUS_OK],
              started_mod_msg);

  if (init_status != 0) {
    size_t len = strlen(_mod_fn_failed_start) + strlen(mod.name) +
                 strlen(_mod_fn_failed_end) + strlen(_start_msg) + 1;

    char msg[len];
    msg[0] = '\0';

    strcat(msg, _mod_fn_failed_start);
    strcat(msg, mod.name);
    strcat(msg, _mod_fn_failed_end);
    strcat(msg, _start_msg);

    panic(msg);
  }

  return init_status;
}

inline int _unload_mod(const kernel_module_t mod) {
  if (!mod.init || !mod.exit || !mod.name) {
    panic("Attempted to unload undefined module");
    return 1;
  }

  const int exit_status = mod.exit();

  if (exit_status != 0) {
    size_t len = strlen(_mod_fn_failed_start) + strlen(mod.name) +
                 strlen(_mod_fn_failed_end) + strlen(_exit_msg) + 1;

    char msg[len];
    msg[0] = '\0';

    strcat(msg, _mod_fn_failed_start);
    strcat(msg, mod.name);
    strcat(msg, _mod_fn_failed_end);
    strcat(msg, _exit_msg);

    panic(msg);
  }

  return exit_status;
}

inline int add_mod(const kernel_module_t mod) {
  const int load_res = _load_mod(mod);

  if (load_res != 0) {
    const int unload_res = _unload_mod(mod);

    if (unload_res != 0) {
      panic("Attempted to add faulty module that couldn't be loaded nor "
            "unloaded");
    }
  }

  return load_res;
}
