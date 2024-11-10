// 1)SCAN 
#include <stdio.h>
#include <stdlib.h>

void SCAN(int requests[], int n, int head, int disk_size);

int main() {
    int n, head, disk_size;
    
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    
    int requests[n + 2];  // Extra space to add boundaries (0 and disk_size - 1)
    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    
    printf("Enter the disk size (total number of cylinders): ");
    scanf("%d", &disk_size);
    
    SCAN(requests, n, head, disk_size);

    return 0;
}

// SCAN (Elevator) Disk Scheduling Algorithm
void SCAN(int requests[], int n, int head, int disk_size) { 
    int totalSeekTime = 0, i;
    
    // Add lower and upper bounds (0 and disk_size - 1) to the request array
    requests[n] = 0;             // Add 0 for lower bound
    requests[n + 1] = disk_size - 1; // Add upper bound (disk size - 1)
    n += 2;

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

    printf("\nSCAN Disk Scheduling:\n"); 
    printf("Seek sequence: %d", head);

    // Move towards the end of the disk (right direction)
    for (i = headIndex; i < n; i++) {
        totalSeekTime += abs(requests[i] - head); 
        head = requests[i];
        printf(" -> %d", head);
    }

    // Move in the opposite direction (left)
    for (i = headIndex - 1; i >= 0; i--) {
        totalSeekTime += abs(requests[i] - head); 
        head = requests[i];
        printf(" -> %d", head);
    }
    
    printf("\nTotal Seek Time (SCAN): %d\n", totalSeekTime);
}

2)
