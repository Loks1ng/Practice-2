#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    // Создание сокета
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Ошибка создания сокета");
        exit(EXIT_FAILURE);
    }
    
    // Настройка сокета
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Ошибка настройки сокета");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Привязка сокета к порту
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Ошибка привязки сокета");
        exit(EXIT_FAILURE);
    }
    
    // Ожидание подключений
    if (listen(server_fd, 3) < 0) {
        perror("Ошибка ожидания подключений");
        exit(EXIT_FAILURE);
    }
    
    printf("Сервер ожидает подключений на порту %d...\n", PORT);
    
    // Принятие подключения
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Ошибка принятия подключения");
        exit(EXIT_FAILURE);
    }
    
    // Чтение данных от клиента
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Получена информация о студенте: %s\n", buffer);
    
    close(new_socket);
    close(server_fd);
    printf("Сервер завершил работу\n");
    return 0;
}
