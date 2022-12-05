#include "session.h"
#include "debugmalloc.h"

bool activeSession;
Session session;


//session handler

Page start_session(){
    activeSession = true;
    Page next_page = login;
    return next_page;
}

void clear_session(void) {
    session.user[0] = '\0';
    session.password[0] = '\0';
}

void end_session() {
    activeSession = false;
}


//user login

void get_username(void) {
    scanf("%s", session.user);
}

void get_password(void) {
    scanf("%s", session.password);
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

        if (!file_init(filename)) {
            strcpy(session.log, "[error:can't open user file]");
            return false;
        }
        
        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            strcpy(session.log, "[error:can't open user file]");
            return false;
        }
        /*not validating user input*/
        char u[LEN_UNAME+1], p[11];
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


//file handler

bool file_init(char *fname) {
    FILE *file = fopen(fname, "a");
    if (file==NULL) {
        return false;
    }
    
    fclose(file);
    return true;
}

FILE *open_savefile(char *mode) {
    char filename[5+LEN_UNAME+4+1] = "save_";
    strcat(filename, session.user);
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
