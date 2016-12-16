#include "pluginapi.h"
#include <stdio.h>
#include <dlfcn.h>

int dummy(int i)
{
    (void)i;
    printf("NULL function, ignoring ...\n");
    return 0;
}

int strdummy(char* str)
{
	(void)str;
	printf("NULL strFunction, ignoring ...\n");
	return 0;
}

void t_complement(EventTable *events)
{
    if (events->onprintnum == NULL)
        events->onprintnum = &dummy;
    if (events->onprintstr == NULL)
        events->onprintstr = &strdummy;
    if (events->onprintname == NULL)
        events->onprintname = &strdummy;
}

void *load_plugin(char *filename, EventTable *events)
{
    void *handle = dlopen(filename, RTLD_LAZY);
    if (handle == NULL)
    {
        fprintf(stderr, "error: %s\n", dlerror());
        return NULL;
    }

    void *symbol = dlsym(handle, "init_plugin");
    if (symbol == NULL)
    {
        fprintf(stderr, "error: %s\n", dlerror());
        dlclose(handle);
        return NULL;
    }

    EventTable* (*init)(void) = symbol;
    *events = *init();
    t_complement(events);

    return handle;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    EventTable events;

    void *handle = load_plugin(argv[1], &events);
    if (handle == NULL)
       return 2;


    events.onprintnum(42);
    events.onprintstr("Does it even work?");
    events.onprintstr("it rly works!");
	events.onprintname("this shouldnt work");
    printf("Closing plugin ...\n");
    dlclose(handle);

    printf("Exit: %s\n", dlerror());
    return 0;
}
