#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>
#include <setjmp.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <readline/history.h>
#include <readline/readline.h>

void printDirectory() {
    char dir[100];
    getcwd(dir, sizeof(dir));
    printf("%s", dir);
}

void printStartInfo() {
    char* username = getenv("USER");
    printf("\n\n\n\nWELCOME TO YOUR CUSTOM SHELL @%s!!!", username);
    printf("\n\n\n\n");
    sleep(1);
    system("clear");
}

int takeInput(char* input) {
    char* str;
    str = readline(("\n>> "));
    if (strlen(str) != 0) {
        add_history(str);
		strcpy(input, str);
        return 1;
    } else {
        return 0;
    }
}

void makeInputArray(char* input, char** commands) {
    for (int i = 0; i < sizeof(&input); i++) {
        commands[i] = strsep(&input, " ");
        if (commands[i] == 0)
			break;
		if (strlen(commands[i]) == 0)
			i--;
    }
}

int checkTypeOfCommand(char** commands, char** ec, char** ic) {
    for (int i = 0; i < 5; i++) {
        if (strcmp(ec[i], commands[0]) == 0) {
            return 1;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (strcmp(ic[i], commands[0]) == 0) {
            return 2;
        }
    }
    return 3;
}

void execInternalCmd(char** internalCmds, char** ic, char* input) {
    int len = 0;
    for (int i = 0; i < sizeof(internalCmds); i++) {
        if (internalCmds[i] != NULL && internalCmds[i] != 0) {
            len++;
        }
    }
    if (strcmp(internalCmds[0], ic[0]) == 0) {
        if (len == 1) {
            chdir("~");
        } else if (len == 2) {
            if (chdir(internalCmds[1]) != 0) {
                printf("customshell: cd: %s", internalCmds[1]);
                printf(": No such file or directory\n");
            }
        } else {
            printf("customshell: cd: too many arguments\n");
        }
    } else if (strcmp(internalCmds[0], ic[1]) == 0) {
        if (len == 1) {
            printf("\n");
        } else if ((internalCmds[1][0] == '"' && internalCmds[len-1][strlen(internalCmds[len-1])-1] != '"')) {
            printf("customshell: unexpected EOF while looking for matching `\"'\n");
        } else if (strcmp(internalCmds[1], "*") == 0) {
            DIR* d;
            struct dirent *dir;
            d = opendir(".");
            if (d) {
                while ((dir = readdir(d)) != NULL) {
                    printf("%s ", dir->d_name);
                }
                closedir(d);
                printf("\n");
            }
            if (len != 2) {
                for (int i = 2; i < len; i++) {
                    for (int j = 0; j < strlen(internalCmds[i]); j++) {
                        if (internalCmds[i][j] != '\"') {
                            putchar(internalCmds[i][j]);
                        }   
                    }
                    printf(" ");
                }
                printf("\n");
            }
        } else if (internalCmds[1][0] == '&') {
            internalCmds[1]++;
            printf("customshell: %s", internalCmds[1]);
            printf(": command not found\n");
        } else if (internalCmds[1][0] == '(' || internalCmds[len-1][strlen(internalCmds[len-1])-1] == ')') {
            printf("customshell: syntax error near unexpected token\n");
        } else if (strcmp(internalCmds[1], "-e") == 0) {
            if (input[0] == '&') {
                input += 11;
            } else {
                input += 8;
            }
            for (int i = 0; i < strlen(input); i++) {
                if (input[i] == '\"') {
                    continue;
                } else if (input[i] == '\\' && input[++i] == 'c') {
                    break;
                } else {
                    printf("%c", input[i]);
                }
            }
            printf("\n");
        } else {
            if (input[0] == '&') {
                input += 8;
            } else {
                input += 5;
            }
            for (int i = 0; i < strlen(input); i++) {
                if (input[i] != '\"') {
                    printf("%c", input[i]);
                }
            }
            printf("\n");
        }
    } else if (strcmp(internalCmds[0], ic[2]) == 0) {
        if (len == 1) {
            printDirectory();
            printf("\n");
        } else {
            if (internalCmds[1][0] == '-') {
                if (strcmp(internalCmds[1], "-P") != 0 && strcmp(internalCmds[1], "-L") != 0) {
                printf("customshell: pwd: %s", internalCmds[1]);
                printf(": invalid option\n");
                printf("pwd: usage: pwd [-LP]\n");
                } else {
                    printDirectory();
                    printf("\n");
                }
            } else if (internalCmds[1][0] == '(' || internalCmds[len-1][strlen(internalCmds[len-1])-1] == ')') {
                printf("customshell: syntax error near unexpected token\n");
            } else {
                printDirectory();
                printf("\n");
            }
        }
    } else if (strcmp(internalCmds[0], ic[3]) == 0) {
        exit(0);
    }
}

void execExternalCmd(char** externalCmds) {
    if (strcmp(externalCmds[0], "mkdir") == 0) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Fork Failed");
            return; 
        } else if (pid == 0) {
            if (execvp("./mkdir", externalCmds) < 0) {
                printf("customshell: command could not be executed\n");
            }
            exit(0);
        } else {
            wait(NULL);
            return;
        }
    } else if (strcmp(externalCmds[0], "ls") == 0) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Fork Failed");
            return; 
        } else if (pid == 0) {
            if (execvp("./ls", externalCmds) < 0) {
                printf("customshell: command could not be executed\n");
            }
            exit(0);
        } else {
            wait(NULL);
            return;
        }
    } else if (strcmp(externalCmds[0], "cat") == 0) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Fork Failed");
            return; 
        } else if (pid == 0) {
            if (execvp("./cat", externalCmds) < 0) {
                printf("customshell: command could not be executed\n");
            }
            exit(0);
        } else {
            wait(NULL);
            return;
        }
    } else if (strcmp(externalCmds[0], "date") == 0) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Fork Failed");
            return; 
        } else if (pid == 0) {
            if (execvp("./date", externalCmds) < 0) {
                printf("customshell: command could not be executed\n");
            }
            exit(0);
        } else {
            wait(NULL);
            return;
        }
    } else if (strcmp(externalCmds[0], "rm") == 0) {
        pid_t pid = fork();
        if (pid < 0) {
            printf("Fork Failed");
            return; 
        } else if (pid == 0) {
            if (execvp("./rm", externalCmds) < 0) {
                printf("customshell: command could not be executed\n");
            }
            exit(0);
        } else {
            wait(NULL);
            return;
        }
    }
}

void* execCmd(void* args) {
    char** cmds = ((char**)args);
    char cmdLine[100] = "./";
    for (int i = 0; i < 100 && cmds[i] != 0; i++) {
        strcat(cmdLine, cmds[i]);
        strcat(cmdLine, " ");
    }
    if (system(cmdLine) != 0) {
        printf("customshell(tbe): command could not be executed\n");
    }
    return NULL;
}

void execExternalCmdThread(char** externalCmdsThreads) {
    pthread_t ptid;
    pthread_create(&ptid, NULL, execCmd, (void*)externalCmdsThreads);
    pthread_join(ptid, NULL);
}

int main() {
    char input[100];
    char echostr[100];
    char* cmds[100];
    char* ic[] = {"cd", "echo", "pwd", "exit"};
    char* ec[] = {"ls", "cat", "date", "rm", "mkdir"};
    printStartInfo();

    while (1) {
        memset(input, 0, 100);
        memset(cmds, 0, 100);
        printf("\n");
        printDirectory();
        if (takeInput(input) == 0) {
            continue;
        }
        strcpy(echostr, input);
        makeInputArray(input, cmds);
        int type = checkTypeOfCommand(cmds, ec, ic);
        if (strcmp(cmds[0], "&t") == 0) {
            char** cmdsThread = cmds;
            cmdsThread++;
            type = checkTypeOfCommand(cmdsThread, ec, ic);
            if (type == 1) {
                execExternalCmdThread(cmdsThread);
            } else if (type == 2) {
                execInternalCmd(cmdsThread, ic, echostr);
            } else {
                printf("customshell: command not found\n");
            }
        } else {
            if (type == 1) {
                execExternalCmd(cmds);
            } else if (type == 2) {
                execInternalCmd(cmds, ic, echostr);
            } else {
                printf("customshell: command not found\n");
            }
        }
    }
    return 0;
}
