#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void create_file_with_hole(void)
{
    int fd = open("file.hole", O_WRONLY|O_TRUNC|O_CREAT, 0600);
    write(fd, "Hello", 5);
    lseek(fd, 99988, SEEK_CUR);
    write(fd, "Goodbye", 7);
    close(fd);
}

void create_file_without_hole(void)
{
    int fd = open("file.nohole", O_WRONLY|O_TRUNC|O_CREAT, 0600);
    write(fd, "Hello", 5);
    char buf[99988];
    memset(buf, 'a', 99988);
    write(fd, buf, 99988);
    write(fd, "Goodbye", 7);
    close(fd);
}

void create_zero_file(void)
{
    int fd = open("zero.file", O_WRONLY|O_TRUNC|O_CREAT, 0600);
    char buf[100000];
    memset(buf, '\0', 100000);
    write(fd, buf, 100000);
    close(fd);
}

int main()
{
    create_file_with_hole();
    create_file_without_hole();
    create_zero_file();
    return 0;
}
