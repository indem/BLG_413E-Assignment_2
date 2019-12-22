#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SET_NICE_INC 355
#define GET_NICE_INC 356

int main(int argc, char* argv[]){
    if (argc < 2 || argc > 4){
        printf("Invalid number of arguments.\n");
        exit(1);
    }
    int parent, child1, child2, grandchild1, grandchild2,
        parent_inc = atoi(argv[1]), new_parent = 0, new_parent_inc;
    char* info_string = "[%s] - pid: %d parent: %d nice: %d nice_inc: %d\n";
    parent = getpid();

    if (argc == 4){
        new_parent = atoi(argv[2]);
        new_parent_inc = atoi(argv[3]);
        printf("parent %d\n", parent);
        printf("parent_inc %d\n", parent_inc);
        printf("new_parent %d\n", new_parent);
        printf("new parent_inc %d\n", new_parent_inc);
    }

    printf(info_string, "PARENT", parent, getppid(), nice(0), syscall(GET_NICE_INC, getpid()));
    child1 = fork();

    if (child1 == 0){
        printf(info_string, "CHILD 1", getppid(), getpid(), nice(0), syscall(GET_NICE_INC, getpid()));
        exit(0);
    }
    
    syscall(SET_NICE_INC, parent, parent_inc);
    printf(info_string, "PARENT", parent, getppid(), nice(0), syscall(GET_NICE_INC, getpid()));

    child2 = fork();

    if (child2 == 0) { // runnning process is child
        printf(info_string, "CHILD 2", getpid(), getppid(), nice(0), syscall(GET_NICE_INC, getpid()));
        grandchild1 = fork();
        
        if (grandchild1 == 0){
            printf(info_string, "GRANDCHILD 1", getpid(), getppid(), nice(0), syscall(GET_NICE_INC, getpid()));
            sleep(6);
            printf(info_string, "GRANDCHILD 1", getpid(), getppid(), nice(0), syscall(GET_NICE_INC, getpid()));
            sleep(7);
            exit(0);
        }
        else {
            grandchild2 = fork();
        }
        if (grandchild2 == 0){
            printf(info_string, "GRANDCHILD 2", getpid(), getppid(), nice(0), syscall(GET_NICE_INC, getpid()));
            sleep(6);
            printf(info_string, "GRANDCHILD 2", getpid(), getppid(), nice(0), syscall(GET_NICE_INC, getpid()));
            sleep(7);
            exit(0);    
        }
        sleep(6);
        printf("\n");
        printf(info_string, "CHILD 2", getpid(), getppid(), nice(0), syscall(GET_NICE_INC, getpid()));
        sleep(6);
    }    
    else { // running process is parent
        sleep(5);
        printf("[PARENT] - Dies.\n");
        if (new_parent != 0){
            printf("New parent passed. pid: %d nice_inc: %ld\n", new_parent, syscall(GET_NICE_INC, new_parent));
            syscall(SET_NICE_INC, new_parent, new_parent_inc);
            printf("New parent updated. pid: %d nice_inc: %ld\n", new_parent, syscall(GET_NICE_INC, new_parent));
        }
        printf("exitting...\n");           
        exit(0);
    }
    return 0;
}