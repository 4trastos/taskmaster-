#include "taskmaster.h"
#include "parse_utils.h"
#include "ft_printf.h"

static int check_is_name(char *str){
    if (str[0] != ' '){
        return 1;
    } else if (str[1] != ' '){
        return 1;
    } else if (str[2] == ' ' ){
        return 1;
    } else {
        return 0;
    }
}

static char *get_field(char *str){
    int start;
    int end;

    if (ft_strlen(str) < 8){
        return NULL;
    }

    for (int i = 0; str[i] == ' '; i++){
        start++;
    }

    if (start != 4){
        return NULL;
    }

    for (int i = 3; str[i] != ':'; i++){
        end++;
    }

    return ft_substr(str, start, end);
}

static char *get_field_value(char *str) {
    int start;
    int end;

    for (int i = 0; str[i] != ':'; i++){
        start++;
    }
    start += 2;
    if (str[start] == '"'){
        start++;
        
        for (int i = start; str[i] != '"'; i++){
            end++;
        }

        if (start == end){
            return NULL;
        }

        return ft_substr(str, start, end);
    }

    for (int i = start; str[i] != ' ' && str[i] != '\n'; i++){
        end++;
    }
    
    if (start == end){
        return NULL;
    }

    return ft_substr(str, start, end);
}

int get_number_of_program(char *filename) {
    int     fd;
    int     n;
    char    *line;
    
    fd = open(filename, O_RDONLY);

    n = 0;
    while (get_next_line(fd, &line)){
        if (line[0] != '#'){
            if (check_is_name(line) == 0){
                n++;
            }
        }
    }
    close(fd);
    
    return n;
}

static t_autorestart get_autorestart_value(char *str) {
    if (ft_strcmp(str, "always") == 0) {
        return AR_ALWAYS;
    } else if (ft_strcmp(str, "never") == 0) {
        return AR_NEVER;
    } else {
        return AR_UNEXPECTED;
    }
}

static void fill_field(t_program_config *config, char *field, char *field_value){
    if (ft_strcmp(field, "cmd") == 0) {
        config->command = field_value;
    } else if (ft_strcmp(field, "numprocs") == 0) {
        config->numprocs = ft_atoi(field_value);
    } else if (ft_strcmp(field, "autostart") == 0) {
        config->autostart = ft_atob(field_value);
    } else if (ft_strcmp(field, "autorestart") == 0) {
        config->autorestart = get_autorestart_value(field_value);
    } else if (ft_strcmp(field, "exitcodes") == 0) {
        config->exitcodes = get_exit_codes(field_value);
    } else if (ft_strcmp(field, "startretries") == 0) {
        config->startretries = ft_atoi(field_value);
    } else if (ft_strcmp(field, "starttime") == 0) {
        config->starttime = ft_atoi(field_value);
    } else if (ft_strcmp(field, "stopsignal") == 0) {
        config->stopsignal = get_signal_from_str(field_value);
    } else if (ft_strcmp(field, "stoptime") == 0) {
        config->stoptime = ft_atoi(field_value);
    } else if (ft_strcmp(field, "stdout") == 0) {
        config->stdout_path = field_value;
    } else if (ft_strcmp(field, "stderr") == 0) {
        config->stderr_path = field_value;
    } else if (ft_strcmp(field, "workingdir") == 0) {
        config->workingdir = field_value;
    } else if (ft_strcmp(field, "umask") == 0) {
        config->umask = field_value; //TODO parsear
    }
}

t_program_config init_program_config_structs(char * filename, int progam_index){
    int                 fd;
    int                 i;
    char                *line;
    char                *field;
    char                *field_value;
    t_program_config    config;

    fd = open(filename, O_RDONLY);
    i = 0;
    while (get_next_line(fd, &line)){
        if (line[0] != '#'){
            if (check_is_name(line) == 0)
                i++;
            if (i == progam_index){
                field = get_field(line);
                field_value = get_field_value(line);
                if (field != NULL){
                    fill_field(&config, field, field_value);
                }
                free(field);
                free(field_value);
            } else if (i > progam_index){
                break;
            }
        }
    }

    return config;
}