// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 UltraNote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ContextGroupTimeout.h"
#include <System/InterruptedException.h>

using namespace System;

ContextGroupTimeout::ContextGroupTimeout(Dispatcher& dispatcher, ContextGroup& contextGroup, std::chrono::nanoseconds timeout) :
  workingContextGroup(dispatcher),
  timeoutTimer(dispatcher) {
  workingContextGroup.spawn([&, timeout] {
    try {
      timeoutTimer.sleep(timeout);
      contextGroup.interrupt();
    } catch (InterruptedException&) {
    }
  });
}
