#include <stdio.h>

void vulnerable_function(char *input) {
    char buffer[64];
    strcpy(buffer, input);
    printf("%s", buffer);
}

int main(void) {
    char small_buffer[4] = "This";
    char *long_string = "This string is definitely longer than 64 characters and will overflow the buffer.";
    small_buffer[4] = 'X'; 
    small_buffer[5] = 'Y';

    printf("small_buffer: %s\n", small_buffer);
    vulnerable_function(long_string);

    printf("Escaping: arr[0] = %d\n", arr[0]);
    
    return 0;
}
