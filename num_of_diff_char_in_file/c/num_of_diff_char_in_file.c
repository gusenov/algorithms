#include <stdio.h>
#include <stdlib.h>

int main() {
    int character;
    int counter[256];
    
    for (character = 0; character < 256; character++) {  // for all 256 characters do
        counter[character] = 0;                          //     assign zero to the counter
    }                                                    // end for
    
    while ((character = getchar()) != EOF) {  // while there are more characters in the file do
                                              //    get the next character
        counter[character]++;                 //    increment the counter for this character by one
    }                                         // end while
    
    for (character = 0; character < 256; character++) {
        if (counter[character] > 0) {
            printf("%d; %d; '%c'\n", counter[character], character, character);
        }
    }
    
    return EXIT_SUCCESS;
}
