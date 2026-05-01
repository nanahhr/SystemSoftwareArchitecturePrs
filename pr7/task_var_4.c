#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    PENDING,
    RUNNING,
    PAUSED,
    CANCELLED,
    COMPLETED
} JobState;

typedef struct
{
    int id;
    char name[32];
    JobState state;
    int progress;
    int total_steps;
} Job;

#define MAX_JOBS 3
Job queue[MAX_JOBS];

void init_queue()
{
    char *names[] = {"Files Sync", "DB Backup", "Log Analysis"};
    for (int i = 0; i < MAX_JOBS; i++)
    {
        queue[i].id = i + 1;
        strcpy(queue[i].name, names[i]);
        queue[i].state = PENDING;
        queue[i].progress = 0;
        queue[i].total_steps = 5;
    }
}

void print_status()
{
    printf("\n--- CURRENT JOB QUEUE ---\n");
    for (int i = 0; i < MAX_JOBS; i++)
    {
        char *status_text;
        switch (queue[i].state)
        {
        case PENDING:
            status_text = "Pending";
            break;
        case RUNNING:
            status_text = "Running";
            break;
        case PAUSED:
            status_text = "Paused";
            break;
        case CANCELLED:
            status_text = "Cancelled";
            break;
        case COMPLETED:
            status_text = "Completed";
            break;
        }
        printf("Job #%d [%s]: %s (%d/%d)\n",
               queue[i].id, queue[i].name, status_text, queue[i].progress, queue[i].total_steps);
    }
}

int main()
{
    init_queue();
    int active_jobs = MAX_JOBS;
    printf("Commands: [n] - step, [p ID] - pause/resume, [c ID] - cancel\n");

    while (active_jobs > 0)
    {
        print_status();
        printf("\nEnter command (e.g., 'n' or 'p 1'): ");

        char cmd;
        int id;
        scanf(" %c", &cmd);

        if (cmd == 'n')
        {
            for (int i = 0; i < MAX_JOBS; i++)
            {
                if (queue[i].state == PENDING)
                    queue[i].state = RUNNING;

                if (queue[i].state == RUNNING)
                {
                    queue[i].progress++;
                    if (queue[i].progress >= queue[i].total_steps)
                    {
                        queue[i].state = COMPLETED;
                        active_jobs--;
                    }
                    break;
                }
            }
        }
        else if (cmd == 'p')
        {
            scanf("%d", &id);
            int i = id - 1;
            if (i >= 0 && i < MAX_JOBS)
            {
                if (queue[i].state == RUNNING || queue[i].state == PENDING)
                {
                    queue[i].state = PAUSED;
                    printf("Job %d PAUSED.\n", id);
                }
                else if (queue[i].state == PAUSED)
                {
                    queue[i].state = RUNNING;
                    printf("Job %d RESUMED.\n", id);
                }
            }
        }
        else if (cmd == 'c')
        {
            scanf("%d", &id);
            int i = id - 1;
            if (i >= 0 && i < MAX_JOBS && queue[i].state != COMPLETED)
            {
                queue[i].state = CANCELLED;
                active_jobs--;
                printf("Job %d CANCELLED.\n", id);
            }
        }
    }

    printf("\nAll jobs processed. Final status:\n");
    print_status();
    return 0;
}