/*******************************************************************************
 * Copyright (c) 2011, Jean-David Gadina <macmade@eosgarden.com>
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/
 
/* $Id$ */

/*!
 * @file        __XSHost.c
 * @brief       Private implementation for the XSHost class
 * @author      Jean-David Gadina <macmade@eosgarden.com>
 */

#include "XS.h"
#include "__XSHost.h"

/*!
 * @var         __XSErrorClass
 * @brief       Runtime class definition
 */
static const XSClassInfos __XSHostClass =
{
    "XSHost",           /* Class name */
    sizeof( __XSHost ), /* Object size */
    __XSHost_Construct, /* Constructor */
    __XSHost_Destruct,  /* Destructor */
    NULL,               /* Default initializer */
    __XSHost_Copy,      /* Object copy */
    __XSHost_ToString,  /* Object description */
    NULL                /* Object comparison */
};

/*!
 * @var         __XSHostClassID
 * @brief       Type ID for the runtime class
 */
XSClassID __XSHostClassID;

void __XSHost_Initialize( void )
{
    __XSHostClassID = XSRuntime_RegisterClass( &__XSHostClass );
    
    XSRuntime_BindMethodToClassID( __XSHostClassID, ( void ( * )( void ) )XSHost_Init, "Init", "void" );
    XSRuntime_BindMethodToClassID( __XSHostClassID, ( void ( * )( void ) )XSHost_InitWithURL, "InitWithURL", "void" );
    XSRuntime_BindMethodToClassID( __XSHostClassID, ( void ( * )( void ) )XSHost_GetHost, "GetHost", "void" );
    XSRuntime_BindMethodToClassID( __XSHostClassID, ( void ( * )( void ) )XSHost_GetIP, "GetIP", "void" );
    XSRuntime_BindMethodToClassID( __XSHostClassID, ( void ( * )( void ) )XSHost_GetPort, "GetPort", "void" );
    XSRuntime_BindMethodToClassID( __XSHostClassID, ( void ( * )( void ) )XSHost_GetSocket, "GetSocket", "void" );
    XSRuntime_BindMethodToClassID( __XSHostClassID, ( void ( * )( void ) )XSHost_Connect, "Connect", "void" );
    XSRuntime_BindMethodToClassID( __XSHostClassID, ( void ( * )( void ) )XSHost_Disconnect, "Disconnect", "void" );
}

void __XSHost_Construct( XSObject object )
{
    __XSHost * host;
    
    host = ( __XSHost * )object;
}

void __XSHost_Destruct( XSObject object )
{
    __XSHost * host;
    
    host = ( __XSHost * )object;
    
    XSRelease( host->host );
    XSRelease( host->ip );
    
    if( host->isCopy == NO )
    {
        freeaddrinfo( host->infos );
    }
}

XSString __XSHost_ToString( XSObject object )
{
    __XSHost * host;
    XSString   description;
    
    host        = ( __XSHost * )object;
    description = XSString_Init( XSString_Alloc() );
    
    XSString_AppendFormat( description, ( char * )"%s (%s) : %u", XSString_CString( host->host ), XSString_CString( host->ip ), host->port );
    
    return XSAutorelease( description );
}

void __XSHost_Copy( XSObject source, XSObject destination )
{
    __XSHost * h1;
    __XSHost * h2;
    
    h1 = ( __XSHost * )source;
    h2 = ( __XSHost * )destination;
    
    h2->host   = XSCopy( h1->host );
    h2->ip     = XSCopy( h1->ip );
    h2->isCopy = YES;
}
