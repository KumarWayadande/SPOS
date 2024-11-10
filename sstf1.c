// Sstf short code
#include <stdio.h> 
#include <stdlib.h>
#include <limits.h> // Include this header for INT_MAX

void SSTF(int requests[], int n, int head);

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
    
    SSTF(requests, n, head);

    return 0;
}

// Function to find the closest request in SSTF
int findClosest(int requests[], int n, int head, int visited[]) {
    int minDistance = INT_MAX;
    int index = -1;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i] && abs(requests[i] - head) < minDistance) { 
            minDistance = abs(requests[i] - head);
            index = i;
        }
    }
    
    return index;
}

// SSTF (Shortest Seek Time First) Disk Scheduling Algorithm 
void SSTF(int requests[], int n, int head) {
    int visited[n], totalSeekTime = 0;

    for (int i = 0; i < n; i++) visited[i] = 0;

    printf("\nSSTF Disk Scheduling:\n"); 
    printf("Seek sequence: %d", head);

    for (int i = 0; i < n; i++) {
        int closestIndex = findClosest(requests, n, head, visited); 
        if (closestIndex == -1) break;

        visited[closestIndex] = 1;
        totalSeekTime += abs(requests[closestIndex] - head); 
        head = requests[closestIndex];

        printf(" -> %d", head);
    }
    
    printf("\nTotal Seek Time (SSTF): %d\n", totalSeekTime);
}
