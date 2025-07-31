#include <stdio.h> // For handling input and output
#include <stdlib.h> // For handling memory
#include <string.h> // For handling strings

void str_slice(char *str, const char *substr) {
    char *match; // Initialize a pointer to hold the result of strstr()

    /*
    The strstr() function finds the first occurrence of a substring inside a larger string and returns a pointer to that occurrence.
    If the substring is not found, strstr() returns NULL.
    In this statement, we assign match to be the pointer to the substring if one is found, and NULL if it's not.
    The value of match is then compared to NULL, and the loop repeats until match is NULL.
    */
    while ((match = strstr(str, substr)) != NULL) { // While substr is found in str
        /*
        The memmove() function copies a block of memory from a source to a destination.
        In this line, the function takes match as the place it's copying memory to (because match points to the location of the substring, which means we can rewrite the string at that location to exclude the substring),
        match + strlen(substr) as the place it's copying memory from (uses pointer addition to get the string excluding the substring),
        andstrlen(match + strlen(substr)) + 1 as the amount of bytes to copy (gets the length of the string after the substring + the null terminator)
        */
       memmove(match, match + strlen(substr), strlen(match + strlen(substr)) + 1);
    }
}

int parse_equation(char *equation) {
    str_slice(equation, " "); // Remove the substring from the string (this function updates the original string so we can just call it)
    printf("%s\n", equation); // Print the result to see if it worked
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