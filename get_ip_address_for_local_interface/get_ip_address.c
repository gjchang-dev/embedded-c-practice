#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int get_ipv4_address(const char *ifname,
                     char *ip,
                     size_t ip_size)
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (fd < 0)
        return -1;

    struct ifreq ifr = {0};

    strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
    ifr.ifr_addr.sa_family = AF_INET;

    if (ioctl(fd, SIOCGIFADDR, &ifr) < 0) {
        close(fd);
        return -1;
    }

    struct sockaddr_in *addr =
        (struct sockaddr_in *)&ifr.ifr_addr;

    const char *result = inet_ntop(
        AF_INET,
        &addr->sin_addr,
        ip,
        ip_size
    );

    close(fd);

    return result ? 0 : -1;
}


int main(int argc, char *argv[])
{
    if (argc != 2) {
        return -1;
    }

    const char *ifname = argv[1];
    char ip[INET_ADDRSTRLEN] = {0};

    if (get_ipv4_address(ifname, ip, sizeof(ip)) == 0) {
        printf("IP address of %s: %s\n", ifname, ip);
        return 0;
    } else {
        printf("Failed to get IP address for interface: %s\n", ifname);
        return -1;
    }
}