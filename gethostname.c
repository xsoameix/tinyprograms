#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>

void
server_listen(int port) {
}

int
main(void) {
  char name[20 + 1] = {0};
  int ret = gethostname(name, sizeof(name) - 1);
  printf("name %s, %d\n", name, ret);
  //char name[] = "google.com";
  struct hostent * host = gethostbyname(name);
  if (!host) return -1;
  if (host->h_addrtype == AF_INET) {
    puts("addr type AF_INET");
  } else if (host->h_addrtype == AF_INET6) {
    puts("addr type AF_INET6");
  }
  printf("official name %s\n", host->h_name);
  printf("address length %d bytes\n", host->h_length);
  printf("host name alias\n");
  int i = 0;
  for (; host->h_aliases[i]; i++) {
    printf("%s\n", host->h_aliases[i]);
  }
  printf("\naddress list\n");
  i = 0;
  for (; host->h_addr_list[i]; i++) {
    printf("connect to %s ... ",
           inet_ntoa(*((struct in_addr *) host->h_addr_list[i])));
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr = *((struct in_addr *) host->h_addr_list[i]);
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
      puts("socket error");
      break;
    }
    int ret = connect(sockfd, (struct sockaddr *) &addr,
                      sizeof(struct sockaddr));
    if (ret == -1) {
      puts("connect error");
      break;
    }
    puts("success");
  }
  return 0;
}
