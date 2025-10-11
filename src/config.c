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

void    handle_signal(void)
{
    if (g_signal == 100)
    {
        g_sinal = 1;
        rl_redisplay();
        ioctl(0, TIOCSTI, "\n");
		return ;
    }
    if (g_signal == 200)
	{
		g_signal = 1;
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		return ;
	}
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void    init_signal(void)
{
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, SIG_IGN);
}