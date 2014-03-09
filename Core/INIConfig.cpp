#include "stdafx.h"
#include "INIConfig.h"

static char* rstrip(char* s)
{
    char* p = s + strlen(s);
    while (p > s && isspace((unsigned char)(*--p)))
        *p = '\0';
    return s;
}

static char* lskip(const char* s)
{
    while (*s && isspace((unsigned char)(*s)))
        s++;
    return (char*)s;
}

static char* find_char_or_comment(const char* s, char c)
{
    int was_whitespace = 0;
    while (*s && *s != c && !(was_whitespace && *s == ';')) {
        was_whitespace = isspace((unsigned char)(*s));
        s++;
    }
    return (char*)s;
}

static char* strncpy0(char* dest, const char* src, size_t size)
{
    strncpy(dest, src, size);
    dest[size - 1] = '\0';
    return dest;
}

int ParseConfigFile(FILE* file,
                int (*ProcessCallBack)(void*,
                const char*,
                const char*,
                const char*),
                void* user)
{
    char line[CONFIG_MAX_LINE];
    char section[CONFIG_MAX_SECTION] = "";
    char prev_name[CONFIG_MAX_NAME] = "";
    
    char* start;
    char* end;
    char* name;
    char* value;
    int lineno = 0;
    int error = 0;
    
    while (fgets(line, CONFIG_MAX_LINE, file) != NULL)
    {
        lineno++;
        start = line;
        if (lineno == 1 && (unsigned char)start[0] == 0xEF &&
                           (unsigned char)start[1] == 0xBB &&
                           (unsigned char)start[2] == 0xBF)
        {
            start += 3;
        }
        start = lskip(rstrip(start));
        if (*start == ';' || *start == '#')
        {
            
        }
        
        else if (*prev_name && *start && start > line)
        {
            if (!ProcessCallBack(user, section, prev_name, start) && !error)
                error = lineno;
        }
        else if (*start == '[')
        {
            end = find_char_or_comment(start + 1, ']');
            if (*end == ']')
            {
                *end = '\0';
                strncpy0(section, start + 1, sizeof(section));
                *prev_name = '\0';
            }
            else if (!error)
            {
                error = lineno;
            }
        }
        else if (*start && *start != ';')
        {
            end = find_char_or_comment(start, '=');
            if (*end != '=')
            {
                end = find_char_or_comment(start, ':');
            }
            if (*end == '=' || *end == ':')
            {
                *end = '\0';
                name = rstrip(start);
                value = lskip(end + 1);
                end = find_char_or_comment(value, '\0');
                if (*end == ';')
                    *end = '\0';
                rstrip(value);
                strncpy0(prev_name, name, sizeof(prev_name));
                if (!ProcessCallBack(user, section, name, value) && !error)
                    error = lineno;
            }
            else if (!error)
            {
                error = lineno;
            }
        }
    }
    return error;
}

int ParseConfigFile(const char* filename,
            int (*ProcessCallBack)(void*,
            const char*,
            const char*,
            const char*),
            void* user)
{
    FILE* file;
    int error;
    
    file = fopen(filename, "r");
    if (!file)
        return -1;
    error = ParseConfigFile(file, ProcessCallBack, user);
    fclose(file);
    return error;
}
