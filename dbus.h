/*
 * Copyright 2014 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef FRECON_DBUS_H
#define FRECON_DBUS_H

#include <sys/select.h>
#include <stdbool.h>
#include <memory.h>
#include <stdio.h>

bool dbus_init();
bool dbus_init_wait();
void dbus_destroy(void);
void dbus_add_fds(fd_set* read_set, fd_set* exception_set, int *maxfd);
void dbus_dispatch_io(void);
void dbus_report_user_activity(int activity_type);
void dbus_take_display_ownership(void);
bool dbus_release_display_ownership(void);
bool dbus_is_initialized(void);
void dbus_set_login_prompt_visible_callback(void (*callback)(void*),
					    void* userptr);
void dbus_set_suspend_done_callback(void (*callback)(void*),
				    void* userptr);

#endif // FRECON_DBUS_H
