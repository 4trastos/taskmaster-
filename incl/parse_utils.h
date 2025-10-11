#ifndef PARSEUTILS_H
# define PARSEUTILS_H

# include "taskmaster.h"
#include <signal.h>
#include <string.h>

typedef struct s_signal_map {
    const char *name;
    int value;
} t_signal_map;

//*** UTILS ***/
int *get_exit_codes(char *exit_codes_str);
int get_signal_from_str(const char *str);

#endif