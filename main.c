#include <stdio.h>
#include <string.h>

#include "msg.h"
#include "shell.h"

#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

extern int udp_simple(int argc, char **argv);
extern int udp_delay(int argc, char **argv);
extern int udp_client(int argc, char **argv);

static const shell_command_t shell_commands[] = {
        { "udps", "simple udp echo server", udp_simple},
        { "udpd", "simple udp echo server with 1s delay", udp_delay},
        { "client", "udp client that sends and receives messages", udp_client},
        { NULL, NULL, NULL }
};

int main(void)
{
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    puts("Type help, or simply type udps to start an echo server, udpd to start an echo server");
    puts("with 1s delay, or client to start a udp client that prints the responses");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
