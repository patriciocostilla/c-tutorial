#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    // Definir dirección destino
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    server.sin_addr.s_addr = inet_addr("172.217.162.4");

    int addrLen = sizeof(server);

    // Definir socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Conectar socket
    printf("Conectando el socket\n");
    int conn = connect(sock, (struct sockaddr *)&server, addrLen);
    if (conn != 0)
    {
        printf("La conexión falló\n");
        return 0;
    }
    printf("La conexión fue exitosa\n");

    // Generar mensaje
    char payload[] = "HEAD / HTTP/1.1\r\n";
    printf("%ld\n", sizeof(payload));

    // Enviar mensaje
    int wasSend = send(sock, payload, sizeof(payload), 0);
    if (wasSend == -1)
    {
        printf("No se envió ningún mensaje\n");
        return 0;
    }
    printf("El mensaje se envió exitosamente\n");

    // Esperar respuesta
    int recvLen = 0x800;
    char *recvBuffer = (char *)malloc(recvLen);
    memset(recvBuffer, 0x00, recvLen);
    printf("Recibiendo\n");
    int res = recv(sock, recvBuffer, recvLen, 0);
    if (res == -1)
    {
        printf("La recepción falló\n");
        return 0;
    }

    // Mostrar respuesta
    recvBuffer[recvLen] = '\0';
    printf("%s\n", recvBuffer);
    printf("Saliendo\n");
    close(sock);
    return 0;
}