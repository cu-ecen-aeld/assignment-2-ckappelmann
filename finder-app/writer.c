#include <stdio.h>
#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define TAG "WRITER"

int main(int argc, char**argv)
{
    openlog(TAG,0, LOG_USER);
    if(argc != 3) {
        syslog(LOG_ERR, "Exactly two arguements expected");
        return 1;
    }

    const char * writefile = argv[1];
    const char * writestr = argv[2];

    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0) {
        syslog(LOG_ERR, "Failed to open file: %s", writefile);
        return 1;
    }

    int count = write(fd, writestr, strlen(writestr));
    if(count == -1) {
        int err = errno;
        syslog(LOG_ERR, "Failed to write file: %d", err);
        return 1;
    }
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    close(fd);
}
