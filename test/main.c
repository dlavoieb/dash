#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int file_flags = O_WRONLY | O_CREAT | O_TRUNC;
    int permission_flags = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    char* output = "redirect.txt";
    close(1);
    
    open(output, file_flags, permission_flags);

    printf("A simple program output.\n");
    return 0;
}