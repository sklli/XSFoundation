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
 * @header      XSURL.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Implementation for the XSURL class
 */

#include "XS.h"
#include "__XSURL.h"

extern XSClassID __XSURLClassID;

XSStatic XSObject XSURL_Alloc( void )
{
    return ( XSObject )XSRuntime_CreateInstance( __XSURLClassID );
}

XSObject XSURL_Init( XSObject xsThis )
{
    return xsThis;
}

XSObject XSURL_InitWithString( XSObject xsThis, XSString str )
{
    return XSURL_InitWithCString( xsThis, ( char * )XSString_CString( str ) );
}

XSObject XSURL_InitWithCString( XSObject xsThis, char * str )
{
    __XSURL * url;
    char    * parts_orig;
    char    * parts;
    char    * search;
    
    url   = ( __XSURL * )xsThis;
    parts = XSAlloc( sizeof( char ) * ( strlen( str ) + 1 ) );
    
    if( parts == NULL )
    {
        return NULL;
    }
    
    strcpy( parts, str );
    
    parts_orig = parts;
    search     = strstr( parts, "://" );
    
    if( search != NULL )
    {
        search[ 0 ] = 0;
        url->scheme = XSString_InitWithCString( XSString_Alloc(), parts ); 
    }
    
    search += 3;
    parts   = search;
    search  = strchr( parts, ':' );
    
    if( search != NULL )
    {
        search[ 0 ] = 0;
        url->domain = XSString_InitWithCString( XSString_Alloc(), parts );
        search     += 1;
        parts       = search;
        search      = strstr( parts, "/" );
        
        if( search != NULL )
        {
            search[ 0 ] = 0;
            url->port   = atol( parts );
            parts      += strlen( parts ) + 1;
        }
    }
    else
    {
        search  = strstr( parts, "/" );
        
        if( search == NULL )
        {
            url->domain = XSString_InitWithCString( XSString_Alloc(), parts );
        }
        else
        {
            search[ 0 ] = 0;
            url->domain = XSString_InitWithCString( XSString_Alloc(), parts );
            search     += 1;
            parts       = search;
        }
    }
    
    search = strchr( parts, '?' );
    
    if( search != NULL )
    {
        search[ 0 ] = 0;
        url->path   = XSString_InitWithCString( XSString_Alloc(), parts );
        search     += 1;
        parts       = search;
        search      = strchr( parts, '#' );
        
        if( search != NULL )
        {
            search[ 0 ] = 0;
            url->query  = XSString_InitWithCString( XSString_Alloc(), parts );
            search     += 1;
            parts       = search;
            
            if( strlen( search ) )
            {
                url->fragment = XSString_InitWithCString( XSString_Alloc(), parts );
            }
        }
        
    }
    else
    {
        search = strchr( parts, '#' );
        
        if( search != NULL )
        {
            search[ 0 ] = 0;
            url->path   = XSString_InitWithCString( XSString_Alloc(), parts );
            search     += 1;
            parts       = search;
            
            if( strlen( search ) )
            {
                url->fragment = XSString_InitWithCString( XSString_Alloc(), parts );
            }
        }
        else
        {
            url->path = XSString_InitWithCString( XSString_Alloc(), parts );
        }
    }
    
    XSRelease( parts_orig );
    
    return xsThis;
}

XSAutoreleased XSString XSURL_GetURL( XSObject xsThis )
{
    __XSURL * url;
    XSString  str;
    
    url = ( __XSURL * )xsThis;
    str = XSString_Init( XSString_Alloc() );
    
    if( url->scheme != NULL )
    {
        XSString_AppendFormat( str, ( char * )"%s://", XSString_CString( url->scheme ) );
    }
    
    if( url->domain != NULL )
    {
        XSString_AppendString( str, url->domain );
    }
    
    if( url->port != 0 )
    {
        XSString_AppendFormat( str, ( char * )":%u", url->port );
    }
    
    XSString_AppendCString( str, ( char * )"/" );
    
    if( url->path != NULL )
    {
        XSString_AppendFormat( str, ( char * )"%s", XSString_CString( url->path ) );
    }
    
    if( url->query != NULL )
    {
        XSString_AppendFormat( str, ( char * )"?%s", XSString_CString( url->query ) );
    }
    
    if( url->fragment != NULL )
    {
        XSString_AppendFormat( str, ( char * )"#%s", XSString_CString( url->fragment ) );
    }
    
    return XSAutorelease( str );
}

void XSURL_SetScheme( XSObject xsThis, XSString scheme )
{
    __XSURL * url;
    
    url = ( __XSURL * )xsThis;
    
    XSRelease( url->scheme );
    
    url->scheme = XSRetain( scheme );
}

void XSURL_SetDomain( XSObject xsThis, XSString domain )
{
    __XSURL * url;
    
    url = ( __XSURL * )xsThis;
    
    XSRelease( url->domain );
    
    url->domain = XSRetain( domain );
}

void XSURL_SetPort( XSObject xsThis, XSUInteger port )
{
    __XSURL * url;
    
    url       = ( __XSURL * )xsThis;
    url->port = port;
}

void XSURL_SetPath( XSObject xsThis, XSString path )
{
    __XSURL * url;
    
    url = ( __XSURL * )xsThis;
    
    XSRelease( url->path );
    
    url->path = XSRetain( path );
}

void XSURL_SetQuery( XSObject xsThis, XSString query )
{
    __XSURL * url;
    
    url = ( __XSURL * )xsThis;
    
    XSRelease( url->query );
    
    url->query = XSRetain( query );
}

void XSURL_SetFragment( XSObject xsThis, XSString fragment )
{
    __XSURL * url;
    
    url = ( __XSURL * )xsThis;
    
    XSRelease( url->fragment );
    
    url->fragment = XSRetain( fragment );
}

XSAutoreleased XSString XSURL_GetScheme( XSObject xsThis )
{
    return ( ( __XSURL * )xsThis )->scheme;
}

XSAutoreleased XSString XSURL_GetDomain( XSObject xsThis )
{
    return ( ( __XSURL * )xsThis )->domain;
}

XSUInteger XSURL_GetPort( XSObject xsThis )
{
    __XSURL * url;
    
    url = ( __XSURL * )xsThis;
    
    if( url->port == 0 && XSString_IsEqualToString( url->scheme, XSSTR( ( char * )"http" ) ) )
    {
        return 80;
    }
    
    if( url->port == 0 && XSString_IsEqualToString( url->scheme, XSSTR( ( char * )"https" ) ) )
    {
        return 443;
    }
    
    return url->port;
}

XSAutoreleased XSString XSURL_GetPath( XSObject xsThis )
{
    return ( ( __XSURL * )xsThis )->path;
}

XSAutoreleased XSString XSURL_GetQuery( XSObject xsThis )
{
    return ( ( __XSURL * )xsThis )->query;
}

XSAutoreleased XSString XSURL_GetFragment( XSObject xsThis )
{
    return ( ( __XSURL * )xsThis )->fragment;
}
