#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char SYMBOL[4];

const char LATIN[5][6] = {
    {'a', 'b', 'c', 'd', 'e', 'f'},
    {'g', 'h', 'i', 'j', 'k', 'l'},
    {'m', 'n', 'o', 'p', 'q', 'r'},
    {'s', 't', 'u', 'v', 'w', 'x'},
    {'y', 'z', '!', '?', ':', ' '},
};

// third index is 4 because utf-8 string can store up to 3 bytes + null terminator
const char GALACTIC[5][6][4] = {
    {"ᔑ", "ʖ", "ᓵ", "↸", "Ŀ", "⎓"},
    {"ㅓ", "〒", "╎", "፧", "ꖌ", "ꖎ"},
    {"ᒲ", "リ", "フ", "¡", "ᑑ", "።"},
    {"ነ", "ﬧ", "⚍", "⍊", "∴", "/"},
    {"॥", "Λ", "ʗ", "˨", "ᚴ", "ᚌ"},
};

void index_of(char coords[2], char letter) {
    for (char i = 0; i < 5; i++) {
        for (char j = 0; j < 6; j++) {
            if (letter == LATIN[i][j]) {
                coords[0] = i;
                coords[1] = j;
            }
        }
    }
}

void encrypt(char *text, unsigned short key, SYMBOL (*final_text)) {
    char coords[2];
    for (unsigned int i = 0; i < strlen(text); i++) {
        index_of(coords, text[i]);
        for (unsigned int j = 0; j < 4; j++) {
            final_text[i][j] = GALACTIC[coords[0]][(coords[1] + key) % 6][j];
        }
    }
}

void revstr(char *text, char reversed_string[255]) {
    for (unsigned int i = 0; i < strlen(text); i++) {
        reversed_string[i] = text[strlen(text) - 1 - i];
    }
}

unsigned short user_key_to_key(char user_key[20]) {
    static unsigned short key;
    for (char i = 0; i < strlen(user_key) - 1; i++) {
        key += user_key[i];
    }
    return key;
}

int main() {
    unsigned int len = 16;
    unsigned int spare_size = 16;

    char *user_text = malloc(len);
    char user_key[20];
    unsigned short key;

    printf("Enter text to be encrypted\n");

    if (user_text != NULL) {
        int i = 0;
        int c;
        while (( c = getchar() ) != '\n' && c != EOF ) {
            user_text[i] = c;
            if (++i == spare_size) {
                spare_size = i + len;
                user_text = realloc(user_text, spare_size);
            }
        }
        user_text[spare_size] = '\0';
    }

    char *reversed_string = malloc(spare_size);
    SYMBOL *final_text = malloc(spare_size * sizeof(SYMBOL));

    revstr(user_text, reversed_string);
    printf("%s\n", reversed_string);

    printf("Enter key (number or text, only first 18 characters will be used)\n");
    fgets(user_key, sizeof(user_key), stdin);
    key = user_key_to_key(user_key);
    printf("key - %hu\n", key);

    encrypt(reversed_string, key, final_text);
    for (unsigned int i = 0; i < strlen(reversed_string); i++) {
        printf("%s", final_text[i]);
    }
}
