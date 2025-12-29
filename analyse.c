    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <string.h>
    #include <errno.h>
    #include <ctype.h>

    #define BUF_SIZE 1024


    /*
    * @author AnastasisDrougas - it2024023.
    * @date 29/12/2025.
    */


    void file_checking(int argc, char*argv[]);

    int extract_data(int fd);


    int main(int argc, char *argv[]){

        //Check if the file structure.
        file_checking(argc, argv);

        //Open file.
        int fd = open(argv[1],O_RDONLY);
        if(fd == -1){
            perror("Error opening file!");
            return 1;
        }

        return extract_data(fd);

        close(fd);
    }


    void file_checking(int argc, char*argv[]){

        //Check if there is files given by the user.
        if(argc < 2){
            printf("\nNo files given!\nUsage: %s <YourLogFile>\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        //Check if the file is a log file.
        if(strlen(argv[1]) >= 4 && strcmp(argv[1] + strlen(argv[1]) - 4, ".log") == 0){
            printf("\nCorrect File type..\n");
        }else{
            printf("\nIncorrect file type..\nUsage: %s <YourLogFile>\n",argv[0]);
            exit(EXIT_FAILURE);
        }
    }


    int extract_data(int fd){
        
        char buf[BUF_SIZE];
        char line[BUF_SIZE];
        int line_index = 0;
        ssize_t bytes_read;
        int total_lines = 0;
        int total_errors = 0;
        int total_digits = 0;

        while((bytes_read = read(fd, buf, BUF_SIZE)) > 0){
            //Read each character.
            for(ssize_t i = 0; i < bytes_read; i++){
                //If '\n', new line. 
                if(buf[i] == '\n'){
                    //For this line:
                    line[line_index] = '\0'; 

                    total_lines++;

                    //Check if the line contains any ERRORS, increase Counter.
                    if(strstr(line, "ERROR") != NULL)
                        total_errors++;

                    //Check if the line contains any digis, increase Counter.
                    for(int j = 0; j < line_index; j++) {
                        if(isdigit(line[j])) {
                            total_digits++;
                        }
                    }
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
                total_lines++;
                if(strstr(line, "ERROR") != NULL)
                    total_errors++;
                for(int j = 0; j < line_index; j++) {
                    if(isdigit(line[j])) {
                        total_digits++;
                        break;
                    }
                }
            }

        //Check if the file is empty.
        if(total_lines == 0){
            printf("\nSorry,the file you privided is empty!");
            return 2;
        }else{
            printf("\nThis is the data we extracted:\n");
            printf("Total Lines: %d\nTotal Errors: %d\nTotal Digits: %d\n",total_lines, total_errors, total_digits);
            return 0;
        }
    }