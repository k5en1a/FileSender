#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
 
void write_file(int sockfd, char* folder){
  int n;
  FILE *fp;
  char path[100];
  char *filename = "recv.txt";

  strcat(path, folder);
  strcat(path, filename);
  char buffer[SIZE];
 
  fp = fopen(path, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    bzero(buffer, SIZE);
  }
  return;
}
 
int main(){
  char *ip = "127.0.0.1";
  int port;
  int e;
  char folder[50]="";

  printf("Enter port number (e.g. 8080): ");
  scanf("%d", &port);
  printf("Server port: %d", port);

  printf("Enter full path for recieved file: ");
  scanf("%s", folder);
  printf("Path for recieved file: ", folder);
 
  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");
 
  if(listen(sockfd, 10) == 0){
    printf("[+]Listening....\n");
  }else{
    perror("[-]Error in listening");
    exit(1);
  }
 
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  write_file(new_sock, folder);
  printf("[+]Data written in the file successfully.\n");
 
  return 0;
}