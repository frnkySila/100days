#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct substring_occurence
{
    int start_index;
    char* substring;
    size_t substring_length;
} substring_occurence;

int compare_substring_occurences(const void* one, const void* another)
{
    return ((substring_occurence*)one)->start_index - ((substring_occurence*)another)->start_index;
}

int main()
{
    int n;

    scanf("%d", &n);

    /*
     * A 5MB array can't be expected to be successfully allocated on the stack, so allocate it in heap
     */
    substring_occurence* occurences = malloc(sizeof(substring_occurence) * 1000000);
    size_t num_occurences = 0;

    char* substring_buf = malloc(sizeof(char) * 1000001);

    for(int i = 0; i < n; i++) {
        int k;

        scanf("%s %d", substring_buf, &k);

        size_t substring_length = strlen(substring_buf);

        for(int j = 0; j < k; j++) {
            int start_index;

            scanf("%d", &start_index);

            occurences[num_occurences].start_index = start_index - 1; // Make indices zero-based
            occurences[num_occurences].substring = substring_buf;
            occurences[num_occurences].substring_length = substring_length;

            num_occurences += 1;
        }

        substring_buf += substring_length + 1;
    }

    qsort(occurences, num_occurences, sizeof(substring_occurence), &compare_substring_occurences);

    /*
     * Determine the length of the resulting string
     */

    size_t result_length = 0;

    for(int i = 0; i < num_occurences; i++) {
        size_t candidate_length = occurences[i].start_index + occurences[i].substring_length;

        if(candidate_length > result_length) {
            result_length = candidate_length;
        }
    }

    char* result = malloc(sizeof(char) * (result_length + 1));

    size_t first_unprocessed_index = 0;

    for(int i = 0; i < num_occurences; i++) {
        while(first_unprocessed_index < occurences[i].start_index) {
            result[first_unprocessed_index++] = 'a';
        }

        while(first_unprocessed_index < occurences[i].start_index + occurences[i].substring_length) {
            result[first_unprocessed_index]
                    = occurences[i].substring[first_unprocessed_index - occurences[i].start_index];

            first_unprocessed_index += 1;
        }
    }

    result[result_length] = '\0';

    printf("%s\n", result);

    return 0;
}
