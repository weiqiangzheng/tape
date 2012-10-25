/*
 * Copyright (C) 2012 Square, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __ANDROID__

#include <android/log.h>
#define ANDROID_LOGGING_TAG "c-tape-lib"
#define MAX_MESSAGE_LENGTH 1024

#else

#include <execinfo.h>

#endif //__ANDROID__

#include "logutil.h"

static enum loglevel currentloglevel = _LOGLEVEL_WARN;
static enum loglevel currentDebugFailloglevel = 9999;


void _log_setlevel(enum loglevel ll) {
  currentloglevel = ll;
}

void _log_debug_failatlevel(enum loglevel ll) {
  currentDebugFailloglevel = ll;
}

static void printStackTrace();

int _log_vprintf(enum loglevel level, char* file, int line, char* msg, ...) {
  if (currentloglevel <= level) {
    va_list args;
    va_start (args, msg);

    #ifdef __ANDROID__
      
      char buf[MAX_MESSAGE_LENGTH];
      int n = vsnprintf(buf, MAX_MESSAGE_LENGTH, msg, args);
      //####jochen TODO: translate internal logging levels
      __android_log_print(ANDROID_LOG_WARN, ANDROID_LOGGING_TAG, "%s:%d [%d]  %s", file, line, level, buf);
      
    #else
      
      fprintf (stdout, "%s:%d [%d] ", file, line, level);
      vfprintf (stdout, msg, args);
      fprintf (stdout, "\n");
      if (currentloglevel >= currentDebugFailloglevel) {
        fprintf(stdout, "*** quitting, logged above debug fail level, see LOG_SETDEBUGFAILLEVEL_WARN or LOG_SETDEBUGFAILLEVEL_FATAL\n");
        printStackTrace();
        abort();
      }
      
    #endif
    va_end (args);

    return 1;
  }
  return 0;
}

#ifndef __ANDROID__

static void printStackTrace() {
  void* addrlist[100];
  int addrlen = backtrace(addrlist, (int)(sizeof(addrlist) / sizeof(void*)));
  if (addrlen == 0) {
    fprintf(stderr, "\n" );
    return;
  }
  char** symbols = backtrace_symbols(addrlist, addrlen);
  int i;
  for (i = 1; i < addrlen; i++ )
    fprintf(stderr, "%s\n", symbols[i]);
  free(symbols);
}

#endif