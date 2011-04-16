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
 * @file        __XSFunctions.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Implementation of private functions
 */

#include "XS.h"
#include "__XSFunctions.h"

/* Weak symbols for the program name and program invocation short name */
extern char * __progname                    WEAK_ATTRIBUTE;
extern char * program_invocation_short_name WEAK_ATTRIBUTE;

/*!
 * @var         __progname
 * @abstract    Program name
 */
char * __progname = NULL;

/*!
 * @var         program_invocation_short_name
 * @abstract    Program invocation short name
 */
char * program_invocation_short_name = NULL;

/*!
 * @var         __log_mutex
 * @abstract    Mutex for the log calls
 */
static pthread_mutex_t __log_mutex  = PTHREAD_MUTEX_INITIALIZER;

/*!
 * @var         __log_paused
 * @abstract    Whether the log system is paused or not
 */
static BOOL __log_paused = NO;

void __XSVLog( const char * fmt, va_list args )
{
    pid_t            pid;
    pthread_t        tid;
    time_t           t;
    char             date[ 255 ];
    char           * exec;
    char           * format;
    char           * format_ptr;
    size_t           length;
    unsigned int     i;
    void           * va_ptr;
    XSRuntimeClass * b;
    XSClassInfos   * cls;
    XSString         description;
    
    #ifdef _WIN32
    struct tm        now;
    #else
    struct tm      * now;
    struct timeval   tv;
    #endif
    
    #ifdef __MACH__
    mach_port_t      mid;
    #endif
    
    while( pthread_mutex_trylock( &__log_mutex ) != 0 )
    {}
    
    pid = getpid();
    tid = pthread_self();

    #ifdef _WIN32
    
    time( &t );
    localtime_s( &now, &t );
    
    #else

    t   = time( NULL );
    now = localtime( &t );
    gettimeofday( &tv, NULL );
    memset( ( void * )date, 0, 255 );
    strftime( ( char * )date, 255, "%Y-%m-%d %H:%M:%S", now );

    #endif
    
    #ifdef __MACH__
    mid = pthread_mach_thread_np( tid );
    #endif
    
    if( __progname != NULL )
    {
        exec = __progname;
    }
    else if( program_invocation_short_name != NULL )
    {
        exec = program_invocation_short_name;
    }
    else
    {
        exec = ( char * )"unknown";
    }
    
    #if defined( _WIN32 )
    printf( "%s %s[%i:%lu] ", date, exec, pid, ( unsigned long )tid );
    #elif defined( __MACH__ )
    printf( "%s.%06lu %s[%i:%X] ", date, ( unsigned long )tv.tv_usec, exec, pid, mid );
    #else
    printf( "%s.%06lu %s[%i:%lu] ", date, ( unsigned long )tv.tv_usec, exec, pid, ( unsigned long )tid );
    #endif
    
    length = strlen( fmt );
    
    if( NULL == ( format_ptr = ( char * )calloc( sizeof( char ), length + 1 ) ) )
    {
        putc( '\n', stdout );
        return;
    }
    
    format = format_ptr;
    
    strcpy( format, fmt );
    
    i = 0;
    
    while( 1 )
    {
        if( format[ i ] == '\0' )
        {
            break;
        }
        if( i > 0 && format[ i ] == '@' && format[ i - 1 ] == '$' )
        {
            format[ i - 1 ] = 0;
            
            vprintf( format, args );
            
            va_ptr = va_arg( args, void * );
            
            if( va_ptr == NULL )
            {
                printf( "<XSObject: nil>" );
            }
            else
            {
                b      = ( XSRuntimeClass * )va_ptr;
                cls    = b->classInfos;
                
                printf( "<%s: %p>", cls->className, va_ptr );
                
                if( cls->toString != NULL )
                {
                    description = cls->toString( va_ptr );
                    printf( " [ %s ]", XSString_CString( description ) );
                }
            }
            
            format += i + 1;
            i       = 0;
        }
        else
        {
            i++;
        }
    }
    
    if( i > 0 )
    {
        vprintf( format, args );
    }
    
    free( ( void * )format_ptr );
    putc( '\n', stdout );
    
    pthread_mutex_unlock( &__log_mutex );
}

void __XSLog_Pause( void )
{
    while( pthread_mutex_trylock( &__log_mutex ) != 0 )
    {}
    
    __log_paused = YES;
}

void __XSLog_Resume( void )
{
    if( __log_paused == YES )
    {
        pthread_mutex_unlock( &__log_mutex );
    }
}
