/*
 * $Id$
 *
 * Diego Zamboni <zamboni@cerias.purdue.edu>
 */

#ifndef _APPMENU_H
#define _APPMENU_H

#include <gtk/gtk.h>
#include "fscache.h"

/* External interface */
void appmenu_add(guchar *app_dir, DirItem *item, GtkWidget *menu);
void appmenu_remove(void);

#endif   /* _APPMENU_H */