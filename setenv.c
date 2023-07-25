#include "shell.h"


int _setenv(const char *name, const char *value, int overwrite)
{
  int nLen = _strlen(name);
  int vaLen = _strlen(value);
  int envLen;
  int arrCnt = 0;
  int envCnt = 0;
  char *newStr = NULL, *envCpy = NULL, *myname;
  char **arr = NULL;
  char **env = environ;
  
  if (_getenv(name) != NULL)
  {
    if (overwrite != 0)
    {
      newStr = malloc((nLen + vaLen + 2) * sizeof(*newStr));
      if (newStr == NULL)
        return (-1);
      sprintf(newStr, "%s=%s", name, value);
      while (*env != NULL)
      {
        envCpy = _strdup(*env);
      	myname = strtok(envCpy, ":");
        if (_strcmp(myname, name) == 0)
        {
          *env = newStr;
          free(envCpy);
          break;
        }
        env++;
        free(envCpy);
      }
    }
  }
  else
  {
    	newStr = malloc((nLen + vaLen + 2) * sizeof(*newStr));
      if (newStr == NULL)
        return (-1);
      sprintf(newStr, "%s=%s", name, value);
    	while (*env != NULL)
      {
        envCnt++;
        env++;
      }
    arr = malloc((envCnt + 2) * sizeof(**arr));
    env = environ;
    while (*env != NULL)
    {
      envLen = _strlen(*env);
      arr[arrCnt] = malloc((envLen + 1)* sizeof(char *));
      if (arr[arrCnt] == NULL)
      {
        while (arrCnt >= 0)
        {
          arrCnt--;
          free(arr[arrCnt]);
        }
        free(newStr);
        free(arr);
        return (-1);
      }
      arr[arrCnt] = *env;
      arrCnt++;
      env++;
    }
    arr[arrCnt] = newStr;
    arr[arrCnt + 1] = NULL;
    environ = arr;
  }
  return (0);
}
