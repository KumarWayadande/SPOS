// C-look short code
#include <stdio.h>
#include <stdlib.h>

void C_Look(int requests[], int n, int head);

int main() {
    int n, head;
    
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    
    int requests[n];
    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    
    C_Look(requests, n, head);

    return 0;
}

// C-LOOK Disk Scheduling Algorithm
void C_Look(int requests[], int n, int head) { 
    int totalSeekTime = 0, i;

    // Sort the requests array
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) { 
                int temp = requests[j]; 
                requests[j] = requests[j + 1]; 
                requests[j + 1] = temp;
            }
        }
    }

    // Find the index of the first request greater than or equal to the head
    int headIndex = 0;
    for (i = 0; i < n; i++) {
        if (requests[i] >= head) { 
            headIndex = i;
            break;
        }
    }

    printf("\nC-LOOK Disk Scheduling:\n"); 
    printf("Seek sequence: %d", head);

    // Move towards the end of the disk (right direction)
    for (i = headIndex; i < n; i++) {
        totalSeekTime += abs(requests[i] - head); 
        head = requests[i];
        printf(" -> %d", head);
    }

    // Jump to the beginning of the queue and continue serving requests
    for (i = 0; i < headIndex; i++) {
        totalSeekTime += abs(requests[i] - head); 
        head = requests[i];
        printf(" -> %d", head);
    }
    
    printf("\nTotal Seek Time (C-LOOK): %d\n", totalSeekTime);
}
