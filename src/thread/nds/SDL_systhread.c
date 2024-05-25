/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2014 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
	  claim that you wrote the original software. If you use this software
	  in a product, an acknowledgment in the product documentation would be
	  appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
	  misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "SDL_config.h"

#include "SDL_error.h"
#include "SDL_thread.h"
#include "../SDL_systhread.h"
#include "../SDL_thread_c.h"
#include <nds.h>

//#define STACKSIZE       (4 * 1024)

int ThreadEntry(void *arg)
{
	SDL_RunThread(arg);
}

int SDL_SYS_CreateThread(SDL_Thread *thread, void *args)
{
	thread->handle = cothread_create(ThreadEntry, args, 0, 0);
	
	thread->threadid = (int) thread->handle;
	if (!thread->threadid)
	{
	SDL_SetError("Create CoThread failed");
	return(-1);
	}

	return 0;
}

void SDL_SYS_SetupThread(void)
{
	 //Nothing, probably
}

Uint32 SDL_ThreadID(void)
{
	u32 threadID=0;
	threadID = cothread_get_current();

	return threadID;
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
	cothread_yield();
}

void SDL_SYS_KillThread(SDL_Thread *thread)
{
	cothread_delete(thread->handle);
}

