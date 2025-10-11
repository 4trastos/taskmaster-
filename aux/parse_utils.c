#include "taskmaster.h"
#include "parse_utils.h"

/**
 * @brief coge un array "[1, 2, 3]" y lo convierte a int arr[] = {1, 2, 3}
 */
int *get_exit_codes(char *exit_codes_str) {
    char *copy = strdup(exit_codes_str);
    if (!copy)
        return NULL;

    char *start = ft_strchr(copy, '[');
    char *end = ft_strchr(copy, ']');
    if (!start || !end || end <= start)
    {
        free(copy);
        return NULL;
    }
    *end = '\0';
    start++;

    int count = 1;
    for (char *p = start; *p; p++)
        if (*p == ',')
            count++;

    int *arr = malloc(sizeof(int) * count);
    if (!arr)
    {
        free(copy);
        return NULL;
    }

    int i = 0;
    char *token = strtok(start, ",");
    while (token)
    {
        arr[i++] = atoi(token);
        token = strtok(NULL, ",");
    }

    free(copy);
    return arr;
}

int get_signal_from_str(const char *str)
{
    if (!str)
        return -1;

    t_signal_map signals[] = {
        {"SIGHUP", SIGHUP},
        {"SIGINT", SIGINT},
        {"SIGQUIT", SIGQUIT},
        {"SIGILL", SIGILL},
        {"SIGABRT", SIGABRT},
        {"SIGFPE", SIGFPE},
        {"SIGKILL", SIGKILL},
        {"SIGSEGV", SIGSEGV},
        {"SIGPIPE", SIGPIPE},
        {"SIGALRM", SIGALRM},
        {"SIGTERM", SIGTERM},
        {"SIGUSR1", SIGUSR1},
        {"SIGUSR2", SIGUSR2},
        {"SIGCHLD", SIGCHLD},
        {"SIGCONT", SIGCONT},
        {"SIGSTOP", SIGSTOP},
        {"SIGTSTP", SIGTSTP},
        {"SIGTTIN", SIGTTIN},
        {"SIGTTOU", SIGTTOU},
        {NULL, 0}
    };

    for (int i = 0; signals[i].name != NULL; i++)
    {
        if (ft_strcmp(str, signals[i].name) == 0)
            return signals[i].value;
    }

    return -1;
}