# myCShell - Linux Shell in C


## About

This is an implementation of a Linux shell in C language.


## Run the shell

1. Execute the following in the directory that contains the source files:
    ```
    $ make
    $ ./run
    ```

## Display

- On executing the code, a shell prompt of the following form appears along with it.
`[exit code] <username@system_name:curr_dir>`
where `[exit code]` is `:')` if last command exited successfully and `:'(` if the exit was unsuccessful.
- The directory from which the ​shell is invoked will be the home directory of the shell and is indicated by `~`. 
- If the user executes `cd` i.e., change dir, then the corresponding change is reflected in the shell as well.
- If the current working directory is the directory from which your shell is invoked, then on executing command `cd ..`, 
the shell displays the absolute path of the current directory from the root.


## Source Files Organisation

- Modular
- The commands are implemented in separate `.c` files.
- The shell is called from the main function in [main.c](main.c).
- Common header files are included, functions and global variables are declared in the [headers.h](headers.h) file.


## Supported commands

### Built-in commands

- Builtin commands are contained within the shell itself. When the name of a builtin command is used as the 
first word of a simple command, the shell executes the command directly without invoking another program. 
- Builtin commands are necessary to implement functionality impossible or inconvenient to obtain with separate utilities.
- Built-in commands have been defined and implemented.

1. `pwd`

    - Implemented in [pwd.c](pwd.c)
    - Displays the name of the working directory.

2. `ls [-l -a] [directory]`

    - Implemented in [ls.c](ls.c)
    - Lists all the files and directories in the specified directory in alphabetical order.
    - Variations such as `ls, ls . , ls ..` also work.
    - Accepts multiple directories as arguments. eg. `ls -la dir1 dir2 dir3`.
    - Highlights directories in blue and executable files in green.

3. `cd [file]`
    - Implemented in [cd.c](cd.c)
    - Changes directory to the directory specified, throws an error if the directory does not exist.
    - It supports `cd .`, `cd ..`, `cd -` too.

4. `echo [arguments]`
    
    - Implemented in [echo.c](echo.c)
    - Displays whatever follows `echo`. 

5. `exit` and `quit`

    - Exits the shell successfully, and updates [hist.txt](hist.txt).

6.  `setenv var[value]` & `unset var`

    - Implemented in [set_unset_env.c](set_unset_env.c)
    - Creates an environment variable var if it doesn't already exist and assigns it the value given
    - `unset var` destroys that environment variable

7.  `jobs`

    - Implemented in [jobs.c](jobs.c)
    - Prints a list of all currently running jobs with their pid in the order of their creation.
    - Gives the state of the job – Running, Sleeping, Stopped or Defunct.

8.  `kjob <jobNumber> <signalNumber>`

    - Implemented in [kjob.c](kjob.c)
    - Takes the job number of a running job and sends the signal corresponding to ​signal number​ to that process.

9. `fg <jobNumber>`

    - Implemented in [fg.c](fg.c)
    - Brings a running or a stopped background job with given job number to foreground.

10. `bg <jobNumber>`

    - Implemented in [bg.c](bg.c)
    - Changes a stopped background job to a running background job.

11. `overkill`

    - Implemented in [overkill.c](overkill.c)
    - Kills all background process at once.

### Foreground and Background Processes

- To run a process in the background, enter the command followed by `&` symbol. Eg. `emacs &`.
- Upon termination of a background process, the shell prints its PID and exit status.


### More Commands

1. `pinfo [PID]`

    - Implemented in [pinfo.c](pinfo.c)
    - Prints process status, memory and executable path.
    - `pinfo` with no arguments gives details of the shell itself.

2. `history [n]`

    - Implemented in [history.c](history.c) 
    - Lists the last [n] commands. If `n` is not specified, it displays the last 10 commands.
    - Retains the `history` even upon exit. 
    - Stores last 20 commands in [hist.txt](hist.text).

3. `nightswatch -n [seconds] [newborn/interrupt]`

    - Implemented in [nightswatch.c](nightswatch.c)
    - `night_interrupt` function prints the number of times CPU has been interrupted by the keyboard.
    The number of interrupts has been taken to be on line 2 of /proc/interrupts.
    - `night_newborn` function prints the PID of the process that is most recently created on the system.
    - `n` specifies the number of seconds after which the interrupt or newborn process is watched, as applicable. 
    Here, `n` is taken as an input from the user.
    - Takes input only in the specified format.
    - Terminates when `q` is pressed.

### Additional Features

1. `​CTRL-Z`

    - Changes the status of currently running job to stop, and pushes it to the background.

2. `CTRL-C`

    - Sends SIGINT signal to the current foreground job​.
    - If there is no foreground job, then the signal does not have any effect on the shell.

3. Input-Output Redirection & Piping

    - Handles `<`, `>`, `>>`, and `|` operators appropriately, wherever they are in the command.
