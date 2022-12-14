#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


#define LEN_T_NAME 50
#define LEN_T_CAT 15
#define LEN_T_DSCR 500

typedef struct Date {
    int y;
    int m;
    int d;
} Date;

typedef struct Task {
    char name[LEN_T_NAME+1];
    Date due;
    char cat[LEN_T_CAT+1];
    char dscr[LEN_T_DSCR+1];
    bool done;
    struct Task *next;
} Task;

Task* task_init(void);

void print_tasks(void);

bool valid_task(Task *task);
Task* add_task(Task *data_start, Task *newTask);

Task* remove_task(Task *data_start, Task *rmTask);

bool load_data(void);

bool save_data(void);


double percent_today(int *count_today, int *count_today_done);
bool find_next_task(void);
bool jump_seq(void);

#endif
