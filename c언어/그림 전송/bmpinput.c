#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 2048

typedef struct {
    int socket_fd;
    int id;
    struct sockaddr_in address;
} client_info_t;

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    int opt = 1;
    char buffer[BUFFER_SIZE];
    client_info_t client;

    // 소켓 생성
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 소켓 옵션 설정
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // 주소 설정
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 바인드
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 연결 대기
    if (listen(server_fd, 1) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("서버가 %d 포트에서 대기 중입니다...\n", PORT);

    // 클라이언트 연결 수락
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 클라이언트 정보 설정
    client.socket_fd = new_socket;
    client.id = 1;
    client.address = address;

    printf("[클라이언트 %d] 연결되었습니다. IP: %s, Port: %d\n",
           client.id, inet_ntoa(client.address.sin_addr), ntohs(client.address.sin_port));

    // 파일 전송
    FILE *file_in = fopen("blackbuck.bmp", "rb");
    if (file_in == NULL) {
        perror("파일 열기 실패");
        close(new_socket);
        close(server_fd);
        return EXIT_FAILURE;
    }

    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file_in)) > 0) {
        ssize_t bytes_sent = send(client.socket_fd, buffer, bytes_read, 0);
        if (bytes_sent < 0) {
            perror("파일 전송 실패");
            break;
        }
    }

    printf("파일 전송 완료.\n");

    fclose(file_in);
    close(new_socket);
    close(server_fd);

    return 0;
}

