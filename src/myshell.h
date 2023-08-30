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

// Includes 
#include <stdio.h> // input output library
#include <stdlib.h> // for memory allocation
#include <string.h> // string manipulation
#include <unistd.h> // system calls and process management
#include <sys/types.h> // provides system definitions
#include <sys/wait.h> // functions for waiting for child processes to complete

// Global variables
#define MAX_BUFFER 1024                        // maxmimum size of input buffer
#define MAX_ARGS 200                           // maximum no. of command-line arghuments that can be passed
#define SEPARATORS " \t\n"                     // string of characters that separtate arguments (e.g. spaces, tabs and newlines)
#define LINES_PER_PAGE 20


// Function prototypes for built-in shell commands

void cd(char *directory); // change current working directory
void clr(); // clear screen
void dir(char *directory); // list contents of a directory
void env(); // print environment variables
void echo(char *string); // print a string to stdout
int help(); // show manual
void pauseShell(); // pause shell until user presses enter
void quit(); // exit the shell
void commands(char *args[], char *outputFile); // executes command. takes file name and output file as arg for i/o redirection
void batchmode(char const *file, char *outputFile); // executes commands on each line after reading lines on cmd line
