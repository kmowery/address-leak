/*
 * Copyright (C) 2011 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "WKPagePrivateMac.h"

#include "WKAPICast.h"
#include "WebContext.h"
#include "WebPageGroup.h"
#include "WebPageProxy.h"
#include "WebPreferences.h"

using namespace WebKit;

pid_t WKPageGetProcessIdentifier(WKPageRef pageRef)
{
    return toImpl(pageRef)->processIdentifier();
}

bool WKPageIsURLKnownHSTSHost(WKPageRef page, WKURLRef url)
{
    WebPageProxy* webPageProxy = toImpl(page);
    bool privateBrowsingEnabled = webPageProxy->pageGroup()->preferences()->privateBrowsingEnabled();

    return webPageProxy->process()->context()->isURLKnownHSTSHost(toImpl(url)->string(), privateBrowsingEnabled);
}

static void callGetPlugInInformationBlockAndDispose(WKDictionaryRef resultValue, WKErrorRef error, void* context)
{
    WKPageGetPlugInInformationBlock block = (WKPageGetPlugInInformationBlock)context;
    block(resultValue, error);
    Block_release(block);
}

void WKPageGetPlugInInformation(WKPageRef pageRef, pid_t plugInProcessID, WKPageGetPlugInInformationBlock block)
{
    toImpl(pageRef)->getPlugInInformation(plugInProcessID, DictionaryCallback::create(Block_copy(block), callGetPlugInInformationBlockAndDispose));
}
