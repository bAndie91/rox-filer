
#ifndef _CALLBACK_H
#define _CALLBACK_H

typedef struct _Callback Callback;
typedef void (*CallbackFn)(gpointer data);

struct _Callback
{
	CallbackFn	callback;
	gpointer	data;
};

#endif
