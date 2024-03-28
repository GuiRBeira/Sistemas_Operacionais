#include <unistd.h>
#include <string.h>

void myprintf(int x, int y, char* msg) {
    // Calcula o tamanho da mensagem
    int size = strlen(msg);
    
    // Calcula as posições do cursor no console
    char cursorPos[16]; // Para garantir espaço suficiente para os números e os caracteres de escape
    sprintf(cursorPos, "\033[%d;%dH", y, x); // Monta a sequência de escape para definir a posição do cursor
    
    // Escreve a sequência de escape para mover o cursor para a posição desejada
    write(STDOUT_FILENO, cursorPos, strlen(cursorPos));
    
    // Escreve a mensagem na posição especificada
    write(STDOUT_FILENO, msg, size);
}

int main() {
    myprintf(1, 3, "Olá");
    return 0;
}
