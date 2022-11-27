
#include "navigation.h"
#include "session.h"
#include "uinterface.h"
#include "datahandler.h"

/*gets and executes user command based on the current window*/
Page navigate(Page screen){
    
    char option;
    do {
        scanf("%c", &option);
    } while (option == '\n');
  
    if (option != EOF && option >= '0' && option <= '9') {
        switch(screen){
            case login:
                switch(option) {
                    case '1':
                        get_username();
                        return screen;
                    case '2':
                        get_password();
                        return screen;
                    case '3':
                        if(login_user()) {
                            load_data();
                            return dashboard;
                        }
                        else {
                            return screen;
                        }
                    default:
                        strcpy(session.log, "Invalid input!");
                        return screen;
                }
            case dashboard:
                switch(option) {
                    case '1':
                        session.task = init_task();
                        return newTask;
                    case '2':
                        return tasks;
                    case '3':
                        return single;
                    case '9':
                        return logout;
                    default:
                        strcpy(session.log, "Invalid input!");
                        return screen;
                }
            case tasks:
                switch(option) {
                    case '0':
                        return dashboard;
                    case '1':
                        return screen;
                    case '2':
                        return screen;
                    case '3':
                        return screen;
                    case '4':
                        return screen;
                    case '5':
                        return screen;
                    case '8':
                        return screen;
                    case '9':
                        return screen;
                    default:
                        strcpy(session.log, "Invalid input!");
                        return screen;
                }
            case single:
                return screen;
            case newTask:
                switch(option) {
                    case '0':
                        if (valid_task(session.task)) {
                            if (append_task(session.data, session.task)) {
                                strcpy(session.log, "Task Saved Successfully");
                                load_data();
                                return dashboard;
                            }
                            strcpy(session.log, "Failed to Save Task");
                            return dashboard;
                        } else {
                            strcpy(session.log, "Title and Due Date fields must be filled out!");
                            return screen;
                        }
                    case '1':
                        scanf("%s", session.task->name);
                        return screen;
                    case '2':
                        printf("(YYYY.MM.DD.)");
                        int iny, inm, ind;
                        if (scanf("%d.%d.%d.", &iny, &inm, &ind) == 3) {
                            session.task->due.y = iny;
                            session.task->due.m = inm;
                            session.task->due.d = ind;
                        } else {
                            strcpy(session.log, "Invalid input!");
                            return screen;
                        }
                        return screen;
                    case '3':
                        scanf("%s", session.task->cat);
                        return screen;
                    case '4':
                        scanf("%s", session.task->dscr);
                        return screen;
                    case '5':
                        printf("(0 - No, 1 - Yes)");
                        int indone;
                        scanf("%d", &indone);
                        if (indone == 0) {
                            session.task->done = false;
                        } else if (indone == 1) {
                            session.task->done = true;
                        } else {
                            strcpy(session.log, "Invalid input!");
                            return screen;
                        }
                        return screen;
                    case '9':
                        return dashboard;
                    default:
                        strcpy(session.log, "Invalid input!");
                        return screen;
                }
                return screen;
            case logout:
                switch(option) {
                    case '1':
                        //remove session info
                        clear_session();
                        return login;
                    case '2':
                        //remove session info & quit
                        clear_session();
                        end_session();
                        return login;
                    case '9':
                        return dashboard;
                    default:
                        strcpy(session.log, "Invalid input!");
                        return screen;
                }
                return screen;
            default:
                return screen;
        }
    }
    else {
        strcpy(session.log, "Invalid input!");
        return screen;
    }
}
