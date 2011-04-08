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
 * @header      XSApplication.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#include "XS.h"
#include "__XSApplication.h"

static __XSApplication    * __xsapp = NULL;
static XSAutoreleasePool    __xsarp = NULL;
static BOOL __xsapp_argv_processed  = NO;

XSApplication XSApplication_Start( int argc, const char ** argv )
{
    XSRuntime_Initialize();
    
    __xsapp = __XSApplication_Alloc();
    __xsarp = XSAutoreleasePool_Create();
    
    __xsapp->argc       = argc - 1;
    __xsapp->argv       = argv + 1;
    __xsapp->executable = argv[ 0 ];
    
    return ( XSApplication )__xsapp;
}

void XSApplication_Exit( void )
{
    XSRelease( __xsarp );
    XSRelease( __xsapp );
    
    __xsarp = NULL;
    __xsapp = NULL;
    
    pthread_exit( NULL );
}

XSApplication XSApplication_SharedApplication( void )
{
    return ( XSApplication )__xsapp;
}

void XSApplication_PrintHelp( XSApplication app, const char * description )
{
    const char          * exec;
    const char          * help;
    __XSApplication     * _app;
    XSApplicationArgument arg;
    XSUInteger            i;
    
    _app = ( __XSApplication * )app;
    
    if( NULL == ( exec = strrchr( _app->executable, '/' ) ) )
    {
        exec = _app->executable;
    }
    else
    {
        exec++;
    }
    
    printf( "--------------------------------------------------------------------------------\n" );
    printf( "%s - %s\n", exec, description );
    printf( "--------------------------------------------------------------------------------\n" );
    
    if( _app->arg_count > 0 )
    {
        printf( "\nArguments:\n\n" );
        
        for( i = 0; i < _app->arg_count; i++ )
        {
            arg = _app->args[ i ];
            
            printf( "    %s ", XSApplicationArgument_GetName( arg ) );
            
            switch( XSApplicationArgument_GetType( arg ) )
            {
                case XSApplicationArgumentTypeFlag:
                    
                    printf( "\n" );
                    break;
                    
                case XSApplicationArgumentTypeInteger:
                    
                    printf( "[ integer ]\n" );
                    break;
                    
                case XSApplicationArgumentTypeUnsignedInteger:
                    
                    printf( "[ positive integer ]\n" );
                    break;
                    
                case XSApplicationArgumentTypeString:
                    
                    printf( "[ string ]\n" );
                    break;
                    
                case XSApplicationArgumentTypeFloat:
                    
                    printf( "[ float ]\n" );
                    break;
                    
                default:
                    
                    printf( "[ value ]\n" );
                    break;
            }
            
            if( NULL == ( help = XSApplicationArgument_GetHelp( arg ) ) )
            {
                printf( "    No description available\n\n" );
            }
            else
            {
                printf( "    %s\n\n", help );
            }
        }
    
        printf( "--------------------------------------------------------------------------------\n" );
    }
    
    ( void )app;
    ( void )description;
}

void XSApplication_RegisterArgument( XSApplication app, const char * name, XSApplicationArgumentType type, ... )
{
    va_list               args;
    __XSApplication     * _app;
    XSApplicationArgument arg;
    const char          * help;
    
    va_start( args, type );
    
    help = va_arg( args, const char * );
    
    va_end( args );
    
    _app = ( __XSApplication * )app;
    
    if( help )
    {
        arg = XSApplicationArgument_Create( name, type, help );
    }
    else
    {
        arg = XSApplicationArgument_Create( name, type );
    }
    
    if( _app->arg_count == _app->arg_alloc )
    {
        XSRealloc( _app->args, _app->arg_count + 25 );
        
        _app->arg_alloc += 25;
    }
    
    _app->args[ _app->arg_count++ ] = arg;
}

XSApplicationArgument XSApplication_GetArgument( XSApplication app, const char * name )
{
    XSUInteger        i;
    __XSApplication * _app;
    
    _app = ( __XSApplication * )app;
    
    for( i = 0; i < _app->arg_count; i++ )
    {
        if( strcmp( name, XSApplicationArgument_GetName( _app->args[ i ] ) ) == 0 )
        {
            return _app->args[ i ];
        }
    }
    
    return NULL;
}

BOOL XSApplication_HasArgument( XSApplication app, const char * name )
{
    if( __xsapp_argv_processed == NO )
    {
        __XSApplication_ProcessArguments( ( __XSApplication * )app );
        
        __xsapp_argv_processed = YES;
    }
    
    return XSApplication_GetArgument( app, name ) != NULL;
}

BOOL XSApplication_GetFlag( XSApplication app, const char * name )
{
    XSApplicationArgument arg;
    
    if( __xsapp_argv_processed == NO )
    {
        __XSApplication_ProcessArguments( ( __XSApplication * )app );
        
        __xsapp_argv_processed = YES;
    }
    
    arg  = XSApplication_GetArgument( app, name );
    
    if( arg == NULL )
    {
        return NO;
    }
    
    return XSApplicationArgument_GetFlag( arg );
}

XSInteger XSApplication_GetInteger( XSApplication app, const char * name )
{
    XSApplicationArgument arg;
    
    if( __xsapp_argv_processed == NO )
    {
        __XSApplication_ProcessArguments( ( __XSApplication * )app );
        
        __xsapp_argv_processed = YES;
    }
        
    arg  = XSApplication_GetArgument( app, name );
    
    if( arg == NULL )
    {
        return 0;
    }
    
    return XSApplicationArgument_GetIntegerValue( arg );
}

XSUInteger XSApplication_GetUnsignedInteger( XSApplication app, const char * name )
{
    XSApplicationArgument arg;
    
    if( __xsapp_argv_processed == NO )
    {
        __XSApplication_ProcessArguments( ( __XSApplication * )app );
        
        __xsapp_argv_processed = YES;
    }
    
    arg  = XSApplication_GetArgument( app, name );
    
    if( arg == NULL )
    {
        return 0;
    }
    
    return XSApplicationArgument_GetUnsignedIntegerValue( arg );
}

XSString XSApplication_GetString( XSApplication app, const char * name )
{
    XSApplicationArgument arg;
    
    if( __xsapp_argv_processed == NO )
    {
        __XSApplication_ProcessArguments( ( __XSApplication * )app );
        
        __xsapp_argv_processed = YES;
    }
    
    arg  = XSApplication_GetArgument( app, name );
    
    if( arg == NULL || XSApplicationArgument_GetStringValue( arg ) == NULL )
    {
        return NULL;
    }
    
    return XSAutorelease( XSSTR( ( char * )XSApplicationArgument_GetStringValue( arg ) ) );
}

XSFloat XSApplication_GetFloat( XSApplication app, const char * name )
{
    XSApplicationArgument arg;
    
    if( __xsapp_argv_processed == NO )
    {
        __XSApplication_ProcessArguments( ( __XSApplication * )app );
        
        __xsapp_argv_processed = YES;
    }
        
    arg  = XSApplication_GetArgument( app, name );
    
    if( arg == NULL )
    {
        return 0;
    }
    
    return XSApplicationArgument_GetFloatValue( arg );
}

XSArray XSApplication_GetUnnamedArguments( XSApplication app )
{
    XSApplication * _app;
    
    _app = ( XSApplication * )app;
    
    return NULL;
}