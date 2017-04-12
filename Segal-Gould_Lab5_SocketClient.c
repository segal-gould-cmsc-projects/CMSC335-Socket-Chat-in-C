//Noah Segal-Gould
//Prof. K. Salehin
//Computer Networks
//9 April 2017

//Lab 5: Socket Client
//To compile, run: gcc -o Segal-Gould_Lab5_SocketClient Segal-Gould_Lab5_SocketClient.c
//To run, type: ./Segal-Gould_Lab5_SocketClient 10.0.0.1 1234

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define QUIT "QUIT\n"

int main(int argc, char **argv) {

    if (argc != 3) {
        printf("\n*****INVALID ARGUMENTS*****\n");
        return 0;
    }

    printf("Starting socket Client with port %s, and address %s.\n", argv[2], argv[1]);

    int port = atoi(argv[2]); // Convert the port to an integer.
    int sockfd;
    char *address = argv[1]; // Grab the IP address from the user input.
    char buff[100]; // String for keeping track of time.
    char sendline[100]; // String being sent to the Server.
    char recvline[100]; // String being received by the Client.
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port); // Connect to the provided port.
    inet_pton(AF_INET, address, &(servaddr.sin_addr));
    connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    while (strcmp(recvline, QUIT) != 0) {
        bzero(sendline, 100);
        bzero(recvline, 100);
        time_t first = time(0); // Get the time before user input.
        strftime(buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&first)); // Format the time as a String.
        printf("Client [%s]: ", buff); // Print the initial time for the message being sent.
        fgets(sendline, 100, stdin); // Wait for user input for message to send.
        time_t second = time(0); // Get the time after input.
        strftime(buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&second)); // Format the time as a String.
        printf("\nMessage sent at %s\n", buff); // Print the corrected time the message was input.
        write(sockfd, sendline, strlen(sendline) + 1);
        read(sockfd, recvline, 100);
        time_t third = time(0); // Get the time after Server response.
        strftime(buff, 100, "%Y-%m-%d %H:%M:%S", localtime(&third)); // Format the time as a String.
        printf("Server [%s]: %s\n", buff, recvline); // Print the message being received and the time.
    }
    printf("\n*****QUITTING PROGRAM*****\n");
    return 0;
}
