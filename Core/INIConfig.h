#ifndef INICONFIG_H
#define INICONFIG_H


#if _MSC_VER > 1000
# pragma once
#endif

int ParseConfigFile(const char* filename,
            int (*ProcessCallBack)(void* user,
            const char* section,
            const char* name,
            const char* value),
            void* user);

int ParseConfigFile(FILE* file,
                int (*ProcessCallBack)(void* user,
                const char* section,
                const char* name,
                const char* value),
                void* user);

#endif
