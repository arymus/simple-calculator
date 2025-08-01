#include <stdio.h> // For handling input and output
#include <stdlib.h> // For handling memory
#include <string.h> // For handling strings
#include <ctype.h> // For handling chars

char (*str_split(const char *str, const char *substr))[256] { // Function that returns a pointer to a 256-byte buffer
    static char arr[10][256]; // Static 2-dimensional array to hold char arrays and stays available all throughout execution
    int count = 0; // Variable to track the amount of substrings stored

    char *str_copy = malloc(strlen(str) + 1); // Allocate the same amount of memory as the string
    if (str_copy == NULL) return NULL; // If str_copy is NULL return NULL because malloc() failed
    strcpy(str_copy, str); // Copy the contents of str to str_copy

    char *token; // Pointer to store the result of strstr() (NULL if no match)
    char *rest = str_copy; // Pointer to update str_copy every time a substring is found

    while ((token = strstr(rest, substr)) != NULL && count < 10) {
        int len = token - rest; // Get the length of the substring (pointer subtraction)
        if (len >= 256) len = 255; // Cap the length at 255 if it exceeds 256 so we have space for the null terminator
        strncpy(arr[count], rest, len); 
        arr[count][len] = '\0';  // Append a null terminator at the end of the string
        count++; // Increase count by 1
        rest = token + strlen(substr); // Update rest to be the rest of the string excluding the substring itself
    }

    // If rest is true (not empty or null-terminator) and the substring count is less than 10
    if (*rest && count < 10) {
        strncpy(arr[count], rest, 255); // Copy 255 bytes of content from rest to arr[count]
        arr[count][256] = '\0'; // Append a null terminator at the end of the string
        count++; // Increase count by 1
    }

    free(str_copy); // Free str_copy from the memory
    return arr; // Return a pointer to the first 256-byte buffer in the array
}

void str_slice(char *str, const char *substr) {
    char *match; // Initialize a pointer to hold the result of strstr()

    // While substr is found in str
    while ((match = strstr(str, substr)) != NULL) {
        /*
        The memmove() function copies a block of memory from a source to a destination.
        In this line, the function takes match as the place it's copying memory to (because match points to the location of the substring, which means we can rewrite the string at that location to exclude the substring),
        match + strlen(substr) as the place it's copying memory from (uses pointer addition to get the string excluding the substring),
        andstrlen(match + strlen(substr)) + 1 as the amount of bytes to copy (gets the length of the string after the substring + the null terminator)
        */
       memmove(match, match + strlen(substr), strlen(match + strlen(substr)) + 1); // Move the substring out of the string
    }
}

int parse_equation(char *equation) {
    str_slice(equation, " "); // Remove the substring from the string (this function updates the original string so we can just call it)
    printf("%s\n", equation); // Print the result to see if it worked

    char (*numbers)[256] = str_split(equation, "+"); // Initialize a pointer to a 256-byte buffer

    for (int i = 0; i < 10 && numbers[i][0] != '\0'; i++) {
        printf("%s\n", numbers[i]); // Print the item
    }
}

int main() {
    printf("Simple Calculator!\n");

    char *equation = malloc(256); // Allocate 256 bytes of memory, *equation points to the first character    
    char *equation_copy = malloc(256); // Allocate memory the same size as equation (256)
    if (equation == NULL || equation_copy == NULL) return 1; // // If equation/equation_copy is NULL, the malloc() failed. Returning 1 indicates an error
    
    printf("Equation: ");
    fgets(equation, 256, stdin); // Get 256 bytes of standard input and write it to equation
    str_slice(equation, "\n"); // Remove newlines from the equation
    parse_equation(equation);
    
    strcpy(equation_copy, equation); // Copy the contents of equation to equation_copy
    printf("Original: %s, copy: %s", equation, equation_copy); // Print out the equation after the user's input is written to it
    return 0; // Return 0, indicating success
}