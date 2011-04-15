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
 * @header      XSBag.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Implementation for the XSBag class
 */

#include "XS.h"
#include "__XSBag.h"

#define __XSBAG_DEFAULT_CAPACITY 256

extern XSClassID __XSBagClassID;

XSStatic XSBag XSBag_Alloc( void )
{
    return ( XSBag )XSRuntime_CreateInstance( __XSBagClassID );
}

XSObject XSBag_Init( XSObject xsThis )
{
    return XSBag_InitWithCapacity( xsThis, __XSBAG_DEFAULT_CAPACITY );
}

XSBag XSBag_InitWithCapacity( XSBag xsThis, XSUInteger capacity )
{
    __XSBag * bag;
    
    bag = ( __XSBag * )XSBag_Init( xsThis );
    
    if( NULL == ( bag->values = ( void ** )( XSAlloc( capacity * sizeof( void * ) ) ) ) )
    {
        return NULL;
    }
    
    bag->count           = 0;
    bag->capacity        = capacity;
    bag->initialCapacity = capacity;
    
    return xsThis;
}

XSBag XSBag_InitWithValues( XSBag xsThis, void * value1, ... )
{
    void    * value;
    va_list   args;
    __XSBag * bag;
    
    bag = ( __XSBag * )XSBag_Init( xsThis );
    
    if( value1 == NULL )
    {
        return xsThis;
    }
    
    va_start( args, value1 );
    
    while( NULL != ( value = va_arg( args, void * ) ) )
    {
        XSBag_AddValue( xsThis, value );
    }
    
    va_end( args );
    
    return xsThis;
}

XSUInteger XSBag_Count( XSBag xsThis )
{
    return ( ( __XSBag * )xsThis )->count;
}

BOOL XSBag_ContainsValue( XSBag xsThis, void * value )
{
    __XSBag  * bag;
    XSUInteger i;
    
    bag = ( __XSBag * )XSBag_Init( xsThis );
    
    for( i = 0; i < XSBag_Count( xsThis ); i++ )
    {
        if( bag->values[ i ] == value )
        {
            return YES;
        }
    }
    
    return NO;
}

void XSBag_AddValue( XSBag xsThis, void * value )
{
    __XSBag  * bag;
    void     * values;
    
    bag = ( __XSBag * )XSBag_Init( xsThis );
    
    if( bag->count == bag->capacity )
    {
        values = XSRealloc( bag->values, ( bag->count + bag->initialCapacity ) * sizeof( void * ) );
        
        if( values == NULL )
        {
            return;
        }
        
        bag->values    = values;
        bag->capacity += bag->initialCapacity;
    }
    
    bag->values[ bag->count++ ] = XSRetain( value );
}

void XSBag_RemoveValue( XSBag xsThis, void * value )
{
    BOOL       found;
    __XSBag  * bag;
    XSUInteger i;
    
    bag   = ( __XSBag * )XSBag_Init( xsThis );
    found = NO;
    
    for( i = 0; i < XSBag_Count( xsThis ); i++ )
    {
        if( found == YES )
        {
            bag->values[ i - 1 ] = bag->values[ i ];
            bag->values[ i ]     = NULL;
        }
        
        if( bag->values[ i ] == value )
        {
            XSRelease( bag->values[ i ] );
            bag->count--;
            
            bag->values[ i ] = NULL;
            found            = YES;
        }
    }
}

void XSBag_ReplaceValue( XSBag xsThis, void * valueOld, void * valueNew )
{
    __XSBag  * bag;
    XSUInteger i;
    
    bag = ( __XSBag * )XSBag_Init( xsThis );
    
    for( i = 0; i < XSBag_Count( xsThis ); i++ )
    {
        if( bag->values[ i ] == valueOld )
        {
            XSRelease( bag->values[ i ] );
            
            bag->values[ i ] = XSRetain( valueNew );
        }
    }
}

XSUInteger XSBag_Index( XSBag xsThis )
{
    __XSBag  * bag;
    
    bag = ( __XSBag * )xsThis;
    
    return bag->cur;
}

void * XSBag_Current( XSBag xsThis )
{
    __XSBag  * bag;
    
    bag = ( __XSBag * )xsThis;
    
    return bag->values[ bag->cur ];
}

void * XSBag_Next( XSBag xsThis )
{
    __XSBag  * bag;
    
    bag = ( __XSBag * )xsThis;
    
    if( ( bag->cur + 1 ) == bag->count )
    {
        return NULL;
    }
    
    return bag->values[ ++bag->cur ];
}

void * XSBag_Previous( XSBag xsThis )
{
    __XSBag  * bag;
    
    bag = ( __XSBag * )xsThis;
    
    if( bag->cur == 0 )
    {
        return bag->values[ 0 ];
    }
    
    return bag->values[ --bag->cur ];
}

void XSBag_Rewind( XSBag xsThis )
{
    __XSBag  * bag;
    
    bag      = ( __XSBag * )xsThis;
    bag->cur = 0;
}
