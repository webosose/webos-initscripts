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


#ifndef PARSE_CMD_LINE_H
#define PARSE_CMD_LINE_H

int parseOtion(const char *line, const char *option, char *value, size_t size);
void getCmdLineOption(const char *option, char *value, size_t size);
bool hasCmdLineOption(const char *option);

#endif // PARSE_CMD_LINE_H
