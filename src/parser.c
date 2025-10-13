#include "taskmaster.h"
#include "ft_printf.h"

int check_is_name(char *str){
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

char *get_field(char *str){
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

    return substr(str, start, end);
}

char *get_field_value(char *str) {
    int start;
    int end;

    for (int i = 0; str[i] != ':'; i++){
        start++;
    }
    start += 2;

    for (int i = start; str[i] != ' '; i++){
        end++;
    }
    
    if (start == end){
        return NULL;
    }

    return substr(str, start, end);
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

void fill_field(t_program_config *config, char *field, char *field_value){
    if (ft_strcmp("cmd", field) == 0)
        config->command = field_value;
    else if (ft_strcmp("numprocs", field) == 0)
        ft_printf("[DEBUG]: FALTA ( numprocs )\n"); 
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