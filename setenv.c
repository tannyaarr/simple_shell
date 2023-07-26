#include "shell.h"


int add_environment_variable(const char *name, const char *value) {
    int nLen = _strlen(name);
    int vaLen = _strlen(value);
    char *newStr = (char *)malloc((nLen + vaLen + 2) * sizeof(char));
    int envCnt = 0;
    if (newStr == NULL) {
        return -1;
    }
    sprintf(newStr, "%s=%s", name, value);
    
    while (environ[envCnt] != NULL) {
        envCnt++;
    }
    environ[envCnt] = newStr;
    environ[envCnt + 1] = NULL;
    return 0;
}

int update_environment_variable(const char *name, const char *value) {
    int nLen = _strlen(name);
    int vaLen = _strlen(value);
    char **env = environ;
    char *newStr = NULL;

    while (*env != NULL) {
        char *envCpy = _strdup(*env);
        char *myname = strtok(envCpy, "=");
        if (_strcmp(myname, name) == 0) {
            newStr = (char *)malloc((nLen + vaLen + 2) * sizeof(char));
            if (newStr == NULL) {
                    free(envCpy);
                return -1;
            }
            sprintf(newStr, "%s=%s", name, value);
            *env = newStr;
            free(envCpy);
            return 0;
        }
        env++;
        free(envCpy);
    }
    return -1;
}

int _setenv(const char *name, const char *value, int overwrite) {
    if (_getenv(name) != NULL) {
        if (overwrite != 0) {
            return update_environment_variable(name, value);
        }
    } else {
        return add_environment_variable(name, value);
    }
    return 0;
}
