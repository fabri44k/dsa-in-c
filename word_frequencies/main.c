/**
 * Given a text file, this program uses an hash table to store all words and
 * their frequency in the input file.
 * DICT: [WORD] -> FREQUECY OF WORD IN THE ENTIRE FILE.
 * The scope is testing the hash table.
 */

#include "hash_table.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR_FOR_WORD 30

void process_word(HashTable *ht, char *word) {

    int count = get_item(ht, word);

    if (count == -1) {

        insert(ht, word, 1);
        return;
    }

    insert(ht, word, count + 1);
}

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr,
                "Error: Usage: ./word_frequency_counter <input_file.txt>\n");
        return 1;
    }

    char *file_path = argv[1];

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error when opening input file: %s\n", file_path);
        return 1;
    }

    printf("Calculating word frequencies in the input file: %s...\n",
           file_path);

    int ch;

    int i = 0;

    char word[MAX_CHAR_FOR_WORD];

    HashTable ht;
    create(&ht, 100);

    while ((ch = fgetc(fp)) != EOF) {

        if (isalpha(ch)) {

            if (i < MAX_CHAR_FOR_WORD - 1) {
                word[i] = tolower(ch);
                i++;
            }

        } else {

            if (i > 0) {

                word[i] = 0;
                process_word(&ht, word);
                i = 0;
            }
        }
    }

    // in case of a file without newline
    if (i > 0) {
        word[i] = 0;
        process_word(&ht, word);
    }

    printf("\nEnd of processing input file.\n");

    printf("\nPrinting results: \n");
    print(&ht);
    destroy(&ht);

    fclose(fp);
    return 0;
}
