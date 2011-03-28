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
 * @file        
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    
 */

#include "XS.h"
#include "private/__XSMemory.h"

XSAutoreleasePoolRef XSAutoreleasePool_Create( void )
{
    XSAutoreleasePool * ap;
    
    if( __xsmemory_ar_pools_num == XS_MEMORY_MAX_AR_POOLS )
    {
        fprintf( stderr, "Maximum number of auto-release pools reached: %u\n", XS_MEMORY_MAX_AR_POOLS );
        exit( EXIT_FAILURE );
    }
    
    if( NULL == ( ap = __XSAutoreleasePool_Alloc() ) )
    {
        fprintf( stderr, "Unable to allocate memory for the auto-release pool\n" );
        exit( EXIT_FAILURE );
    }
    
    if( NULL == ( ap->objects = ( void ** )calloc( sizeof( void * ), XS_MEMORY_NUM_OBJECTS ) ) )
    {
        free( ap );
        fprintf( stderr, "Unable to allocate memory for the auto-release pool\n" );
        exit( EXIT_FAILURE );
    }
    
    ap->size                                         = XS_MEMORY_NUM_OBJECTS;
    ap->num_objects                                  = 0;
    __xsmemory_ar_pools[ __xsmemory_ar_pools_num++ ] = ap;
    
    return ( XSAutoreleasePoolRef )ap;
}

void XSAutoreleasePool_Drain( void )
{
    XSAutoreleasePool * ap;
    
    ap = __XSMemory_GetCurrentAutoreleasePool();
    
    __XSMemory_AutoreleasePoolDrain( ap );
}

void * XSAlloc( size_t size, ... )
{
    va_list                      args;
    __XSMemoryObject           * o;
    char                       * ptr;
    XSTypeID                     typeID;
    const XSRuntimeClass const * cls;
    
    va_start( args, size );
    
    typeID = va_arg( args, XSTypeID );
    
    o = calloc( sizeof( __XSMemoryObject ) + size, 1 );
    
    if( o == NULL )
    {
        return NULL;
    }
    
    if( typeID > 0 )
    {
        o->typeID = typeID;
    }
    
    o->retain_count = 1;
    o->size         = size;
    
    ptr     =  ( char * )o;
    ptr    += ( sizeof( __XSMemoryObject ) );
    o->data = ptr;
    
    if( typeID > 0 )
    {
        cls = XSRuntime_GetClassForTypeID( o->typeID );
        
        if( cls->init != NULL )
        {
            cls->init( ptr );
        }
    }
    
    return ptr;
}

void * XSCopy( void * ptr )
{
    __XSMemoryObject           * o;
    void                       * ptr2;
    const XSRuntimeClass const * cls;
    
    if( ptr == NULL )
    {
        return NULL;
    }
    
    o = __XSMemory_GetMemoryObject( ptr );
    
    if( o->typeID != 0 )
    {
        cls  = XSRuntime_GetClassForTypeID( o->typeID );
        ptr2 = XSAlloc( o->size, o->typeID );
        
        if( ptr2 == NULL )
        {
            return NULL;
        }
        
        memcpy( ptr2, o->data, o->size );
        
        if( cls->copy != NULL )
        {
            cls->copy( ptr, ptr2 );
        }
    }
    else
    {
        ptr2 = XSAlloc( o->size );
        
        if( ptr2 == NULL )
        {
            return NULL;
        }
        
        memcpy( ptr2, o->data, o->size );
    }
    
    return ptr2;
}

void XSRelease( void * ptr )
{
    __XSMemoryObject           * o;
    const XSRuntimeClass const * cls;
    
    if( ptr == NULL )
    {
        return;
    }
    
    o = __XSMemory_GetMemoryObject( ptr );
    
    o->retain_count--;
    
    if( o->retain_count == 0 )
    {
        if( o->typeID != 0 )
        {
            cls = XSRuntime_GetClassForTypeID( o->typeID );
            
            if( cls->dealloc != NULL )
            {
                cls->dealloc( ptr );
            }
        }
        
        free( o );
    }
}

void XSRetain( void * ptr )
{
    __XSMemoryObject * o;
    
    if( ptr == NULL )
    {
        return;
    }
    
    o = __XSMemory_GetMemoryObject( ptr );
    
    o->retain_count++;
}

void * XSRealloc( void * ptr, size_t size )
{
    __XSMemoryObject * o;
    void             * data;
    
    if( ptr == NULL )
    {
        return NULL;
    }
    
    o    = __XSMemory_GetMemoryObject( ptr );
    data = realloc( o->data, size );
    
    if( data == NULL )
    {
        return NULL;
    }
    
    o->data = data;
    o->size = size;
    
    return o->data;
}

void * XSAutoAlloc( size_t size )
{
    void * ptr;
    
    ptr = XSAlloc( size );
    
    XSAutorelease( ptr );
    
    return ptr;
}

void XSAutorelease( void * ptr )
{
    XSAutoreleasePool * ap;
    
    if( ptr == NULL )
    {
        return;
    }
    
    ap = __XSMemory_GetCurrentAutoreleasePool();
    
    if( ap->num_objects == ap->size )
    {
        ap->objects = ( void ** )realloc( ap->objects, sizeof( void * ) * ( ap->size + XS_MEMORY_NUM_OBJECTS ) );
        
        if( ap->objects == NULL )
        {
            fprintf( stderr, "Unable to allocate memory for the auto-release pool" );
            exit( EXIT_FAILURE );
        }
        
        ap->size += XS_MEMORY_NUM_OBJECTS;
    }
    
    ap->objects[ ap->num_objects++ ] = ptr;
}
