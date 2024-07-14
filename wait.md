// funcion de waitpid

    while ((data->pid = wait(&status)) > 0) //$?
    {
        if (WIFEXITED(status))
            data->status = WEXITSTATUS(status);
    }

Reference: https://linux.die.net/man/2/waitpid

The wait() system call suspends execution of the calling process until one of its children terminates. The call wait(&status) is equivalent to:

waitpid(-1, &status, 0);

The waitpid() system call suspends execution of the calling process until a child specified by pid argument has changed state. By default, waitpid() waits only for terminated children, but this behavior is modifiable via the options argument, as described below.

The value of pid can be:

< -1
meaning wait for any child process whose process group ID is equal to the absolute value of pid.

-1

meaning wait for any child process.

0

meaning wait for any child process whose process group ID is equal to that of the calling process.

> 0

meaning wait for the child whose process ID is equal to the value of pid.

If status is not NULL, wait() and waitpid() store status information in the int to which it points. This integer can be inspected with the following macros (which take the integer itself as an argument, not a pointer to it, as is done in wait() and waitpid()!):

WIFEXITED(status)
returns true if the child terminated normally, that is, by calling exit(3) or _exit(2), or by returning from main().

WEXITSTATUS(status)
returns the exit status of the child. This consists of the least significant 8 bits of the status argument that the child specified in a call to exit(3) or _exit(2) or as the argument for a return statement in main(). This macro should only be employed if WIFEXITED returned true.

WIFSIGNALED(status)
returns true if the child process was terminated by a signal.

WTERMSIG(status)
returns the number of the signal that caused the child process to terminate. This macro should only be employed if WIFSIGNALED returned true.