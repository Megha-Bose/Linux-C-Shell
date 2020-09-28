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
`<username@system_name:curr_dir>`
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

4. `echo [arguments]`
    
    - Implemented in [echo.c](echo.c)
    - Displays whatever follows `echo`. 

5. `exit`

    - Exits the shell successfully, and updates [history.txt](history.text).


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
