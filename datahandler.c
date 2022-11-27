#include "datahandler.h"
#include "session.h"

/*
 Task name
 due date
 category
 description
 done
 */

/*
 open file
 get liene
 store data in linked list
 */

Task* init_task(void) {
    Task *task;
    task = (Task*) malloc(sizeof(Task));
    
    strcpy(task->name, "");
    task->due.y = 0;
    task->due.m = 0;
    task->due.d = 0;
    strcpy(task->cat, "");
    strcpy(task->dscr, "");
    task->done = false;
    
    return task;
}

bool valid_task(Task *task) {
    if (strcmp(task->name, "") != 0) {
        if (task->due.y !=0 && task->due.m !=0 && task->due.d !=0) {
            return true;
        }
    }
    return false;
}

Task* insert_task(Task *data_start, Task *loadTask) {
    Task *new;
    new = (Task*) malloc(sizeof(Task));
    if (new == NULL) {
        return NULL;
    }
    
    strcpy(new->name, loadTask->name);
    new->due = loadTask->due;
    strcpy(new->cat, loadTask->cat);
    strcpy(new->dscr, loadTask->dscr);
    new->done = loadTask->done;
    
    new->next = data_start;
    return new;
}

Task* load_task(FILE *savefile, bool *empty) {
    Task *loadTask;
    loadTask = (Task*) malloc(sizeof(Task));
    if (loadTask == NULL) {
        return NULL;
    }
    
    if (fscanf(savefile, "%s\n", loadTask->name) != 1) {
        *empty = true;
        return NULL;
    }
    
    fscanf(savefile, "%d.%d.%d.\n", &loadTask->due.y, &loadTask->due.m, &loadTask->due.d);
    
    fscanf(savefile, "%s\n", loadTask->cat);
    
    fscanf(savefile, "%s\n", loadTask->dscr);
    
    int loadDone;
    fscanf(savefile, "%d\n", &loadDone);
    if (loadDone == 1) {
        loadTask->done = true;
    }
    else if (loadDone == 0) {
        loadTask->done = false;
    }
    
    return loadTask;
}

FILE *open_savefile(char *mode) {
    // mac has read-only permission
    /*
    char filename[11+LEN_UNAME+4+1] = "/savefiles/";
    strcat(filename, session.user);
    strcat(filename, ".txt");
    
    if (!dir_init("/savefiles")) {
        strcpy(session.log, "[error:can't create directory | ");
        strcat(session.log, strerror(errno));
        strcat(session.log, "]");
        strcat(session.log, filename);
        return false;
    }*/
    char filename[LEN_UNAME+4+1] = "save_";
    strcpy(filename, session.user);
    strcat(filename, ".txt");
    
    if (!file_init(filename)) {
        return NULL;
    }
    
    FILE *savefile = fopen(filename, mode);
    if (savefile == NULL) {
        return NULL;
    }
    
    return savefile;
}

bool load_data(void) {
    
    FILE *savefile = open_savefile("r");
    if (savefile == NULL) {
        strcpy(session.log, "[error:can't open save file | ");
        strcat(session.log, strerror(errno));
        strcat(session.log, "]");
        return false;
    }
    
    Task *data_start = NULL;
    bool empty = false;
    
    Task *loadTask = load_task(savefile, &empty);
    if (empty) {
        strcpy(session.log, "empty file");
        return true;
    }
    if (loadTask == NULL && !(empty)) {
        strcpy(session.log, "[error: failed to allocate memory | ");
        strcat(session.log, strerror(errno));
        strcat(session.log, "]");
        return false;
    }
    while (loadTask != NULL) {
        data_start = insert_task(data_start, loadTask);
        free(loadTask);
        loadTask = load_task(savefile, &empty);
        if ((loadTask == NULL && !empty )|| data_start == NULL) {
            strcpy(session.log, "[error: failed to allocate memory | ");
            strcat(session.log, strerror(errno));
            strcat(session.log, "]");
            return false;
        }
    }
    
    fclose(savefile);
    session.data = data_start;
    return true;
}


bool append_task(Task *data_start, Task *newTask) {
    FILE *savefile = open_savefile("a");
    if (savefile == NULL) {
        strcpy(session.log, "[error:can't open save file | ");
        strcat(session.log, strerror(errno));
        strcat(session.log, "]");
        return false;
    }
    
    fprintf(savefile, "%s\n", newTask->name);
    fprintf(savefile, "%d.%d.%d.\n", newTask->due.y, newTask->due.m, newTask->due.d);
    fprintf(savefile, "%s\n", newTask->cat);
    fprintf(savefile, "%s\n", newTask->dscr);
    if (newTask->done) {
        fprintf(savefile, "1\n");
    } else {
        fprintf(savefile, "0\n");
    }
    
    fclose(savefile);
    return true;
}

void print_tasks(void) {
    Task *pointer = session.data;
    while (pointer != NULL) {
        printf("%s\n", pointer->name);
        printf("%d.%d.%d.\n", pointer->due.y, pointer->due.y, pointer->due.y);
        printf("%s\n", pointer->cat);
        printf("%s\n", pointer->dscr);
        if (pointer->done) {
            printf("1\n");
        } else {
            printf("0\n");
        }
        
        pointer = pointer->next;
    }
}

bool save_data(void) {
    FILE *savefile = open_savefile("w");
    if (savefile == NULL) {
        strcpy(session.log, "[error:can't open save file | ");
        strcat(session.log, strerror(errno));
        strcat(session.log, "]");
        return false;
    }
    
    Task *pointer = session.data;
    while (pointer != NULL) {
        Task *temp = pointer->next;
        
        fprintf(savefile, "%s\n", pointer->name);
        fprintf(savefile, "%d.%d.%d.\n", pointer->due.y, pointer->due.y, pointer->due.y);
        fprintf(savefile, "%s\n", pointer->cat);
        fprintf(savefile, "%s\n", pointer->dscr);
        if (pointer->done) {
            fprintf(savefile, "1\n");
        } else {
            fprintf(savefile, "0\n");
        }
        
        free(pointer);
        pointer = temp;
    }
    
    fclose(savefile);
    return true;
}
