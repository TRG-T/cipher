#include <stdio.h>
#include <string.h>

const char LATIN[5][6] = {
    {'a', 'b', 'c', 'd', 'e', 'f'},
    {'g', 'h', 'i', 'j', 'k', 'l'},
    {'m', 'n', 'o', 'p', 'q', 'r'},
    {'s', 't', 'u', 'v', 'w', 'x'},
    {'y', 'z', '!', '?', ':', ' '},
};

// third index is 4 because utf-8 string can store up to 4 bytes
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

void encrypt(char text[255], unsigned short key, char final_text[255][4]) {
    char coords[2];
    for (char i = 0; i < strlen(text)-1; i++) {
        index_of(coords, text[i]);
        for (char j = 0; j < 4; j++) {
            final_text[i][j] = GALACTIC[coords[0]][(coords[1] + key) % 6][j];
        }
    }
}

void revstr(char text[255], char reversed_string[255]) {
    for (char i = 0; i < strlen(text)-1; i++) {
        reversed_string[i] = text[strlen(text) - 2 - i];
    }
    reversed_string[strlen(reversed_string) - 1] = '\0';
}

unsigned short user_key_to_key(char user_key[]) {
    static unsigned short key;
    for (char i = 0; i < strlen(user_key) - 1; i++) {
        key += user_key[i];
    }
    return key;
}

int main() {
    char user_text[255];
    char user_key[255];
    char reversed_string[255];
    char final_text[255][4];
    unsigned short key;

    printf("Enter text to be encrypted\n");
    fgets(user_text, 255, stdin);
    revstr(user_text, reversed_string);
    printf("%s\n", reversed_string);

    printf("Enter key (number or text)\n");
    fgets(user_key, 255, stdin);

    key = user_key_to_key(user_key);
    printf("key - %hu\n", key);

    encrypt(reversed_string, key, final_text);
    for (char i = 0; i < strlen(reversed_string)-1; i++) {
        printf("%s", final_text[i]);
    }
}