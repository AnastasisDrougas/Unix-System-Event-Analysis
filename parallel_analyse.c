#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <pthread.h>

#define BUF_SIZE 1024


/*
* @author AnastasisDrougas - it2024023.
* @date 2/1/2026.
*/


//Struct given to each thread
typedef struct {
    char filename[256];
}thread_arg_t;

//Struct extracted from each thread
typedef struct{
    char filename[256];
    int total_lines;
    int total_errors;
    int total_digits;
}results_t;


void file_checking(int argc, char*argv[]);

void* file_thread_handling(void*arg); 

void extract_data(int fd, results_t *res, char *filename);

void print_data(int file_number, pthread_t threads[]);


int main(int argc, char *argv[]){

    //Check the file structure.
    file_checking(argc, argv);

    //Handle multiple files with threads:
    int file_number = argc-1;
    pthread_t threads[file_number];
    thread_arg_t thread_args[file_number];

    //Create Threads
    for(int i = 0; i < file_number; i++){
        //Extract filename.
        strcpy(thread_args[i].filename, argv[i+1]);
        //Create.
        pthread_create(&threads[i], NULL, file_thread_handling, &thread_args[i]);
    }
    //Print all data extracted.
    print_data(file_number, threads);

    return 0;
}


void file_checking(int argc, char *argv[]){

    //Check if there is files given by the user.
    if(argc < 2){
        printf("\nNo files given!\nUsage: %s <YourLogFile>\n", argv[0]);
        printf("-------------------------------------------\n\n");
        exit(EXIT_FAILURE);
    }
    //Check if all the files are .log file.
    for(int i = 1; i < argc; i++){
        if(strlen(argv[i]) >= 4 && strcmp(argv[i] + strlen(argv[i]) - 4, ".log") == 0){
        printf("<%s> Correct File type..\n",argv[i]);
        }else{
            printf("Incorrect file type..\nFile %s is not a '.log' file!\n",argv[i]);
            printf("-------------------------------------------\n\n");
            exit(EXIT_FAILURE);
        }
    }
    
}

void extract_data(int fd, results_t *res, char *filename){

    strcpy(res->filename, filename);

    char buf[BUF_SIZE];
    char line[BUF_SIZE];
    int line_index = 0;
    ssize_t bytes_read;

    res->total_lines = 0;
    res->total_errors = 0;
    res->total_digits = 0;
   

    while((bytes_read = read(fd, buf, BUF_SIZE)) > 0){
        //Read each character.
        for(ssize_t i = 0; i < bytes_read; i++){
            //If '\n', new line. 
            if(buf[i] == '\n'){
                //For this line:
                line[line_index] = '\0'; 

                res->total_lines++;

                //Check if the line contains any ERRORS, increase Counter.
                if(strstr(line, "ERROR") != NULL)
                    res->total_errors++;
                
                line_index = 0; //Reset line.
            }else{
                if(line_index < BUF_SIZE -1){
                    line[line_index++] = buf[i];
                }
            }
        }
    }
    //If the file doesn't end with '\n'.
    if(line_index > 0) {
        line[line_index] = '\0';
        res->total_lines++;
        if(strstr(line, "ERROR") != NULL)
            res->total_errors++;
    }
    //Close file.
    close(fd);
}

void* file_thread_handling(void*arg){ //Thread function.

    //Typecast args to thread_arg_t.
    thread_arg_t *targ = (thread_arg_t *)arg;
    
    //Extract filename.
    char *filename = targ->filename;

    //Open file.
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror(filename);
        pthread_exit(NULL);
    }

    //Alloc mem for then results.
    results_t *res = malloc(sizeof(results_t));
    if(!res){close(fd);pthread_exit(NULL);}

    extract_data(fd, res, filename); 
   
    //Return struct to main.
    pthread_exit(res);
}

void print_data(int file_number, pthread_t threads[]){
    putchar('\n');
    int total_lines = 0;
    int total_errors = 0;

    for(int i = 0; i < file_number; i++){
        results_t *res;
        pthread_join(threads[i], (void**)&res); //Get the pointer from the thread.

        if(res){ //Can be NULL
            printf("File: %s | Lines: %d | Errors: %d\n",
            res->filename, res->total_lines, res->total_errors);

            total_lines += res->total_lines;
            total_errors += res->total_errors;

            free(res); //Free mem allocated by res.
        }
    }
    putchar('\n');
    printf("TOTAL LINES: %d\n", total_lines);
    printf("TOTAL ERRORS: %d\n", total_errors);
}