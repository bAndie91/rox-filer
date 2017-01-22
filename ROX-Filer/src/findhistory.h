
#include "xml.h"

#ifndef _FINDHISTORY_H
#define _FINDHISTORY_H

XMLwrapper *findhistory;

void findhistory_new(void);
void findhistory_load();
void findhistory_add(const guchar*);
void findhistory_save();
xmlNode *findhistory_find(const gchar*, int);

#endif
