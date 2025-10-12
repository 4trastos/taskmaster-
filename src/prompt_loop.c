#include "taskmaster.h"
#include "ft_printf.h"

bool    prompt_loop(t_program_config *config)
{
    char    *command;

    command = no_last_space(readline(PROMPT));
    if (!command)
        return (false);
    add_history(command);
    if (ft_strcmp("exit", command) == 0)
        return (false);
    return (true);
}
