#include "stdafx.h"
#include "INIConfig.h"
#include "TResource.h"

static int ConfigHandler(void* object, const char* section, const char* name,const char* value)
{
    configuration* pconfig = (configuration*)object;
    
    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
    if (MATCH("Textures", "Texture1"))
    {
        pconfig->version = _strdup(value);
    }
    else if (MATCH("VertexShader", "File"))
    {
        pconfig->name = _strdup(value);
    }
    else if (MATCH("VertexShader", "Entry"))
    {
        pconfig->email = _strdup(value);
    }
    else if (MATCH("VertexShader", "ShaderModel"))
    {
        pconfig->email = _strdup(value);
    }
    else if (MATCH("PixelShader", "File"))
    {
        pconfig->email = _strdup(value);
    }
    else if (MATCH("PixelShader", "Entry"))
    {
        pconfig->email = _strdup(value);
    }
    else if (MATCH("PixelShader", "ShaderModel"))
    {
        pconfig->email = _strdup(value);
    }
    else
    {
        return 0;
    }
    return 1;
}

void LoadRenderConfig()
{
    configuration config;
    
    
    
    printf("load Config: version=%d, name=%s, email=%s\n",config.version, config.name, config.email);
}