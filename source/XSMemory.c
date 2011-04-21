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
 * @file        XSMemory.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Implementation of the memory management functions and implementation for the XSAutoreleasePool class
 */

#include "XS.h"
#include "__XSMemory.h"
#include "__XSMemoryDebug.h"

extern XSClassID __XSAutoreleasePoolClassID;

static size_t __xsmemory_alloc = 0;

XSStatic XSObject XSAutoreleasePool_Alloc( void )
{
    return ( XSObject )XSRuntime_CreateInstance( __XSAutoreleasePoolClassID );
}

XSObject XSAutoreleasePool_Init( XSObject xsThis )
{
    __XSAutoreleasePool * ap;
    
    ap = ( __XSAutoreleasePool * )xsThis;
    
    if( __xsmemory_ar_pools_num == XS_MEMORY_MAX_AR_POOLS )
    {
        XSFatalError( "maximum number of auto-release pools reached: %u", XS_MEMORY_MAX_AR_POOLS );
    }
    
    if( NULL == ( ap->objects = ( void ** )XSAlloc( sizeof( void * ) * XS_MEMORY_NUM_OBJECTS ) ) )
    {
        free( ap );
        XSFatalError( "unable to allocate memory for the auto-release pool" );
    }
    
    XSDebugLog( XSDebugLogLevelDebug, "Creating new auto-release pool (%p)", ( void * )ap );
    
    ap->size                                         = XS_MEMORY_NUM_OBJECTS;
    ap->numObjects                                   = 0;
    __xsmemory_ar_pools[ __xsmemory_ar_pools_num++ ] = ap;
    
    return ( XSAutoreleasePool )ap;
}

XSStatic void XSAutoreleasePool_Drain( void )
{
    __XSAutoreleasePool * ap;
    
    ap = __XSMemory_GetCurrentAutoreleasePool();
    
    XSDebugLog( XSDebugLogLevelDebug, "Draining current auto-release pool (%p)", ( void * )ap );
    
    __XSMemory_AutoreleasePoolDrain( ap );
}

void * XSAllocWithInfos( const char * file, int line, const char * func, size_t size, ... )
{
    static size_t        allocID = 0;
    va_list              args;
    __XSMemoryObject   * o;
    char               * ptr;
    XSClassID            classID;
    const XSClassInfos * cls;
    
    va_start( args, size );
    
    classID = va_arg( args, XSClassID );
    
    va_end( args );
    
    o = ( __XSMemoryObject * )calloc( sizeof( __XSMemoryObject ) + size + 12, 1 );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    if( classID > 0 && XSRuntime_GetClassForClassID( classID ) != NULL )
    {
        o->classID = classID;
    }
    else
    {
        classID = 0;
    }
    
    o->retainCount = 1;
    o->allocID     = allocID++;
    o->size        = size;
    
    o->fence[ 0  ] = 0;
    o->fence[ 1  ] = 'X';
    o->fence[ 2  ] = 'S';
    o->fence[ 3  ] = '_';
    o->fence[ 4  ] = 'M';
    o->fence[ 5  ] = 'E';
    o->fence[ 6  ] = 'M';
    o->fence[ 7  ] = 'D';
    o->fence[ 8  ] = 'A';
    o->fence[ 9  ] = 'T';
    o->fence[ 10 ] = 'A';
    o->fence[ 11 ] = 0;
    
    ptr     =  ( char * )o;
    ptr    += ( sizeof( __XSMemoryObject ) );
    o->data = ptr;
    
    ptr[ size + 0  ] = 0;
    ptr[ size + 1  ] = 'X';
    ptr[ size + 2  ] = 'S';
    ptr[ size + 3  ] = '_';
    ptr[ size + 4  ] = 'M';
    ptr[ size + 5  ] = 'E';
    ptr[ size + 6  ] = 'M';
    ptr[ size + 7  ] = 'D';
    ptr[ size + 8  ] = 'A';
    ptr[ size + 9  ] = 'T';
    ptr[ size + 10 ] = 'A';
    ptr[ size + 11 ] = 0;
    
    if( classID > 0 )
    {
        cls = XSRuntime_GetClassForClassID( o->classID );
        
        if(  cls != NULL && cls->construct != NULL )
        {
            cls->construct( ptr );
        }
    }
    
    XSHash( ptr );
    
    __xsmemory_alloc++;
    
    __XSMemoryDebug_NewRecord( o, file, line, func );
    
    return ptr;
}

void * XSReallocWithInfos( const char * file, int line, const char * func, void * ptr, size_t size )
{
    __XSMemoryObject * o1;
    __XSMemoryObject * o2;
    char             * cptr;
    
    if( ptr == NULL )
    {
        return NULL;
    }
    
    o1 = __XSMemory_GetMemoryObject( ptr );
    o2 = o1;
    o2 = ( __XSMemoryObject * )realloc( o2, size + sizeof( __XSMemoryObject ) + 12 );
    
    if( o2 == NULL )
    {
        return NULL;
    }
    
    o2->size  = size;
    cptr      =  ( char * )o2;
    cptr     += ( sizeof( __XSMemoryObject ) );
    o2->data  = cptr;
    
    cptr[ size + 0  ] = 0;
    cptr[ size + 1  ] = 'X';
    cptr[ size + 2  ] = 'S';
    cptr[ size + 3  ] = '_';
    cptr[ size + 4  ] = 'M';
    cptr[ size + 5  ] = 'E';
    cptr[ size + 6  ] = 'M';
    cptr[ size + 7  ] = 'D';
    cptr[ size + 8  ] = 'A';
    cptr[ size + 9  ] = 'T';
    cptr[ size + 10 ] = 'A';
    cptr[ size + 11 ] = 0;
    
    __XSMemoryDebug_UpdateRecord( o1, o2, file, line, func );
    
    return o2->data;
}

void * XSRetain( void * ptr )
{
    __XSMemoryObject * o;
    
    if( ptr == NULL )
    {
        return NULL;
    }
    
    o = __XSMemory_GetMemoryObject( ptr );
    
    o->retainCount++;
    
    return ptr;
}

void * XSReleaseWithInfos( const char * file, int line, const char * func, void * ptr )
{
    __XSMemoryObject   * o;
    const XSClassInfos * cls;
    
    if( ptr == NULL )
    {
        return NULL;
    }
    
    o = __XSMemory_GetMemoryObject( ptr );
    
    __XSMemoryDebug_ReleaseRecord( o, NO, file, line, func );
    
    if( o->retainCount > 0 )
    {
        o->retainCount--;
    }
    
    if( o->retainCount == 0 )
    {
        if( o->classID != 0 )
        {
            cls = XSRuntime_GetClassForClassID( o->classID );
            
            if( cls != NULL && cls->destruct != NULL )
            {
                cls->destruct( ptr );
            }
        }
        
        __XSMemoryDebug_ReleaseRecord( o, YES, file, line, func );
        free( o );
        
        __xsmemory_alloc--;
        
        return NULL;
    }
    
    return ptr;
}

void * XSAutorelease( void * ptr )
{
    __XSAutoreleasePool * ap;
    
    if( ptr == NULL )
    {
        return NULL;
    }
    
    ap = __XSMemory_GetCurrentAutoreleasePool();
    
    if( ap == NULL )
    {
        XSLog( "Warning: autoreleasing object %p with no auto-release pool in place - leaking memory", ptr );
    }
    
    if( ap->numObjects == ap->size )
    {
        ap->objects = ( void ** )XSRealloc( ap->objects, sizeof( void * ) * ( ap->size + XS_MEMORY_NUM_OBJECTS ) );
        
        if( ap->objects == NULL )
        {
            XSFatalError( "unable to allocate memory for the auto-release pool" );
        }
        
        ap->size += XS_MEMORY_NUM_OBJECTS;
    }
    
    ap->objects[ ap->numObjects++ ] = ptr;
    
    return ptr;
}

void * XSAutoAllocWithInfos( const char * file, int line, const char * func, size_t size )
{
    void * ptr;
    
    ptr = XSAllocWithInfos( file, line, func, size );
    
    XSAutorelease( ptr );
    
    return ptr;
}

void * XSCopyWithInfos( const char * file, int line, const char * func, void * ptr )
{
    __XSMemoryObject   * o;
    void               * ptr2;
    const XSClassInfos * cls;
    
    if( ptr == NULL )
    {
        return NULL;
    }
    
    o = __XSMemory_GetMemoryObject( ptr );
    
    if( o->classID != 0 )
    {
        cls  = XSRuntime_GetClassForClassID( o->classID );
        ptr2 = XSAllocWithInfos( file, line, func, o->size, o->classID );
        
        if( ptr2 == NULL )
        {
            return NULL;
        }
        
        memcpy( ptr2, o->data, o->size );
        
        if(  cls != NULL && cls->copy != NULL )
        {
            cls->copy( ptr, ptr2 );
        }
    }
    else
    {
        ptr2 = XSAllocWithInfos( file, line, func, o->size );
        
        if( ptr2 == NULL )
        {
            return NULL;
        }
        
        memcpy( ptr2, o->data, o->size );
    }
    
    return ptr2;
}

BOOL XSEquals( void * ptr1, void * ptr2 )
{
    __XSMemoryObject   * o;
    const XSClassInfos * cls;
    
    if( ptr1 == NULL && ptr2 == NULL )
    {
        return YES;
    }
    
    if( ptr1 == NULL || ptr2 == NULL )
    {
        return NO;
    }
    
    o = __XSMemory_GetMemoryObject( ptr1 );
    
    if( o->classID != 0 )
    {
        cls = XSRuntime_GetClassForClassID( o->classID );
        
        if(  cls != NULL && cls->equals != NULL )
        {
            return cls->equals( ptr1, ptr2 );
        }
    }
    
    return ( ptr1 == ptr2 ) ? YES : NO;
}

const char * XSHash( void * ptr )
{
    __XSMemoryObject   * o;
    const XSClassInfos * cls;
    Str255               size;
    
    o = __XSMemory_GetMemoryObject( ptr );
    
    if( strlen( ( char * )o->hash ) )
    {
        return ( const char * )o->hash;
    }
    
    if( o->classID != 0 )
    {
        cls = XSRuntime_GetClassForClassID( o->classID );
        
        utoa( cls->instanceSize, ( char * )size, 10 );

        strcat( ( char * )o->hash, "HASH:" );
        sprintf( ( char * )( o->hash + strlen( ( char * )o->hash ) ), "%08X", ( unsigned int )o->classID );
        strcat( ( char * )o->hash, ":" );
        strcat( ( char * )o->hash, cls->className );
        strcat( ( char * )o->hash, ":" );
        sprintf( ( char * )( o->hash + strlen( ( char * )o->hash ) ), "%08X", ( unsigned int )o->allocID );
        strcat( ( char * )o->hash, ":" );
        strcat( ( char * )o->hash, ( char * )size );
        
        return ( const char * )o->hash;
    }
    
    strcat( ( char * )o->hash, "HASH:00000000:NONE:" );
    sprintf( ( char * )( o->hash + strlen( ( char * )o->hash ) ), "%08X", ( unsigned int )o->allocID );
    utoa( o->size, ( char * )size, 10 );
    strcat( ( char * )o->hash, ":" );
    strcat( ( char * )o->hash, ( char * )size );
    
    return ( const char * )o->hash;
}

XSUInteger XSGetRetainCount( void * ptr )
{
    __XSMemoryObject * o;
    
    if( ptr == NULL )
    {
        return 0;
    }
    
    o = __XSMemory_GetMemoryObject( ptr );
    
    return o->retainCount;
}

size_t XSGetAllocationCount( void )
{
    return __xsmemory_alloc;
}
