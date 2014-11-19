/*
 * Copyright 2014 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef DBUS_INTERFACE_H_
#define DBUS_INTERFACE_H_

/* Minimal set of power manager constants copied from
   platform/system_api/dbus/service_constants.h which are C++
   header file so we can't use it in our code directly */

static const char kPowerManagerInterface[] = "org.chromium.PowerManager";
static const char kPowerManagerServicePath[] = "/org/chromium/PowerManager";
static const char kPowerManagerServiceName[] = "org.chromium.PowerManager";
/* Methods exposed by powerd. */
static const char kDecreaseScreenBrightnessMethod[] = "DecreaseScreenBrightness";
static const char kIncreaseScreenBrightnessMethod[] = "IncreaseScreenBrightness";
static const char kHandleUserActivityMethod[] = "HandleUserActivity";
/* Values */
static const int kBrightnessTransitionGradual = 1;
static const int kBrightnessTransitionInstant = 2;
enum UserActivityType {
  USER_ACTIVITY_OTHER = 0,
  USER_ACTIVITY_BRIGHTNESS_UP_KEY_PRESS = 1,
  USER_ACTIVITY_BRIGHTNESS_DOWN_KEY_PRESS = 2,
  USER_ACTIVITY_VOLUME_UP_KEY_PRESS = 3,
  USER_ACTIVITY_VOLUME_DOWN_KEY_PRESS = 4,
  USER_ACTIVITY_VOLUME_MUTE_KEY_PRESS = 5,
};

static const char kSessionManagerInterface[] = "org.chromium.SessionManagerInterface";
static const char kSessionManagerServicePath[] = "/org/chromium/SessionManager";
static const char kSessionManagerServiceName[] = "org.chromium.SessionManager";

static const char kLoginPromptVisibleSignal[] = "LoginPromptVisible";
static const char kLoginPromptVisiibleRule[] = "interface='org.chromium.SessionManagerInterface',type='signal'";

static const char kLibCrosServiceName[] = "org.chromium.LibCrosService";
static const char kLibCrosServicePath[] = "/org/chromium/LibCrosService";
static const char kLibCrosServiceInterface[] =
  "org.chromium.LibCrosServiceInterface";
static const char kTakeDisplayOwnership[] = "TakeDisplayOwnership";
static const char kReleaseDisplayOwnership[] = "ReleaseDisplayOwnership";

#endif // FRECON_DBUS_API_H_