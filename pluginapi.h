#ifndef _PLUGINAPI_H
#define _PLUGINAPI_H
 
typedef int (*Callback)(int id);
typedef int (*StrCallback)(char *str);
 
typedef struct {
    Callback onprintnum;
    StrCallback onprintstr;
    StrCallback onprintname;
} EventTable;
 
#endif
