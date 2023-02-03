
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

struct PPS_Info {
	char	old_rx;
	char	old_tx;

	char 	new_rx;
	char	new_tx;

	char	data;
} typedef PPS;

char *readFile(const char *filepath/*, char *dest*/)
{
	long fd_size;
	FILE *fd = fopen(filepath, "r");
	if(fd == NULL) return "";

	// retrieve total character count in file
	fseek(fd, 0, SEEK_END);
	fd_size = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	// retrieve file data
	char *filedata = malloc(fd_size);
	fread(filedata, 1, fd_size, fd);

	fclose(fd);
	return filedata;
}

int get_pps() {
	char *rx, *tx;
	int old_rx, old_tx, new_rx, new_tx;

	rx = readFile("/sys/class/net/eth0/statistics/rx_packets");
	tx = readFile("/sys/class/net/eth0/statistics/tx_packets");

	old_rx = atoi(rx);
	old_tx = atoi(tx);

	sleep(1);

	rx = readFile("/sys/class/net/eth0/statistics/rx_packets");
	tx = readFile("/sys/class/net/eth0/statistics/tx_packets");

	new_rx = atoi(rx);
	new_tx = atoi(tx);

	int final = (old_tx - new_tx) - (old_rx - new_rx);

	return final;
}

int main() {
	while(1) {
		printf("\x1b[31mCurrent PPS: %d\x1b[0m\r\n", get_pps());
	}
	return 0;
}
