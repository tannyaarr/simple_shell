#include "shell.h"



void handle_echo_command(shell_data *data)
{
    int i;
    for (i = 1; i < data->num_args; i++) {
        printf("%s", data->args[i]);
        if (i != data->num_args - 1) {
            printf(" ");
        }
    }
    printf("\n");
    if (data->line != NULL) {
        free(data->line);
        data->line = NULL;
    }

}

char* _getenv(const char* name) {
    extern char** environ;
    int nameLen = _strlen(name);
    int i;

    for (i = 0; environ[i] != NULL; i++) {
        if (_strncmp(name, environ[i], nameLen) == 0 && environ[i][nameLen] == '=') 
        {
            return (environ[i] + nameLen + 1);
        }
    }

    return (NULL);
}
