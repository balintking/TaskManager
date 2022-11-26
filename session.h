#ifndef SESSION_H
#define SESSION_H

#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "uinterface.h"
#include "datahandler.h"


#ifdef __APPLE__
#define PLATFORM 1
#else
#define PLATFORM 0
#endif

#define LEN_UNAME 10

typedef struct Session {
    char user[LEN_UNAME+1];
    char password[11];
    char log[200];
    Task *data;
} Session;

extern bool activeSession;
extern Session session;

Page start_session(void);
void end_session(void);

void get_username(void);
void get_password(void);

bool login_user(void);

bool dir_init(char *dirname);
bool file_init(char *fname);

#endif
