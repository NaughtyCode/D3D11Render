#include "stdafx.h"
#include "INIConfig.h"



typedef struct
{
    int version;
    const char* name;
    const char* email;
} configuration;

static int ConfigHandler(void* user, const char* section, const char* name,const char* value)
{
    configuration* pconfig = (configuration*)user;
    
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("protocol", "version"))
    {
        pconfig->version = atoi(value);
    } else if (MATCH("user", "name"))
    {
        pconfig->name = _strdup(value);
    } else if (MATCH("user", "email"))
    {
        pconfig->email = _strdup(value);
    } else
    {
        return 0;
    }
    return 1;
}

void LoadRenderConfig()
{
    configuration config;
    
    if (ParseConfigFile("Render.ini", ConfigHandler, &config) < 0)
    {
        printf("Can't load Render.ini \n");
        return;
    }
    
    printf("load Config: version=%d, name=%s, email=%s\n",config.version, config.name, config.email);
}