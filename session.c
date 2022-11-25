
#include "session.h"
#include "navigation.h"
#include "uinterface.h"

bool activeSession = false;
Session session;

Page start_session(){
    activeSession = true;
    Page next_page = login;
    return next_page;
}

void end_session() {
    activeSession = false;
}

void get_username(void) {
    scanf("%s", session.user);
}

void get_password(void) {
    scanf("%s", session.password);
}

static bool register_user(void) {
    FILE *file = fopen("users.txt", "a");
    if (file==NULL) {
        printf("user list opening unsuccessful");
        return false;
    }
    
    fprintf(file, "user:%s\npw:%s\n\n", session.user, session.password);
    fclose(file);
    return true;
}

bool login_user(void) {
    fclose(fopen("users.txt", "a"));
    FILE *file = fopen("users.txt", "r");
    if (file==NULL) {
        printf("user list opening unsuccessful");
        return false;
    }
    
    char u[11], p[11];
    while (fscanf(file, " user:%s\npw:%s ", u, p)==2) {
        if (strcmp(u, session.user) == 0) {
            if (strcmp(p, session.password)==0) {
                fclose(file);
                printf("login success");
                return true;
            }
            else {
                fclose(file);
                printf("incorrect password");
                return false;
            }
        }
        
    }
    /*create new user*/
    if(register_user()) {
        printf("sign up success");
        return true;
    }
    
    return false;
}
