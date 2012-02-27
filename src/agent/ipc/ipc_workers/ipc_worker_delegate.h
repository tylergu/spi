/*
 * Copyright (c) 1996-2011 Barton P. Miller
 *
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 *
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

// The base class for various IPC workers. Possible IPC workers include:
// - TCP worker
// - UDP worker
// - Pipe worker

#ifndef _IPC_WORKER_DELEGATE_H_
#define _IPC_WORKER_DELEGATE_H_

namespace sp {


	class SpIpcWorkerDelegate {

  public:
    // An entry_payload function does two things:
    // 1. tracing: user-defined logic
    // 2. propagation: propagate instrumentation
    // Here we let user determine if it is okay to trace
		// This set_* function is used by the sender-end process, to determine
    // whether or not the process who owns this worker instance can start
    // tracing
    virtual void set_start_tracing(char yes_or_no,
                                   SpChannel* c) = 0;

		// This is used by the process who owns this worker instance
    virtual void set_start_tracing(char yes_or_no) = 0;

		// Query if it's okay to trace on local end of the channel:
    // 1. For Write-channel, it always return 1 (true)
    // 2. For Read-channel, it should be synchronized by remote process
    // Used by the process who owns this Worker instance.
    virtual char start_tracing(int fd) = 0;

		// Inject the agent shared library to the other end of a channel
    virtual bool inject(SpChannel*, char* agent_path = NULL,
                        char* injector_path = NULL,
												char* ijagent_path = NULL) = 0;

    // Get IPC channel from a file descriptor.
    // Input Param: fd -- the file descriptor
    // Input Param: rw -- specify whether the channel is read-only or
    // write-only
    // Return NULL if not a valid IPC channel; otherwise, the channel.
    virtual SpChannel* get_channel(int fd,
                                   ChannelRW rw,
                                   void* arg = NULL);

		virtual ~SpIpcWorkerDelegate() {}
  protected:
    // fd-to-SpChannel mapping
    typedef std::map<long, SpChannel*> ChannelMap;
    ChannelMap channel_map_write_;
    ChannelMap channel_map_read_;

		// Create a channel.
    // Assumption: the channel for this fd has not yet existed
		virtual SpChannel* create_channel(int fd,
                                      ChannelRW rw,
                                      void*) = 0;
	};


}

#endif  // _IPC_WORKER_DELEGATE_H_ */