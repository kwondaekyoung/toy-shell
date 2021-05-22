# toy-shell
+ "Computer Architecture and Real-Time Operationg System" First project
+ OS version : Ubuntu Linux 18.04
##command
> all of these command can run after compiling
'''
gcc shell.c
./a.out
'''


+ [exit] : exit code
	+ with exit command you can exit own shell and move on terminal
	+ (additional function that wait 3 seconds for exit shell)
```
exit
```
+ [cd] : cd code
	+ help for change directories
```
cd .           ->change to present directory
cd ..          ->change to upper directory
cd a           ->change to directory a 
```
+ [clear] :clear code
	+ help for clear own shell
```
write (1, "\033[1;1H\033[2J",10);
```
+ [mkdir] : mkdir code
	+ help for make new directory
```
mkdir a         ->make directory 'a' in present position
```
+ [rmdir] : rmdir code
	+ help for remove existing directory
```
(if directory 'a' present)
rmdir           ->remove directory 'a' which in present position
```
+ [ls] : ls code
	+ show list in present directory
```
ls
```
+ [pwd] : pwd code
	+ show present address
```
pwd
```
+ [help]
	+ show help manual(all of command that added)
```
help
```
+ [cat] : cat code
	+ show code that in present directory
```
cat          ->show all of code (c. py cpp)
```
+ [info]
	+ first with student_ID.c
	+ you have to compile student_ID.c with command
	+ and you can see student_ID with command 'info'
	+ these method is same with using  make file...
```
gcc -0 info student_ID.c
gcc shell.c
./a.out
```

```
	info
```

