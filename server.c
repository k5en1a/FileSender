#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024
 
void write_file(int sockfd, char* targetFile){
  int n;
  FILE *fp;
//  char path[100];
//  char *filename = "recv.txt";
 
  char buffer[SIZE];
 
  fp = fopen(targetFile, "w");
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
 
int main(int argc, char* argv[]){
  if (argc != 3){
    printf("Usage: server [port] [targetFilePath]\n"
    "for example\n"
    "./server 8080 ./recievedFile\n");
    return 1;
  }
  char *ip = "127.0.0.1";
  int port = atoi(argv[1]);
  int e;
  char *tartetFile = argv[2];

  printf("[+]Server will start on port %d\n", port);
  printf("[+]Target file: %s\n", tartetFile);

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
  write_file(new_sock, tartetFile);
  printf("[+]Data written in the file successfully.\n");
 
  return 0;
}