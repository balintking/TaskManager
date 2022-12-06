#ifndef UINTERFACE_H
#define UINTERFACE_H

#include <stdio.h>
#include <ctype.h>

#include "datahandler.h"

typedef enum Page{
    login,
    dashboard,
    tasks,
    edit,
    create,
    logout
} Page;

void display(Page screen);

#endif
