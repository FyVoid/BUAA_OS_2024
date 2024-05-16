#include "../../fs/serv.h"
#include <lib.h>

int main() {
	fs_init();
	char buffer[256];
	int fd_num = open("/newmotd", O_RDWR);
	int bytes;
	if (fork() == 0) {
		bytes = read(fd_num, buffer, 8);
		debugf("child buffer: %s\n", buffer);
	} else {
		bytes = read(fd_num, buffer, 8);
		debugf("father buffer: %s\n", buffer);
	}
}
