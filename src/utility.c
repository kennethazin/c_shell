/**
* Acknowledgement of the DCU Academic Integrity Policy:
* I understand that the University regards breaches of academic integrity and plagiarism as grave and serious.
* I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the penalties that may be imposed should I engage in practice or practices that breach this policy.
* I have identified and included the source of all facts, ideas, opinions and viewpoints of others in the assignment references. Direct quotations, paraphrasing, discussion of ideas from books, journal articles, internet sources, module text, or any other source whatsoever are acknowledged and the sources cited are identified in the assignment references.
* I declare that this material, which I now submit for assessment, is entirely my own work and has not been taken from the work of others save and to the extent that such work has been cited and acknowledged within the text of my work.
* I have used the DCU library referencing guidelines and/or the appropriate referencing system recommended in the assignment guidelines and/or programme documentation.
*
* Kenneth John Ras, 21787441 - Operating Systems Project 1
* ca216/myshell
**/

#include "myshell.h"

void cd(char *directory) {
    if (directory == NULL) {
        fprintf(stderr, "cd: expected argument to directory\n");
    } else {
        if (chdir(directory) != 0) {
            perror("cd failed");
        }
    }
}

void clr() {
    system("clear");
}

void dir(char *directory) {
    if (directory == NULL) {
        system("ls");
    } else {
        char command[1024];
        sprintf(command, "ls %s", directory);
        system(command);
    }
}

void env() {
    extern char **environ;
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}

void echo(char *string) {
    if (string == NULL) {
        fprintf(stderr, "echo: expected argument to string\n");
    } else {
        printf("%s\n", string);
    }
}

int help() {
    char line[MAX_BUFFER];
    int lineCount = 0;
    int displayMessage = 0;

    FILE *file = fopen("../manual/readme.md", "r");
    if (file == NULL) {
        printf("Unable to open file\n");
        return 1;
    }

    while (fgets(line, MAX_BUFFER, file)) {
        lineCount++;

        if (lineCount <= LINES_PER_PAGE) {
            printf("%s", line);
        } else {
            if (!displayMessage) {
                printf("\nPress enter to continue...");
                displayMessage = 1;
            }

            getchar();
            printf("%s", line);
            lineCount = 1;
        }
    }

    fclose(file);
    return 0;
}

void pauseShell() {
    printf("Program has been paused. Press ENTER to continue...\n");
    while (getchar() != '\n');
}

void quit() {
    exit(EXIT_SUCCESS);
}
void commands(char *args[], char *outputFile) {
    int pid = fork();
    // checks if fork failed
    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);
    // child process
    } else if (pid == 0) {
        // if there is an output file
        if (outputFile != NULL) {
            if (strcmp(outputFile, ">") == 0) {
                // redirect stdout to output file
                freopen(args[1], "w", stdout);
            } else if (strcmp(outputFile, ">>") == 0) {
                freopen(args[1], "a", stdout);
            }
        }
        // the command args
        execvp(args[0], args);
        // if execvp fails
        fprintf(stderr, "Command '%s' not found\n", args[0]);
        exit(EXIT_FAILURE);
    // parent process
    } else {
        // check if the last argument is the ampersand character
        int background = 0; // determines if parent process should wait for child process or not. if true, command should not be executes, else executre in background.
        int argCount = 0;
        // count no. of args
        while (args[argCount] != NULL) {
            argCount++;
        }
        // if last arg is ampersand character
        if (argCount > 0 && strcmp(args[argCount - 1], "&") == 0) {
            // "1" flag indicates background executoin
            background = 1;
            args[argCount - 1] = NULL; // Remove the ampersand character from args
        }

        // if background is false, wait for child process to finish
        if (!background) {  
            wait(NULL);
        }
    }
}


void batchmode(char const *file, char *outputFile) {
    // open and read file
    FILE *fptr = fopen(file, "r");
    if (fptr == NULL) {
        printf("Error: Failed to open the file '%s'\n", file);
        return;
    }
    
    // read each line in file
    char line[MAX_BUFFER];
    while (fgets(line, MAX_BUFFER, fptr)) {
        // tokenise lines into args
        char *args[MAX_ARGS];
        int argCount = 0;

        char *token = strtok(line, SEPARATORS);
        while (token != NULL && argCount < MAX_ARGS - 1) {
            args[argCount++] = token;
            token = strtok(NULL, SEPARATORS);
        }
        args[argCount] = NULL;

        // if there are arguments, execute commands
        if (argCount > 0) {
            commands(args, outputFile);
        }
    }

    fclose(fptr);
}
