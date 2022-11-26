
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

bool file_init(char *fname) {
    FILE *file = fopen(fname, "a");
    if (file==NULL) {
        strcpy(session.log, "[error:can't open user file]");
        return false;
    }
    
    fclose(file);
    return true;
}

static bool register_user(char *fname) {
    FILE *file = fopen(fname, "a");
    if (file==NULL) {
        strcpy(session.log, "[error:can't open user file]");
        return false;
    }
    
    fprintf(file, "user:%s\npw:%s\n\n", session.user, session.password);
    fclose(file);
    return true;
}

bool login_user(void) {
    if (strcmp(session.user, "")!=0 && strcmp(session.password, "")!=0) {
        char filename[] = "users.txt";
        file_init(filename);
        
        FILE *file = fopen(filename, "r");
        if (file==NULL) {
            strcpy(session.log, "[error:can't open user file]");
            return false;
        }
        /*not validating user input*/
        char u[11], p[11];
        while (fscanf(file, " user:%s\npw:%s ", u, p)==2) {
            if (strcmp(u, session.user) == 0) {
                if (strcmp(p, session.password)==0) {
                    fclose(file);
                    strcpy(session.log, "Login successful");
                    return true;
                }
                else {
                    fclose(file);
                    strcpy(session.log, "Incorrect password!");
                    return false;
                }
            }
        }
        /*create new user*/
        if(register_user(filename)) {
            strcpy(session.log, "Sign up successful");
            return true;
        }
        return false;
    }
    else {
        strcpy(session.log, "Missing fields!");
        return false;
    }
}
