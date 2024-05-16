#include "../../fs/serv.h"
#include <lib.h>

int main() {
	char buffer[256];
	int fd_num = open("/newmotd", O_RDONLY);
	int bytes;
	debugf("opened\n");
	if (fork() == 0) {
		debugf("child\n");
		bytes = read(fd_num, buffer, 8);
		debugf("child buffer: %s\n", buffer);
	} else {
		debugf("parent\n");
		bytes = read(fd_num, buffer, 8);
		debugf("parent buffer: %s\n", buffer);
	}
}
