#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *student_info = "Мирин Алексей Александрович ККСО-26-24 1 курс";
    
    // Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Ошибка создания сокета \n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Преобразование IP адреса
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nНеверный адрес/ Адрес не поддерживается \n");
        return -1;
    }
    
    // Подключение к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nОшибка подключения \n");
        return -1;
    }
    
    // Отправка данных серверу
    send(sock, student_info, strlen(student_info), 0);
    printf("Информация о студенте отправлена на сервер\n");
    
    close(sock);
    return 0;
}
