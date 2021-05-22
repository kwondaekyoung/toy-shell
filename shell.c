#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#define MAX_LEN_LINE    100
#define LEN_HOSTNAME	30

void init_shell(){
    printf("\n\x1b[36m#########################################\x1b[0m");
    printf("\n\n\n\t######KWON SHELL#######");
    printf("\n\n\n\n\x1b[36m#########################################\x1b[0m");
    char* username = getenv("USER");
    printf("\n\n\n");
    char hostname[LEN_HOSTNAME + 1];
    memset(hostname, 0x00, sizeof(hostname));
    printf("username: %s\n", getpwuid(getuid())->pw_name);

    gethostname(hostname, LEN_HOSTNAME);
    printf("hostname: %s\n", hostname);

    sleep(1);
    }

void openHelp()
{
    printf("\n\t\x1b[32m HELP manual(just for help command)\n"
        "command list:\n"
        ">>>cd\n"
	">>>exit\n"
	">>>help\t(same with this manual)\n"
        ">>>ls\n"
	">>>mkdir\n"
	">>>clear\n"
	">>>pwd\n"
	">>>cat\n"
	">>>rmdir\n\x1b[0m"
	);
}

int main(void)
{
    char *arg;
    char *arg2;
    char command[MAX_LEN_LINE];
    char *args[] = {command, arg, arg2, NULL};
    int ret, status;

    pid_t pid, cpid;
    init_shell();
    
    while (true) {
        char *s;
        int len;
	printf("\n>>>");
        
        s = fgets(command, MAX_LEN_LINE, stdin);
        if (s == NULL) {
            fprintf(stderr, "fgets failed\n");
            exit(1);
        }
        
        len = strlen(command);
        printf("%d\n", len);
        if (command[len - 1] == '\n') {
            command[len - 1] = '\0'; 
        }
        
        printf("[%s]\n", command);

	arg = strtok(command," ");

	if(strcmp(command,"exit")==0){
		printf("\x1b[31m\nfinish kwon shell\n\x1b[0m");
		for(int t=3;t>0;t--){	
			if(t==0){
				break;
				}	
			printf("\x1b[31m wait %d seconds\n\x1b[0m",t);
			sleep(1);
		}
		break;
	}
	
	if(strcmp(command,"cd")==0){
		arg = strtok(NULL, " ");
			if(chdir(arg)<0){
				printf("ERROR : No such Directory [%s].\n",arg);
				continue;
			}	
			else{
				printf("Change Directory [%s].\n",arg);
				continue;
			}
	}

	if(strcmp(command,"clear")==0){
		arg = strtok(NULL, " ");
		write (1, "\033[1;1H\033[2J",10);
	}
      
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } 
        if (pid != 0) {  /* parent */
            cpid = waitpid(pid, &status, 0);
            if (cpid != pid) {
                fprintf(stderr, "waitpid failed\n");        
            }

	    printf("Child process terminated\n");
            if (WIFEXITED(status)) {
                printf("Exit status is %d\n", WEXITSTATUS(status)); 
            }
        }
        else {  /* child */
		if(strcmp(command,"mkdir")==0){
			arg = strtok(NULL, " ");
			args[0] ="/bin/mkdir";
			args[1] = arg;
			arg2 = strtok(NULL, " ");
			args[2] = arg2;
		}
		else if(strcmp(command,"rmdir")==0){
			arg = strtok(NULL, " ");
			args[0] ="/bin/rmdir";
			args[1] = arg;
			arg2 = strtok(NULL, " ");
			args[2] = arg2;
		}
		else if(strcmp(command,"ls")==0){
			arg = strtok(NULL, " ");
			args[0] ="/bin/ls";
			args[1] = arg;
		}
		else if(strcmp(command,"pwd")==0){
			arg = strtok(NULL, " ");
			args[0] ="/bin/pwd";
			args[1] = arg;
		}
		else if(strcmp(command,"help")==0){
			openHelp();
		}

		else if(strcmp(command,"cat")==0){
			arg = strtok(NULL, " ");
			args[0] ="/bin/cat";
			args[1] = arg;
			arg2 = strtok(NULL, " ");
			args[2] = arg2;
		}
            
	    ret = execve(args[0], args, NULL);
            	if (ret < 0) {
                	fprintf(stderr, "execve failed\n");   
                	return 1;
            	}
        } 
    }
    return 0;
}
