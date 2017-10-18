/***************************************************************************************************************************************
Using permission bits of a linux configuration file to secretly share message between two processes.*****************************
An example of a covert channel attack*****************************************************************
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

void main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: channel [message]\n");
        return;
    }
    if (argv[1][5] != '\0') {
        printf("Message should be 5 cahracters long\n"); // message to secretly share
        return;
    }
    // going to use the ./bash_history file, a hidden file.
    //The last bit of the permissiosn will be changed to the
    //bit of the message wished to be communicated
    char* user = getlogin(); // current user name
    int user_length = 0; //length of current user name
    for(;user[user_length] != '\0';user_length++);
    // /home/user/.bash_history ----> target file
    char path[user_length+21]; // path of target file
    int i;
    char* temp_path = "/home/";
    for (i = 0; i < 6; i++)
        path[i] = temp_path[i];
    temp_path = user;
    for(; i < 6 + user_length ;i++)
        path[i] = user[i-6];
    temp_path = "/.bash_history";
    for(; i < user_length + 21; i++)
        path[i] = temp_path[i-13];
    path[i] = '\0';

    // we need to obtain current permission for this file
    // we use stat to get file stats
    struct stat filestats;  
    stat(path, &filestats);
    int orig_fileperm = filestats.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
    //printf("chmod: %o\n", orig_fileperm);
    
    int fileperm, hidden_message;
    
    // now , fork!
    //creating second process
    int pid = fork();
    for (i = 0; i < 5; i++) { // we'll be passing 5 bits
        if (pid == 0) { // child
            sleep(1); // let parent write message
            stat(path, &filestats);
            hidden_message = filestats.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO) & 1; //check first bit
            printf("output: bit %d is %d\n", i, hidden_message);
        }
        if (pid != 0) { // parent
            if (argv[1][i] == '1') {
                fileperm = orig_fileperm | 1 << 0; // set world execute bit (zeroth bit)
                hidden_message = 1;
            }
            else {
                fileperm = orig_fileperm & ~(1 << 0); // clear bit 0
                hidden_message = 0;
            }
            printf("input: bit %d is %d\n", i, hidden_message);
            chmod(path, fileperm); // toggle world execution bit. if its zero, message is zero. else 1.
            sleep(1); // let child read it
        }
    }
    
    if (pid != 0) {
        chmod(path, orig_fileperm); // set original permissions back
        // printf("chmod: %o\n", fileperm);
    }
}
