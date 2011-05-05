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
 * @file        __XSData.c
 * @brief       Private implementation for the XSData class
 * @author      Jean-David Gadina <macmade@eosgarden.com>
 */

#include "XS.h"
#include "__XSData.h"

/*!
 * @var         __XSDataClass
 * @brief       Runtime class definition
 */
static const XSClassInfos __XSDataClass =
{
    "XSData",           /* Class name */
    sizeof( __XSData ), /* Object size */
    NULL,               /* Constructor */
    __XSData_Destruct,  /* Destructor */
    XSData_Init,        /* Default initializer */
    __XSData_Copy,      /* Object copy */
    __XSData_ToString,  /* Object description */
    NULL                /* Object comparison */
};

/*!
 * @var         __XSDataClassID
 * @brief       Type ID for the runtime class
 */
XSClassID __XSDataClassID;

void __XSData_Initialize( void )
{
    __XSDataClassID = XSRuntime_RegisterClass( &__XSDataClass );
    
    XSRuntime_BindMethodToClassID( __XSDataClassID, ( void ( * )( void ) )XSData_Init, "Init", "void" );
    XSRuntime_BindMethodToClassID( __XSDataClassID, ( void ( * )( void ) )XSData_InitWithCapacity, "InitWithCapacity", "void" );
    XSRuntime_BindMethodToClassID( __XSDataClassID, ( void ( * )( void ) )XSData_InitWithBytes, "InitWithBytes", "void" );
    XSRuntime_BindMethodToClassID( __XSDataClassID, ( void ( * )( void ) )XSData_GetLength, "GetLength", "void" );
    XSRuntime_BindMethodToClassID( __XSDataClassID, ( void ( * )( void ) )XSData_GetBytes, "GetBytes", "void" );
    XSRuntime_BindMethodToClassID( __XSDataClassID, ( void ( * )( void ) )XSData_AppendBytes, "AppendBytes", "void" );
    XSRuntime_BindMethodToClassID( __XSDataClassID, ( void ( * )( void ) )XSData_GetBytesPointer, "GetBytesPointer", "void" );
}

void __XSData_Destruct( XSObject object )
{
    XSRelease( ( ( __XSData * )object )->bytes );
}

XSString __XSData_ToString( XSObject object )
{
    XSUInteger i;
    __XSData * data;
    XSString   description;
    
    description = XSString_Init( XSString_Alloc() );
    data        = ( __XSData * )object;
    
    XSString_AppendFormat( description, ( char * )"%lu bytes:", data->length );
    
    for( i = 0; i < data->length; i++ )
    {
        XSString_AppendFormat( description, ( char * )" 0x%02X", data->bytes[ i ] );
    }
    
    return XSAutorelease( description );
}

void __XSData_Copy( XSObject source, XSObject destination )
{
    __XSData * d1;
    __XSData * d2;
    
    d1 = ( __XSData * )source;
    d2 = ( __XSData * )destination;
    
    d2->bytes = XSCopy( d1->bytes );
}
