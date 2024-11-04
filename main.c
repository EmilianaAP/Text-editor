#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char input[50];
    printf("Please enter the path to the file you would like to open or create: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character from input
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') input[len - 1] = '\0';

    FILE *file = fopen(input, "a+");
    if (file == NULL) {
        printf("Error opening or creating file!\n");
        return -1;
    }

    printf("+-------------------------------------------------------------+\n");
    printf("| File: %-40s Ln 1, Col 1 |\n", input);
    printf("+-------------------------------------------------------------+\n");

    char line[100];
    int line_number = 1;
    char command[10];

    while (1) {
        rewind(file);  // Move to the beginning to read
        printf("File contents:\n");

        while (fgets(line, sizeof(line), file)) {
            printf("| %d | %s", line_number++, line);
        }

        printf("| %d | ", line_number);
        char new_content[100];
        fgets(new_content, sizeof(new_content), stdin);

        printf("+-------------------------------------------------------------+\n");
        printf("| Commands: :save = Save | :quit = Quit | :find = Find        |\n");
        printf("+-------------------------------------------------------------+\n\n");

        new_content[strcspn(new_content, "\n")] = '\0';

        if (strcmp(new_content, ":save") == 0) {
            fseek(file, 0, SEEK_END);
            printf("File saved.\n");
        } else if (strcmp(new_content, ":quit") == 0) {
            printf("Quitting...\n");
            break;
        } else if (strlen(new_content) > 0) {
            fseek(file, 0, SEEK_END);
            fputs(new_content, file);
            fputs("\n", file);
            printf("Content appended to file.\n");
            line_number++;
        } else {
            printf("No new content added.\n");
        }
    }

    fclose(file);
    return 0;
}