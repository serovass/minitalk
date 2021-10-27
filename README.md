# minitalk
A small data exchange program using UNIX signals

The following functions are allowed to use:
```
write,
sigemptyset,
sigaddset,
sigaction,
kill,
getpid,
malloc,
free,
pause,
usleep,
exit
```
  
Only two signals `SIGUSR1` and `SIGUSR2` are allowed

The server confirms every signal received by sending a signal to the client.

------------------------------------------------------------------------------------
The server must be launched first, and after being launched it must display its PID.

The client will take as parameters: the server PID, the string that should be sent.

```
$>make
$>./server
$>./client [the server PID] [the string that should be sent]
```
