#include <stdio.h>
#include "net/sock/udp.h"
#include "xtimer.h"


uint8_t buf[128];

int udp_simple(void)
{
    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_udp_t sock;
    local.port = 12345;
    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("Error creating UDP sock");
        return 1;
    }
    while (1) {
        sock_udp_ep_t remote;
        ssize_t res;
        if ((res = sock_udp_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT,
                                 &remote)) >= 0) {
            puts("Received a message");
            if (sock_udp_send(&sock, buf, res, &remote) < 0) {
                puts("Error sending reply");
            }
        }
    }
    return 0;
}

int udp_delay(void)
{
    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_udp_t sock;
    local.port = 12345;
    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("Error creating UDP sock");
        return 1;
    }
    while (1) {
        sock_udp_ep_t remote;
        ssize_t res;
        if ((res = sock_udp_recv(&sock, buf, sizeof(buf), SOCK_NO_TIMEOUT,
                                 &remote)) >= 0) {
            printf("Received message: \"");
            for (int i = 0; i < res; i++) {
                printf("%c", buf[i]);
            }
            printf("\" at time %d    ",xtimer_now_usec());
            //Puts 1 second delay before sending the message
            xtimer_sleep(1);
            if (sock_udp_send(&sock, buf, res, &remote) < 0) {
                puts("Error sending reply");
            } else {
                printf("Sent reply at time %d \n", xtimer_now_usec());
            }
        }
    }
    return 0;
}



