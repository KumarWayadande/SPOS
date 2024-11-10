// Optimal page replace

#include <stdio.h>

int findOptimal(int pages[], int frames[], int n, int f, int index) {
    int farthest = index, pos = -1, i, j;
    for (i = 0; i < f; i++) {
        int found = 0;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                found = 1;
                break;
            }
        }
        if (!found) {
            return i; // If a page is not going to be used in the future, replace it
        }
    }
    return (pos == -1) ? 0 : pos;
}

int main() {
    int frames[10], pages[30];
    int n, f, i, j, pos, pageFaults = 0;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
    }

    printf("\nPage Reference String\t");
    for (i = 0; i < f; i++) {
        printf("Frame %d\t", i + 1);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        int found = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) { // Page hit
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault
            if (pageFaults < f) {
                frames[pageFaults] = pages[i];
            } else {
                pos = findOptimal(pages, frames, n, f, i + 1);
                frames[pos] = pages[i];
            }
            pageFaults++;
        }

        // Print the current page and the frame content
        printf("%d\t\t\t", pages[i]);
        for (j = 0; j < f; j++) {
            if (frames[j] != -1) {
                printf("%d\t", frames[j]);
            } else {
                printf("-\t");
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}

