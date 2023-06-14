/* @@@LICENSE
 *
 * Copyright (c) 2019 LG Electronics, Inc.
 *
 * Confidential computer software. Valid license from LG required for
 * possession, use or copying. Consistent with FAR 12.211 and 12.212,
 * Commercial Computer Software, Computer Software Documentation, and
 * Technical Data for Commercial Items are licensed to the U.S. Government
 * under vendor's standard commercial license.
 *
 * LICENSE@@@
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ParseCmdLine.h"

#define CMDLINE "/proc/cmdline"

int parseOption(const char *line, const char *option, char *value, size_t size)
{
    const char *p0, *p1;
    int len;

    p0 = strstr(line, option);
    if (!p0)
        return 0;

    p0 += strlen(option);
    p1  = strchr(p0, ' ');

    if (!p1)
        p1 = p0 + strlen(p0);

    len = p1 - p0;

    if (len > size - 1)
        len = size - 1;

    memcpy(value, p0, len);
    value[len] = '\0';

    return len;
}

void getCmdLineOption(const char *option, char *value, size_t size)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    if (!size)
        return;

    *value = '\0';
    fp = fopen(CMDLINE, "r");
    if (fp == NULL)
        return;

    while ((read = getline(&line, &len, fp)) != -1)
        if (parseOption(line, option, value, size))
            break;

    fclose(fp);
    if (line)
        free(line);

    return;
}

bool hasCmdLineOption(const char *option)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    bool search = false;

    fp = fopen(CMDLINE, "r");
    if (fp == NULL)
        return false;

    while ((read = getline(&line, &len, fp)) != -1) {
        if (strstr(line, option)) {
            search  = true;
            break;
        }
    }

    fclose(fp);
    if (line)
        free(line);

    if (search)
        return true;
    else
        return false;
}
