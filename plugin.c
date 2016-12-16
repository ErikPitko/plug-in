#include "pluginapi.h"
#include <stdio.h>

int p_printnum(int id);
int p_printstr(char* str);

EventTable PLUG_TABLE = {
    .onprintnum = p_printnum,
    .onprintstr = p_printstr,
};

EventTable *init_plugin(void)
{
    printf("plugin initialized :)\n");
    return &PLUG_TABLE;
}

int p_printnum(int id)
{
    printf("plugin: num: %d\n", id);
    return 1;
}

int p_printstr(char* str)
{
    printf("plugin: str: %s\n", str);
    return 1;
}
