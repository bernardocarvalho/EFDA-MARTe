/*
 * Copyright 2011 EFDA | European Fusion Development Agreement
 *
 * Licensed under the EUPL, Version 1.1 or - as soon they 
   will be approved by the European Commission - subsequent  
   versions of the EUPL (the "Licence"); 
 * You may not use this work except in compliance with the 
   Licence. 
 * You may obtain a copy of the Licence at: 
 *  
 * http://ec.europa.eu/idabc/eupl
 *
 * Unless required by applicable law or agreed to in 
   writing, software distributed under the Licence is 
   distributed on an "AS IS" basis, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either 
   express or implied. 
 * See the Licence for the specific language governing 
   permissions and limitations under the Licence. 
 *
 * $Id: SyslogRelay.h 3 2012-01-15 16:26:07Z aneto $
 *
**/
#if !defined(SYSLOG_RELAY_PLUGIN)
#define SYSLOG_RELAY_PLUGIN

#include "LoggerMessageQueue.h"
#include "LoggerMessage.h"
#include "GCReferenceContainer.h"
#include "Threads.h"
#include "UDPLoggerPlugin.h"
#include "File.h"
#include "Directory.h"
#include "CDBExtended.h"
#include <syslog.h>

/**
 * @file
 * Plugin implementation which sinks the messages into the syslog
 */
OBJECT_DLL(SyslogRelay)
class SyslogRelay : public UDPLoggerPlugin{
private:
OBJECT_DLL_STUFF(SyslogRelay)

public:

    SyslogRelay(){
    }

    virtual ~SyslogRelay(){
    }

    virtual     bool                ObjectLoadSetup(
            ConfigurationDataBase & info,
            StreamInterface *       err){

        bool ret = UDPLoggerPlugin::ObjectLoadSetup(info, err);
        return ret;
    }

    virtual bool TextMenu(
                    StreamInterface &               in,
                    StreamInterface &               out){
        return True;
    }

    virtual void ProcessMessage(GCRTemplate<LoggerMessage> msg);

};

#endif

