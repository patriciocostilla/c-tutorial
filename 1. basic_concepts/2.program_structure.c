// Preprocessor commands
#include <stdio.h>

// Function definitions, you can't call a function without defining it first
void say_hello();

// Program entrypoint
int main() {
    say_hello();
    return 0;
}

// Functions implementations
void say_hello(){
    printf("Hello World!\n");
}