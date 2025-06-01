#include <stdio.h>

int main() {
    int A[100][4];
    int i, j, n = 0, choice;
    int total;
    float avg_wt, avg_tat;
    int dataEntered = 0;

    while (1) {
        printf("\n--- SJF Scheduling Menu ---\n");
        printf("1. Enter Process Data\n");
        printf("2. Show SJF Schedule\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter number of processes: ");
                scanf("%d", &n);
                getchar();

                printf("Enter Burst Times:\n");
                for (i = 0; i < n; i++) {
                    printf("P%d: ", i + 1);
                    scanf("%d", &A[i][1]);
                    A[i][0] = i + 1;
                }
                dataEntered = 1;
                break;

            case 2:
                if (!dataEntered) {
                    printf("No data entered. Please input process data first.\n");
                    break;
                }

                for (i = 0; i < n; i++) {
                    int index = i;
                    for (j = i + 1; j < n; j++) {
                        if (A[j][1] < A[index][1])
                            index = j;
                    }

                    int temp = A[i][1];
                    A[i][1] = A[index][1];
                    A[index][1] = temp;

                    temp = A[i][0];
                    A[i][0] = A[index][0];
                    A[index][0] = temp;
                }

                A[0][2] = 0;
                total = 0;

                for (i = 1; i < n; i++) {
                    A[i][2] = 0;
                    for (j = 0; j < i; j++) {
                        A[i][2] += A[j][1];
                    }
                    total += A[i][2];
                }

                avg_wt = (float)total / n;

                total = 0;
                printf("\n%-3s %3s %3s %3s\n", "PID", "BT", "WT", "TAT");

                for (i = 0; i < n; i++) {
                    A[i][3] = A[i][1] + A[i][2];
                    total += A[i][3];
                    printf("P%-2d %3d %3d %3d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
                }

                avg_tat = (float)total / n;

                printf("\nAverage Waiting Time    = %.2f", avg_wt);
                printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
                break;

            case 3:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

