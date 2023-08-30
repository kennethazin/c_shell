/*
Name: Kenneth John Ras
Student Number: 21787441
Acknowledgement of the DCU Academic Integrity Policy:
    I understand that the University regards breaches of academic integrity and plagiarism as grave and serious.
    I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the penalties that may be imposed should I engage in practice or practices that breach this policy.
    I have identified and included the source of all facts, ideas, opinions and viewpoints of others in the assignment references. Direct quotations, paraphrasing, discussion of ideas from books, journal articles, internet sources, module text, or any other source whatsoever are acknowledged and the sources cited are identified in the assignment references.
    I declare that this material, which I now submit for assessment, is entirely my own work and has not been taken from the work of others save and to the extent that such work has been cited and acknowledged within the text of my work.
    I have used the DCU library referencing guidelines and/or the appropriate referencing system recommended in the assignment guidelines and/or programme documentation.
*/
#include "myshell.h"

int main(int argc, char **argv) { // main function that takes command-line arguments
    // constants and variables
    const char *prompt = "==> "; // string that is printed before each command
    int shouldRun = 1; // flag that indicates whether program should keep running

    printf("Welcome to Kenneth's shell!\nPress ENTER to start.\n");

    /* checks whether file name is passed as argument when shell is run*/
    FILE *inputStream = stdin;
    if (argc > 1) { // if a filename is passed, open the file and use it as input stream
        inputStream = fopen(argv[1], "r");
        if (inputStream == NULL) { // if file cannot be opened, print an error message and exit with error code
            fprintf(stderr, "Error: could not open file '%s'.\n", argv[1]);
            return 1;
        }
    }

    

    /* main loop of program*/
    // runs as long as 'shouldRun' is true and 'fgets()' reads line of input from stream successfully
    // each line of input is stored in 'buffer'
    // tokenizes input line into seperate arguments
    char buffer[MAX_BUFFER];
    while (shouldRun && fgets(buffer, MAX_BUFFER, inputStream)) {
        // Tokenize input line into separate arguments
        char *args[MAX_ARGS];
        char *token = strtok(buffer, SEPARATORS);
        int argCount = 0;
        while (token != NULL && argCount < MAX_ARGS) {
            args[argCount++] = token;
            token = strtok(NULL, SEPARATORS);
        }
        args[argCount] = NULL;

        // Check if the user's input matches a predefined command
        if (argCount > 0) {
            char *inputFile = NULL;
            char *outputFile = NULL;

            // Check for input and output redirection
            for (int i = 0; args[i] != NULL; i++) {
                if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0) {
                    outputFile = args[i];
                    args[i] = NULL;
                } else if (strcmp(args[i], "<") == 0) {
                    inputFile = args[i + 1];
                    args[i] = NULL;
                    args[i + 1] = NULL;
                    i++;
                }
            }

            if (strcmp(args[0], "cd") == 0) {
                // Change directory command
                cd(args[1]);
            } else if (strcmp(args[0], "clr") == 0) {
                // Clear screen command
                clr();
            } else if (strcmp(args[0], "dir") == 0) {
                // List directory contents command
                dir(args[1]);
            } else if (strcmp(args[0], "environ") == 0) {
                // Print environment variables command
                env();
            } else if (strcmp(args[0], "echo") == 0) {
                // Print arguments command
                char echoString[MAX_BUFFER] = "";
                for (int i = 1; i < argCount; i++) {
                    strcat(echoString, args[i]);
                    strcat(echoString, " ");
                }
                echo(echoString);
            } else if (strcmp(args[0], "help") == 0) {
                // Output shell manual to user
                help();
            } else if (strcmp(args[0], "pause") == 0) {
                // Pause command
                pauseShell();
            } else if (strcmp(args[0], "quit") == 0) {
                // Quit command
                shouldRun = 0;
            } else if (strcmp(args[0], "batchmode") == 0) {
                // batchmode 
                if (argCount >= 2) {
                    batchmode(args[1], outputFile);
                } else {
                    fprintf(stderr, "Error: batchmode requires a filename argument.\n");
                }
            } else {
                // if the user's input does not match any predefined commands, print an error
                fprintf(stderr, "Error: command '%s' not recognized.\n", args[0]);
            }

            // Handle input and output redirection
            if (inputFile != NULL) {
                freopen(inputFile, "r", stdin);
            }

            if (outputFile != NULL) {
                if (strcmp(outputFile, ">") == 0) {
                    freopen(args[argCount - 1], "w", stdout);
                } else if (strcmp(outputFile, ">>") == 0) {
                    freopen(args[argCount - 1], "a", stdout);
                }
            }
        }

        // print prompt if reading stdin
        if (inputStream == stdin) {
            printf("%s", prompt);
            fflush(stdout);
        }
    }

    // close opened files before exiting
    if (inputStream != stdin) {
        fclose(inputStream);
    }

    return 0;
}


// say hello