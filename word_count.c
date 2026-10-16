#include <stdio.h>

//Count Each Line Word and Every Character
void word_count(FILE *input)
{
    int character;
    int lines = 0;
    int words = 0;
    int characters = 0;
    int in_word = 0;

    //One char at a time
    while ((character = fgetc(input)) != EOF) {
        characters++;

        if (character == '\n') {
            lines++;
        }

	//Check Whitespace
        if (character == ' ' || character == '\t' ||
            character == '\n' || character == '\r' ||
            character == '\v' || character == '\f') {
            in_word = 0;
        } else if (!in_word) {
            words++;
            in_word = 1;
        }
    }

    printf("Lines: %d Words: %d Characters: %d\n", lines, words, characters);
}

int main(int argc, char *argv[])
{
    FILE *input;

    //Only one File
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return 1;
    }

    //open file
    if (argc == 2) {
        input = fopen(argv[1], "r");

        if (input == NULL) {
            perror(argv[1]);
            return 1;
        }
    } else {
        input = stdin;
    }

    word_count(input);

    if (input != stdin) {
        fclose(input);
    }

    return 0;
}

