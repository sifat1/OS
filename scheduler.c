#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main() {
    int policy;
    struct sched_param param;

    // Get the current scheduling policy of the process
    policy = sched_getscheduler(0);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Current scheduling policy: ");
    switch (policy) {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        default:
            printf("Unknown\n");
    }

    // Change the scheduling policy to SCHED_FIFO
    param.sched_priority = 50;  // Set the priority (must be within the valid range)
    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler");
        return 1;
    }

    // Get the updated scheduling policy
    policy = sched_getscheduler(0);
    if (policy == -1) {
        perror("sched_getscheduler");
        return 1;
    }

    printf("Updated scheduling policy: ");
    switch (policy) {
        case SCHED_FIFO:
            printf("SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("SCHED_OTHER\n");
            break;
        default:
            printf("Unknown\n");
    }

    return 0;
}
