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

bool    is_exit_code_expected(t_program_config *config, int exit_code)
{

}

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
