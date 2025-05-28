#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"  // 서버 IP 주소
#define PORT 8080              // 서버 포트
#define BUFFER_SIZE 2048

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];

    // 소켓 생성
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("소켓 생성 실패");
        return EXIT_FAILURE;
    }

    // 서버 주소 설정
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // IP 주소 변환
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("잘못된 주소 / 주소 변환 실패");
        return EXIT_FAILURE;
    }

    // 서버에 연결
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("서버 연결 실패");
        return EXIT_FAILURE;
    }

    printf("서버에 연결되었습니다. 파일을 수신 중...\n");

    // 파일 열기
    FILE *file_out = fopen("get.bmp", "wb");
    if (file_out == NULL) {
        perror("파일 열기 실패");
        close(sock);
        return EXIT_FAILURE;
    }

    // 수신 루프
    ssize_t bytes_received;
    while ((bytes_received = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, file_out);
    }

    if (bytes_received < 0) {
        perror("데이터 수신 오류");
    } else {
        printf("파일 수신 완료.\n");
    }

    fclose(file_out);
    close(sock);

    return 0;
}

