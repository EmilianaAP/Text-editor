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

    // Open file in "a+" mode (read from start, append to end, create if not exists)
    FILE *file = fopen(input, "a+");
    if (file == NULL) {
        printf("Error opening or creating file!\n");
        return -1;
    }

    // Display file info
    printf("+-------------------------------------------------------------+\n");
    printf("| File: %-40s Ln 10, Col 5 |\n", input);
    printf("+-------------------------------------------------------------+\n");

    // Read and display existing content
    printf("Existing file contents:\n");
    rewind(file);  // Move to the beginning for reading
    char line[100];
    int line_number = 1;
    while (fgets(line, sizeof(line), file)) {
        printf("| %d | %s", line_number++, line);  // Display line number and content
    }

    // Adding new content to the file
    printf("\nEnter text to append to the file (or press ENTER to skip): ");
    char new_content[100];
    fgets(new_content, sizeof(new_content), stdin);
    if (strlen(new_content) > 1) {  // If input is not just newline
        fseek(file, 0, SEEK_END);  // Move to end of file to append
        fputs(new_content, file);
        printf("Content appended to file.\n");
    } else {
        printf("No new content added.\n");
    }

    fclose(file);  // Close the file
    return 0;
}
