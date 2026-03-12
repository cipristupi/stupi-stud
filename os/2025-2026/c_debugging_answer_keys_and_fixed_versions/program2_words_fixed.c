#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *make_word(const char *src, int extra);
void shout_word(char *word);
int count_letters(const char *word);
void print_info(const char *word);

char *make_word(const char *src, int extra) {
    size_t len = strlen(src);
    char *word = malloc(len + (size_t)extra + 1);
    if (!word) {
        return NULL;
    }
    strcpy(word, src);
    return word;
}

void shout_word(char *word) {
    size_t len = strlen(word);
    for (size_t i = 0; i < len; i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            word[i] = (char)(word[i] - ('a' - 'A'));
        }
    }
}

int count_letters(const char *word) {
    int count = 0;
    while (*word) {
        count++;
        word++;
    }
    return count;
}

void print_info(const char *word) {
    printf("word=%s\n", word);
}

int main(void) {
    char *word = make_word("dynamic", 3);
    char *copy = malloc(4);
    int *numbers = malloc(5 * sizeof(int));

    if (!word || !copy || !numbers) {
        free(word);
        free(copy);
        free(numbers);
        return 1;
    }

    strcpy(copy, "abc");
    for (int i = 0; i < 5; i++) {
        numbers[i] = i;
    }

    shout_word(word);
    print_info(word);
    printf("letters=%d\n", count_letters(word));
    printf("copy=%s first_number=%d\n", copy, numbers[0]);

    free(word);
    free(copy);
    free(numbers);
    return 0;
}
