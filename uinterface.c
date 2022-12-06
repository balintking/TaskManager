
#include "uinterface.h"
#include "session.h"
#include "navigation.h"

#include "debugmalloc.h"

void display_log(void) {
    printf("%s\n", session.log);
    session.log[0] = '\0';
}

static void display_login(void){
    printf("\n");
    printf("LOGIN");
    printf("\n\n");
    
    printf("[1] username: %s\n", session.user);
    printf("[2] password: %s\n", session.password);
    printf("\n");
    
    printf("[3] Login\n");
    printf("\n");

}

static void display_dashboard(void){
    printf("\n");
    printf("HELLO, ");
    for (int i = 0; i < strlen(session.user); i++) {
        printf("%c", toupper(session.user[i]));
    }
    printf("!\n");
    printf("\n\n");
    
    int count_today, count_today_done;
    double percent = percent_today(&count_today, &count_today_done);
    
    if (percent == -1) {
        printf("You don't have any Tasks for today");
    } else {
        printf("Your Tasks for today %d/%d [", count_today_done, count_today);
        for (int i = 1; i <= 10; i++) {
            (i <= percent/10) ? printf("#") : printf(" ");
        }
        printf("] %.0f%% Done\n", percent);
    }
    printf("\n");
    
    if(find_next_task()) {
        printf("Next Task:\t[3] %s\n\t\t    %04d.%02d.%02d.\n\t\t    %s\n", session.task->name, session.task->due.y, session.task->due.m, session.task->due.d, session.task->cat);
    }
    printf("\n\n\n\n");
    
    printf("[1] Create New Task\t[2] See All Tasks\t\t\t[9] Log Out\n");
    printf("\n");
    
}

static void display_tasks(void){
    printf("\n");
    printf("YOUR TASKS");
    printf("\n\n");
    
    if (session.data != NULL) {
        print_tasks();
    }
    printf("\n\n");

    printf("[0] Next\t\t\t[9] Home\n");
    printf("\n");
}

static void display_edit(void) {
    printf("\n");
    printf("EDIT TASK");
    printf("\n\n");
    
    printf("[1] Title: %s\n", session.task->name);
    printf("[2] Due Date: %04d.%02d.%02d.\n", session.task->due.y, session.task->due.m, session.task->due.d);
    printf("[3] Category: %s\n", session.task->cat);
    printf("[4] Description: %s\n", session.task->dscr);
    printf("[5] Done: ");
    if (session.task->done) {
        printf("Yes");
    }
    else {
        printf("No");
    }
    printf("\n");
    printf("\n");
    
    printf("[0] Save\t[9] Remove\n");
    printf("\n");
}

static void display_create(void){
    printf("\n");
    printf("CREATE NEW TASK");
    printf("\n\n");
    
    printf("[1] Title: %s\n", session.task->name);
    printf("[2] Due Date: %04d.%02d.%02d.\n", session.task->due.y, session.task->due.m, session.task->due.d);
    printf("[3] Category: %s\n", session.task->cat);
    printf("[4] Description: %s\n", session.task->dscr);
    printf("[5] Done: ");
    if (session.task->done) {
        printf("Yes");
    }
    else {
        printf("No");
    }
    printf("\n");
    printf("\n");
    
    printf("[0] Save\t[9] Cancel\n");
    printf("\n");
}

static void display_logout(void) {
    printf("\n");
    printf("LOG OUT");
    printf("\n\n");
    
    printf("[1] Save & Log out\n");
    printf("[2] Save & Close application\n");
    printf("\n");
    printf("[9] Cancel\n");
    printf("\n");
}

/*displays the contents of the current page*/
void display(Page screen) {
    
    if (PLATFORM == 1) {
        system("clear");
    }
    else {
        system("cls");
    }
    
    switch(screen){
        case login:
            display_login();
            break;
        case dashboard:
            display_dashboard();
            break;
        case tasks:
            display_tasks();
            break;
        case edit:
            display_edit();
            break;
        case create:
            display_create();
            break;
        case logout:
            display_logout();
            break;
        default:
            break;
    }
    
    display_log();
    
    printf("OPTION: ");
}


