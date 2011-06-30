#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void readlock(int fd) {
        struct flock fl;
        fl.l_type = F_RDLCK;
        fl.l_whence = SEEK_SET;
        fl.l_start = 0;
        fl.l_len = 0;
        fl.l_pid = getpid();
        fcntl(fd, F_SETLKW, &fl);
}

void writelock(int fd) {
        struct flock fl;
        fl.l_type = F_WRLCK;
        fl.l_whence = SEEK_SET;
        fl.l_start = 0;
        fl.l_len = 0;
        fl.l_pid = getpid();
        fcntl(fd, F_SETLKW, &fl);
}

void unlock(int fd) {
        struct flock fl;
        fl.l_type = F_UNLCK;
        fl.l_whence = SEEK_SET;
        fl.l_start = 0;
        fl.l_len = 0;
        fl.l_pid = getpid();
        fcntl(fd, F_SETLK, &fl);
}

long long gettimeofday_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 1000000 * tv.tv_sec + tv.tv_usec;
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR|O_CREAT);
    FILE *file = fdopen(fd, "r+");
    if (file == NULL) {
        printf("Unable to open file\n");
        return 1;
    }

    printf("Starting loop...\n"); 

    int i;
    unsigned long long counter;
    //long long start_time = gettimeofday_us();
    //while ((gettimeofday_us() - start_time) < 10000000) {
    while (1) {
        writelock(fd);
        rewind(file);
        int items_read = fscanf(file, "%llu", &counter);
        if (items_read < 1)
            counter = 0;
        rewind(file);
        fprintf(file, "%llu", counter + 1);
        fflush(file);
        unlock(fd);
    }
    printf("Done\n");
    fclose(file);
    return 0;
}
