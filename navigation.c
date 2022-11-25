
#include "navigation.h"
#include "session.h"
#include "uinterface.h"

static int get_choise(void) {
    
    char choise;
    
    do {
        scanf("%c", &choise);
    } while (choise < '0' || choise > '9' || choise == '\n');
    
    return choise;
}

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
                return screen;
            case tasks:
                return screen;
            case single:
                return screen;
            case newTask:
                return screen;
            case logout:
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
