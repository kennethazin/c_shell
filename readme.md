# myshell                 USER MANUAL

### NAME
    myshell

### SYNOPSIS
    myshell [command_string | file]

### DESCRIPTION
    A user friendly command interpreter used to run various commands and programs from standard input or from a file.

### USAGE
    Invoke myshell without any arguments to run the program.
    Once shell is invoked, enter commands into prompt for execution.


### SHELL COMMANDS
The following commands are supported by myshell:

Change current working directory
- `cd(char *directory)`    
Clear the Screen
- `clr()`
List contents of a directory
- `dir(char *directory)`
Print a string to stdout       
- `echo(char *string)`
Show manual
- `help()`
Pause shell until the user presses Enter.
- `pause()`
Print environment variables.
- `env()`
Exit the shell.
`quit()`

### I/O REDIRECTION
    I/O redirection is is a feature of the shell that allows you to change the input and output of a command.

    Input and output redirection can be achieved using special characters <, > or >>.

    INPUT REDIRECTION
        To redirected the input (stdin) of a command from a file, use the < operator.

    OUTPUT REDIRECTION
        To redirect the output (stdout) of a command to a file, use the > operator.
        outputfile is created if it does not exist and truncated if it does.

        Use >> operator to create outputfile if it does not exist and append if it does.


AUTHOR
    Kenneth John Ras

REFERENCES
    Running a Command in the Background | Linux Shell | InformIT (2023). Available at: https://www.informit.com/articles/article.aspx?p=2854374&seqNum=6 (Accessed: 4 July 2023).

    Stephen, B. (2015) ‘Tutorial- Write a Shell in C’, 16 January. Available at: https://brennan.io/2015/01/16/write-a-shell-in-c/ (Accessed: 12 July 2023).

    Newham, C. (2005) Learning the bash Shell: Unix Shell Programming. O’Reilly Media, Inc.

ANTI-PLAGIARISM POLICY
    Name: Kenneth John Ras
    Student Number: 21787441
    Acknowledgement of the DCU Academic Integrity Policy:
        I understand that the University regards breaches of academic integrity and plagiarism as grave and serious.
        I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the penalties that may be imposed should I engage in practice or practices that breach this policy.
        I have identified and included the source of all facts, ideas, opinions and viewpoints of others in the assignment references. Direct quotations, paraphrasing, discussion of ideas from books, journal articles, internet sources, module text, or any other source whatsoever are acknowledged and the sources cited are identified in the assignment references.
        I declare that this material, which I now submit for assessment, is entirely my own work and has not been taken from the work of others save and to the extent that such work has been cited and acknowledged within the text of my work.
        I have used the DCU library referencing guidelines and/or the appropriate referencing system recommended in the assignment guidelines and/or programme documentation.

