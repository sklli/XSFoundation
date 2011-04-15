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
 * @header      XSNumber.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Implementation for the XSNumber class
 */

#include "XS.h"
#include "__XSNumber.h"

extern XSClassID __XSNumberClassID;

XSStatic XSObject XSNumber_Alloc( void )
{
    return ( XSObject )XSRuntime_CreateInstance( __XSNumberClassID );
}

XSObject XSNumber_Init( XSObject xsThis )
{
    __XSNumber * num;
    
    num                 = ( __XSNumber * )xsThis;
    num->boolValue      = NO;
    num->sCharValue     = ( signed char )0;
    num->uCharValue     = ( unsigned char )0;
    num->sShortValue    = ( signed short )0;
    num->uShortValue    = ( unsigned short )0;
    num->sIntValue      = ( signed int )0;
    num->uIntValue      = ( unsigned int )0;
    num->sLongValue     = ( signed long )0;
    num->uLongValue     = ( unsigned long )0;
    num->sLongLongValue = ( signed long long )0;
    num->uLongLongValue = ( unsigned long long )0;
    num->floatValue     = ( float )0;
    num->doubleValue    = ( double )0;
    num->sIntegerValue  = ( XSInteger )0;
    num->uIntegerValue  = ( XSUInteger )0;
    num->types          = __XSNUMBER_TYPE_ALL;
    
    return xsThis;
}

XSNumber XSNumber_InitWithBool( XSNumber xsThis, BOOL value )
{
    __XSNumber * num;
    
    num            = ( __XSNumber * )xsThis;
    num->boolValue = value;
    num->types     = __XSNUMBER_TYPE_BOOL;
    
    return xsThis;
}

XSNumber XSNumber_InitWithChar( XSNumber xsThis, char value )
{
    __XSNumber * num;
    
    num             = ( __XSNumber * )xsThis;
    num->sCharValue = value;
    num->types      = __XSNUMBER_TYPE_SCHAR;
    
    return xsThis;
}

XSNumber XSNumber_InitWithUnsignedChar( XSNumber xsThis, unsigned char value )
{
    __XSNumber * num;
    
    num             = ( __XSNumber * )xsThis;
    num->uCharValue = value;
    num->types      = __XSNUMBER_TYPE_UCHAR;
    
    return xsThis;
}

XSNumber XSNumber_InitWithShort( XSNumber xsThis, short value )
{
    __XSNumber * num;
    
    num              = ( __XSNumber * )xsThis;
    num->sShortValue = value;
    num->types       = __XSNUMBER_TYPE_SSHORT;
    
    return xsThis;
}

XSNumber XSNumber_InitWithUnsignedShort( XSNumber xsThis, unsigned short value )
{
    __XSNumber * num;
    
    num              = ( __XSNumber * )xsThis;
    num->uShortValue = value;
    num->types       = __XSNUMBER_TYPE_USHORT;    
    return xsThis;
}

XSNumber XSNumber_InitWithInt( XSNumber xsThis, int value )
{
    __XSNumber * num;
    
    num            = ( __XSNumber * )xsThis;
    num->sIntValue = value;
    num->types     = __XSNUMBER_TYPE_SINT;    
    return xsThis;
}

XSNumber XSNumber_InitWithUnsignedInt( XSNumber xsThis, unsigned int value )
{
    __XSNumber * num;
    
    num            = ( __XSNumber * )xsThis;
    num->uIntValue = value;
    num->types     = __XSNUMBER_TYPE_UINT;    
    return xsThis;
}

XSNumber XSNumber_InitWithLong( XSNumber xsThis, long value )
{
    __XSNumber * num;
    
    num             = ( __XSNumber * )xsThis;
    num->sLongValue = value;
    num->types      = __XSNUMBER_TYPE_SLONG;    
    return xsThis;
}

XSNumber XSNumber_InitWithUnsignedLong( XSNumber xsThis, unsigned long value )
{
    __XSNumber * num;
    
    num             = ( __XSNumber * )xsThis;
    num->uLongValue = value;
    num->types      = __XSNUMBER_TYPE_ULONG;
    
    return xsThis;
}

XSNumber XSNumber_InitWithLongLong( XSNumber xsThis, long long value )
{
    __XSNumber * num;
    
    num                 = ( __XSNumber * )xsThis;
    num->sLongLongValue = value;
    num->types          = __XSNUMBER_TYPE_SLONGLONG;
    
    return xsThis;
}

XSNumber XSNumber_InitWithUnsignedLongLong( XSNumber xsThis, unsigned long long value )
{
    __XSNumber * num;
    
    num                 = ( __XSNumber * )xsThis;
    num->uLongLongValue = value;
    num->types          = __XSNUMBER_TYPE_ULONGLONG;
    
    return xsThis;
}

XSNumber XSNumber_InitWithFloat( XSNumber xsThis, float value )
{
    __XSNumber * num;
    
    num             = ( __XSNumber * )xsThis;
    num->floatValue = value;
    num->types      = __XSNUMBER_TYPE_FLOAT;
    
    return xsThis;
}

XSNumber XSNumber_InitWithDouble( XSNumber xsThis, double value )
{
    __XSNumber * num;
    
    num              = ( __XSNumber * )xsThis;
    num->doubleValue = value;
    num->types       = __XSNUMBER_TYPE_DOUBLE;
    
    return xsThis;
}

XSNumber XSNumber_InitWithInteger( XSNumber xsThis, XSInteger value )
{
    __XSNumber * num;
    
    num                = ( __XSNumber * )xsThis;
    num->sIntegerValue = value;
    num->types         = __XSNUMBER_TYPE_SINTEGER;
    
    return xsThis;
}

XSNumber XSNumber_InitWithUnsignedInteger( XSNumber xsThis, XSUInteger value )
{
    __XSNumber * num;
    
    num                = ( __XSNumber * )xsThis;
    num->uIntegerValue = value;
    num->types         = __XSNUMBER_TYPE_UINTEGER;
    
    return xsThis;
}

void XSNumber_SetBool( XSNumber xsThis, BOOL value )
{
    XSNumber_InitWithBool( xsThis, value );
}

void XSNumber_SetChar( XSNumber xsThis, char value )
{
    XSNumber_InitWithBool( xsThis, value );
}

void XSNumber_SetUnsignedChar( XSNumber xsThis, unsigned char value )
{
    XSNumber_InitWithUnsignedChar( xsThis, value );
}

void XSNumber_SetShort( XSNumber xsThis, short value )
{
    XSNumber_InitWithShort( xsThis, value );
}

void XSNumber_SetUnsignedShort( XSNumber xsThis, unsigned short value )
{
    XSNumber_InitWithUnsignedShort( xsThis, value );
}

void XSNumber_SetInt( XSNumber xsThis, int value )
{
    XSNumber_InitWithInt( xsThis, value );
}

void XSNumber_SetUnsignedInt( XSNumber xsThis, unsigned int value )
{
    XSNumber_InitWithUnsignedInt( xsThis, value );
}

void XSNumber_SetLong( XSNumber xsThis, long value )
{
    XSNumber_InitWithLong( xsThis, value );
}

void XSNumber_SetUnsignedLong( XSNumber xsThis, unsigned long value )
{
    XSNumber_InitWithUnsignedLong( xsThis, value );
}

void XSNumber_SetLongLong( XSNumber xsThis, long long value )
{
    XSNumber_InitWithLongLong( xsThis, value );
}

void XSNumber_SetUnsignedLongLong( XSNumber xsThis, unsigned long long value )
{
    XSNumber_InitWithUnsignedLongLong( xsThis, value );
}

void XSNumber_SetFloat( XSNumber xsThis, float value )
{
    XSNumber_InitWithFloat( xsThis, value );
}

void XSNumber_SetDouble( XSNumber xsThis, double value )
{
    XSNumber_InitWithDouble( xsThis, value );
}

void XSNumber_SetInteger( XSNumber xsThis, XSInteger value )
{
    XSNumber_InitWithInteger( xsThis, value );
}

void XSNumber_SetUnsignedInteger( XSNumber xsThis, XSUInteger value )
{
    XSNumber_InitWithUnsignedInteger( xsThis, value );
}

BOOL XSNumber_GetBool( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_BOOL ) == 0 )
    {
        uint64    = __XSNumber_GetUInt64Value( n );
        n->types |= __XSNUMBER_TYPE_BOOL;
        
        if( uint64 > 0 )
        {
            n->boolValue = YES;
        }
        else
        {
            n->boolValue = NO;
        }
    }
    
    return n->boolValue;
}

char XSNumber_GetChar( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_SCHAR ) == 0 )
    {
        uint64        = __XSNumber_GetUInt64Value( n );
        n->types     |= __XSNUMBER_TYPE_SCHAR;
        n->sCharValue = ( signed char )uint64;
    }
    
    return n->sCharValue;
}

unsigned char XSNumber_GetUnsignedChar( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_UCHAR ) == 0 )
    {
        uint64        = __XSNumber_GetUInt64Value( n );
        n->types     |= __XSNUMBER_TYPE_UCHAR;
        n->uCharValue = ( unsigned char )uint64;
    }
    
    return n->uCharValue;
}

short XSNumber_GetShort( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_SSHORT ) == 0 )
    {
        uint64         = __XSNumber_GetUInt64Value( n );
        n->types      |= __XSNUMBER_TYPE_SSHORT;
        n->sShortValue = ( signed short )uint64;
    }
    
    return n->sShortValue;
}

unsigned short XSNumber_GetUnsignedShort( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_USHORT ) == 0 )
    {
        uint64         = __XSNumber_GetUInt64Value( n );
        n->types      |= __XSNUMBER_TYPE_USHORT;
        n->uShortValue = ( unsigned short )uint64;
    }
    
    return n->uShortValue;
}

int XSNumber_GetInt( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_SINT ) == 0 )
    {
        uint64       = __XSNumber_GetUInt64Value( n );
        n->types    |= __XSNUMBER_TYPE_SINT;
        n->uIntValue = ( signed int )uint64;
    }
    
    return n->uIntValue;
}

unsigned int XSNumber_GetUnsignedInt( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_UINT ) == 0 )
    {
        uint64       = __XSNumber_GetUInt64Value( n );
        n->types    |= __XSNUMBER_TYPE_UINT;
        n->sIntValue = ( unsigned int )uint64;
    }
    
    return n->sIntValue;
}

long XSNumber_GetLong( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_SLONG ) == 0 )
    {
        uint64        = __XSNumber_GetUInt64Value( n );
        n->types     |= __XSNUMBER_TYPE_SLONG;
        n->sLongValue = ( signed long )uint64;
    }
    
    return n->sLongValue;
}

unsigned long XSNumber_GetUnsignedLong( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_ULONG ) == 0 )
    {
        uint64        = __XSNumber_GetUInt64Value( n );
        n->types     |= __XSNUMBER_TYPE_ULONG;
        n->uLongValue = ( unsigned long )uint64;
    }
    
    return n->uLongValue;
}

long long XSNumber_GetLongLong( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_SLONGLONG ) == 0 )
    {
        uint64            = __XSNumber_GetUInt64Value( n );
        n->types         |= __XSNUMBER_TYPE_SLONGLONG;
        n->sLongLongValue = ( signed long long )uint64;
    }
    
    return n->sLongLongValue;
}

unsigned long long XSNumber_GetUnsignedLongLong( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_ULONGLONG ) == 0 )
    {
        uint64            = __XSNumber_GetUInt64Value( n );
        n->types         |= __XSNUMBER_TYPE_ULONGLONG;
        n->uLongLongValue = ( unsigned long long )uint64;
    }
    
    return n->uLongLongValue;
}

float XSNumber_GetFloat( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_SINTEGER ) == 0 )
    {
        uint64    = __XSNumber_GetUInt64Value( n );
        n->types |= __XSNUMBER_TYPE_SINTEGER;
        
        if( n->types & __XSNUMBER_TYPE_DOUBLE )
        {
            n->floatValue = ( float )n->doubleValue;
        }
        else
        {
            n->floatValue = ( float )uint64;
        }
    }
    
    return n->floatValue;
}

double XSNumber_GetDouble( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
        
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_UINTEGER ) == 0 )
    {
        uint64    = __XSNumber_GetUInt64Value( n );
        n->types |= __XSNUMBER_TYPE_UINTEGER;
        
        if( n->types & __XSNUMBER_TYPE_FLOAT )
        {
            n->doubleValue = ( double )n->floatValue;
        }
        else
        {
            n->doubleValue = ( double )uint64;
        }
    }
    
    return n->doubleValue;
}

XSInteger XSNumber_GetInteger( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_UINTEGER ) == 0 )
    {
        uint64           = __XSNumber_GetUInt64Value( n );
        n->types        |= __XSNUMBER_TYPE_UINTEGER;
        n->sIntegerValue = ( XSInteger )uint64;
    }
    
    return n->sIntegerValue;
}

XSUInteger XSNumber_GetUnsignedInteger( XSNumber xsThis )
{
    __XSNumber * n;
    uint64_t     uint64;
    
    n = ( __XSNumber * )xsThis;
    
    if( ( n->types & __XSNUMBER_TYPE_UINTEGER ) == 0 )
    {
        uint64           = __XSNumber_GetUInt64Value( n );
        n->types        |= __XSNUMBER_TYPE_UINTEGER;
        n->uIntegerValue = ( XSUInteger )uint64;
    }
    
    return n->uIntegerValue;
}
