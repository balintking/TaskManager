#ifndef SESSION_H
#define SESSION_H

#include <stdbool.h>
#include <string.h>

#include "uinterface.h"

typedef struct Session {
    char user[11];
    char password[11];
} Session;

extern bool activeSession;
extern Session session;

Page start_session(void);
void end_session(void);

void get_username(void);
void get_password(void);

bool login_user(void);

#endif
