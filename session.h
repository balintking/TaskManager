#ifndef SESSION_H
#define SESSION_H

#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "navigation.h"
#include "uinterface.h"
#include "datahandler.h"

/* src: https://www.geeksforgeeks.org/how-to-detect-operating-system-through-a-c-program/ */
#ifdef __APPLE__
#define PLATFORM 1
#else
#define PLATFORM 0
#endif

#define LEN_UNAME 10
#define LEN_PW 15

typedef struct Session {
    char user[LEN_UNAME+1];
    char password[LEN_PW+1];
    char log[200];
    Task *data;
    Task *task;
} Session;

extern bool activeSession;
extern Session session;

Page start_session(void);
void clear_session(void);
void end_session(void);

void get_username(void);
void get_password(void);
bool login_user(void);

bool file_init(char *fname);
FILE *open_savefile(char *mode);

#endif
