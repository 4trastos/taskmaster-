#include "taskmaster.h"
#include "ft_printf.h"

void    sigchld_handler(int signum)
{
    (void)signum;
    g_child_status_changed = 1;
}

void    sigint_handler(int signum)
{
    (void)signum;
    if (g_signal == 100)
    {
        g_signal = 1;
        rl_redisplay();
        ioctl(0, TIOCSTI, "\n");
		return ;
    }

	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void    init_signal(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGCHLD, sigchld_handler);
}