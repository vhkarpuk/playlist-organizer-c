#include <stdio.h>
#include <string.h>

#define MAX_SONGS  32
#define BUF_SIZE   128

// Utility: print playlist on one line
void print_playlist(const char *songs[], int count) {
    if (count == 0) { printf("(empty)\n"); return; }
    for (int i = 0; i < count; i++) {
        printf("'%s'%s", songs[i], (i == count - 1 ? "\n" : ", "));
    }
}

// Previous algorithm: selection sort (alphabetical, A–Z)
void selection_sort(const char *songs[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (strcmp(songs[j], songs[minIndex]) < 0) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            const char *tmp = songs[i];
            songs[i] = songs[minIndex];
            songs[minIndex] = tmp;
        }
    }
}

// New algorithm: bubble sort (alphabetical, A–Z)
void bubble_sort(const char *songs[], int count) {
    int swapped;
    for (int i = 0; i < count - 1; i++) {
        swapped = 0;
        for (int j = 0; j < count - 1 - i; j++) {
            if (strcmp(songs[j], songs[j + 1]) > 0) {
                const char *tmp = songs[j];
                songs[j] = songs[j + 1];
                songs[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break; // already sorted
    }
}

// Delete by exact title; returns 1 if deleted, 0 if not found
int delete_song(const char *songs[], int *count, const char *title) {
    int n = *count;
    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(songs[i], title) == 0) { idx = i; break; }
    }
    if (idx == -1) return 0;

    // shift left to fill the gap
    for (int i = idx; i < n - 1; i++) {
        songs[i] = songs[i + 1];
    }
    (*count)--;
    return 1;
}

int main(void) {
    // Start with 8 titles in random (unsorted) order; must include "Last Minute"
    const char *songs[MAX_SONGS] = {
        "Hey Jude",
        "Like a Rolling Stone",
        "Last Minute",
        "Bohemian Rhapsody",
        "Wonderwall",
        "Hotel California",
        "Imagine",
        "Smells Like Teen Spirit"
    };
    int count = 8;

    while (1) {
        int choice;
        printf("\nPlaylist Organizer\n");
        printf("1. Display playlist\n");
        printf("2. Sort (Selection Sort)\n");
        printf("3. Sort (Bubble Sort)\n");
        printf("4. Delete a song by exact title\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) { printf("Invalid input.\n"); return 1; }

        // flush leftover newline before any fgets
        int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}

        if (choice == 1) {
            printf("\nCurrent playlist (%d):\n", count);
            print_playlist(songs, count);

        } else if (choice == 2) {
            printf("\nBefore (Selection Sort):\n");
            print_playlist(songs, count);
            selection_sort(songs, count);
            printf("After (Selection Sort):\n");
            print_playlist(songs, count);

        } else if (choice == 3) {
            printf("\nBefore (Bubble Sort):\n");
            print_playlist(songs, count);
            bubble_sort(songs, count);
            printf("After (Bubble Sort):\n");
            print_playlist(songs, count);

        } else if (choice == 4) {
            char title[BUF_SIZE];
            printf("Enter the exact song title to delete: ");
            if (!fgets(title, sizeof(title), stdin)) { printf("Input error.\n"); return 1; }
            // strip trailing newline
            size_t len = strlen(title);
            if (len > 0 && title[len - 1] == '\n') title[len - 1] = '\0';

            if (delete_song(songs, &count, title)) {
                printf("Deleted: '%s'\n", title);
                printf("Updated playlist (%d):\n", count);
                print_playlist(songs, count);
            } else {
                printf("Song not found: '%s'\n", title);
            }

        } else if (choice == 5) {
            printf("Goodbye!\n");
            break;

        } else {
            printf("Invalid choice. Please select 1, 2, 3, 4, or 5.\n");
        }
    }

    return 0;
}