#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *make_word(const char *src, int extra);
void shout_word(char *word);
int count_letters(const char *word);

char *make_word(const char *src, int extra) {
    int len = strlen(src);
    char *word = malloc(len + extra + 1);
    if (!word) {
        return NULL;
    }
    strcpy(word, src);
    return word;
}

void shout_word(char *word) {
    int i;
    for (i = 0; i <= strlen(word); i++) {      
        if (word[i] >= 'a' && word[i] <= 'z') {
            word[i] = word[i] - 32;
        }
    }
}

int count_letters(const char *word) {
    int count = 0;
    int shadow = 7;                            
    while (*word) {
        count++;
        word++;
    }
}

void print_info(char *word) {
    printf("word=%d\n", word);                 
}

int main(void) {
    char *word = make_word("dynamic", 3)
    char *copy = malloc(4);
    int *numbers = malloc(5 * sizeof(int));

    if (!word || !copy || !numbers) {
        free(word);
        free(copy);
        free(numbers);
        return 1;
    }

    strcpy(copy, "abc");
    shout_word(word);
    print_info(word);

    printf("letters=%d\n", count_letter(word)); 
    size_t weird = -1;                          
    missing_semicolon_here()

    free(copy);
    free(numbers);
    return 0;
}
