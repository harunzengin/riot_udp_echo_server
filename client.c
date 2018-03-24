#include <stdio.h>

#include "xtimer.h"
#include "net/af.h"
#include "net/protnum.h"
#include "net/ipv6/addr.h"
#include "xtimer.h"
#include "net/sock/udp.h"

uint8_t buffer[128];

int udp_client(int argc, char **argv)
{
	if(argc != 2){
		puts("Usage client <message>");
		return -1;
	}

	char * message = argv[1];

    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_udp_t sock;
    local.port = 0xabcd;
    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("Error creating UDP sock");
        return 1;
    }

    while (1) {
        sock_udp_ep_t remote = { .family = AF_INET6 };
        ssize_t res;
        remote.port = 12345;
        ipv6_addr_set_all_nodes_multicast((ipv6_addr_t *)&remote.addr.ipv6,
                                          IPV6_ADDR_MCAST_SCP_LINK_LOCAL);
        if (sock_udp_send(&sock, message, sizeof(message), &remote) < 0) {
            puts("Error sending message");
            sock_udp_close(&sock);
            return 1;
        }
        // Wait for 2 seconds for the message to be replied
        if ((res = sock_udp_recv(&sock, buffer, sizeof(buffer), 2 * US_PER_SEC,
                                NULL)) < 0) {
            if (res == -ETIMEDOUT) {
                puts("Timed out");
            }
            else {
                puts("Error receiving message");
            }
        }
        else {
            printf("Received message: \"");
            for (int i = 0; i < res; i++) {
                printf("%c", buffer[i]);
            }
            printf("\"\n");
        }
        xtimer_sleep(1);
    }
    return 0;
}
