#include "taskmaster.h"
#include "ft_printf.h"

char    *check_exit(char *command)
{

}

char    *terminal_string(char *command)
{
    
}

bool    prompt_loop(char *cmd, t_program_config *config)
{
    char    *command;
    char    *next_command;

    init_signal();
    next_command = !cmd;
    if (!cmd)
    {
        command = no_last_space(readline(PROMPT));
        if (!command)
            return (false);
        cmd = terminal_string(command);
    }
    add_history(cmd);
    next_command = check_exit(cmd);
    return (next_command);
}