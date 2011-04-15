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
 * @file        __XSNumber.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Private implementation for the XSNumber class
 */

#include "XS.h"
#include "__XSNumber.h"

/*!
 * @var         __XSNumberClass
 * @abstract    Runtime class definition
 */
static const XSClassInfos __XSNumberClass =
{
    "XSNumber",             /* Class name */
    sizeof( __XSNumber ),   /* Object size */
    NULL,                   /* Constructor */
    NULL,                   /* Destructor */
    XSNumber_Init,          /* Default initializer */
    NULL,                   /* Object copy */
    NULL,                   /* Object description */
    NULL                    /* Object comparison */
};

/*!
 * @var         __XSNumberClassID
 * @abstract    Type ID for the runtine class
 */
XSClassID __XSNumberClassID;

void __XSNumber_Initialize( void )
{
    __XSNumberClassID = XSRuntime_RegisterClass( &__XSNumberClass );
}

uint64_t __XSNumber_GetUInt64Value( __XSNumber * n )
{
    if( n->types & __XSNUMBER_TYPE_BOOL )
    {
        return ( uint64_t )n->boolValue;
    }
    else if( n->types & __XSNUMBER_TYPE_SCHAR )
    {
        return ( uint64_t )n->sCharValue;
    }
    else if( n->types & __XSNUMBER_TYPE_UCHAR )
    {
        return ( uint64_t )n->uCharValue;
    }
    else if( n->types & __XSNUMBER_TYPE_SSHORT )
    {
        return ( uint64_t )n->sShortValue;
    }
    else if( n->types & __XSNUMBER_TYPE_USHORT )
    {
        return ( uint64_t )n->uShortValue;
    }
    else if( n->types & __XSNUMBER_TYPE_SINT )
    {
        return ( uint64_t )n->sIntValue;
    }
    else if( n->types & __XSNUMBER_TYPE_UINT )
    {
        return ( uint64_t )n->uIntValue;
    }
    else if( n->types & __XSNUMBER_TYPE_SLONG )
    {
        return ( uint64_t )n->sLongValue;
    }
    else if( n->types & __XSNUMBER_TYPE_ULONG )
    {
        return ( uint64_t )n->uLongValue;
    }
    else if( n->types & __XSNUMBER_TYPE_SLONGLONG )
    {
        return ( uint64_t )n->sLongLongValue;
    }
    else if( n->types & __XSNUMBER_TYPE_ULONGLONG )
    {
        return ( uint64_t )n->uLongLongValue;
    }
    else if( n->types & __XSNUMBER_TYPE_FLOAT )
    {
        return ( uint64_t )n->floatValue;
    }
    else if( n->types & __XSNUMBER_TYPE_DOUBLE )
    {
        return ( uint64_t )n->doubleValue;
    }
    else if( n->types & __XSNUMBER_TYPE_SINTEGER )
    {
        return ( uint64_t )n->sIntegerValue;
    }
    else if( n->types & __XSNUMBER_TYPE_UINTEGER )
    {
        return ( uint64_t )n->uIntegerValue;
    }
    
    return 0;
}