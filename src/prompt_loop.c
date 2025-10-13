#include "taskmaster.h"
#include "ft_printf.h"

char	*no_last_space(char *str)
{
    size_t  len;

    if (!str)
        return (NULL);
    len = ft_strlen(str);
    if (len < 2)
        return (str);
    len --;
    while (str[len] == ' ' && len > 0)
    {
        str[len] = '\0';
        len --;
    }
    return (str);
}

int    status_comand(t_program_config *config, char *command)
{
    if (ft_strcmp("start", command) == 0)
        config->process->pstate = STARTING;
    else if (ft_strcmp("stop", command) == 0)
    {
        config->process->pstate = STOPPING;
        g_child_status_changed = 1;
    }
    else if (ft_strcmp("restart", command) == 0)
        config->process->pstate = STARTING;
    else if (ft_strcmp("exit", command) == 0)
    {
        config->process->pstate = STOPPING;
        return (-1);
    }
    else
        ft_printf("❌ Comando no reconocido. Use: [start] , [stop] o [restart] ❌\n");
    return (0);

}

bool    prompt_loop(t_program_config *config)
{
    char    *command;

    command = no_last_space(readline(PROMPT));
    if (!command)
        return (false);
    add_history(command);
    if (status_comand(config, command) == -1)
        return (false);
    return (true);
}
