
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Print only lines that are unique from previous line
void unique_lines(FILE *input)
{
    char *current = NULL;
    char *previous = NULL;
    size_t current_capacity = 0;
    size_t previous_capacity = 0;
    ssize_t length;
    char *temp;
    size_t temp_capacity;

    // Read one line at a time
    while ((length = getline(&current, &current_capacity, input)) != -1) {

        // Print the line if first time seen since last line
        if (previous == NULL || strcmp(current, previous) != 0) {
            fputs(current, stdout);
        }

        // Swap the buffers so the current line becomes the previous line
        temp = previous;
        previous = current;
        current = temp;

        temp_capacity = previous_capacity;
        previous_capacity = current_capacity;
        current_capacity = temp_capacity;
    }

    // Release the buffers
    free(current);
    free(previous);
}

int main(int argc, char *argv[])
{
    FILE *input;

    // Accept one file
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return 1;
    }

    // Open file
    if (argc == 2) {
        input = fopen(argv[1], "r");

        if (input == NULL) {
            perror(argv[1]);
            return 1;
        }
    } else {
        input = stdin;
    }

    unique_lines(input);

    if (input != stdin) {
        fclose(input);
    }

    return 0;
}

