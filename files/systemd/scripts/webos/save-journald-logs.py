#!/usr/bin/env python2
# @@@LICENSE
#
# Copyright (c) 2019 LG Electronics, Inc.
#
# Confidential computer software. Valid license from LG required for
# possession, use or copying. Consistent with FAR 12.211 and 12.212,
# Commercial Computer Software, Computer Software Documentation, and
# Technical Data for Commercial Items are licensed to the U.S. Government
# under vendor's standard commercial license.
#
# LICENSE@@@

import os
import tarfile
import time

from subprocess import call, PIPE, Popen

def get_timestamp():
    t = time.localtime()
    return str(t.tm_year).zfill(4) + "-" + str(t.tm_mon).zfill(2) + "-" + str(t.tm_mday).zfill(2) + "-" + str(
        t.tm_hour).zfill(2) + "-" + str(t.tm_min).zfill(2) + "-" + str(t.tm_sec).zfill(2)

def flush_journald_log_to_file():
    journalctl_options = ['-a']
    command = ['journalctl'] + journalctl_options
    log_file_name = "/var/log/journald-" + get_timestamp() + ".log"
    with open(log_file_name, "w") as logfile:
        call(command, stdout=logfile)
    return

def backup_var_log():
    logfile = '/var/spool/rdxd/previous_boot_logs.tar.gz'
    if os.path.isfile(logfile):
        os.remove(logfile)
    
    source = '/var/log/'
    with tarfile.open(logfile, "w:gz") as tar:
        tar.add(source, arcname='log')
    return

if __name__ == '__main__':
    flush_journald_log_to_file()
    backup_var_log()

    exit(0)
