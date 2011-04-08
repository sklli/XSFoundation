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
 * @file        XSFile.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#include "XS.h"
#include "__XSFile.h"

/*!
 * @var         __XSSStdin
 * @abstract    XSFile structure representing stdin
 */
__XSFile __XSSStdin = { .stdin  = YES, .need_init = YES };

/*!
 * @var         __XSSStdout
 * @abstract    XSFile structure representing srdout
 */
__XSFile __XSSStdout = { .stdout = YES, .need_init = YES };

/*!
 * @var         __XSSStderr
 * @abstract    XSFile structure representing stderr
 */
__XSFile __XSSStderr = { .stderr = YES, .need_init = YES };

/*!
 * @var         XSStdin
 * @abstract    XSFile object representing stdin
 */
XSFile XSStdin = ( XSFile )&__XSSStdin;

/*!
 * @var         XSStdout
 * @abstract    XSFile object representing stdout
 */
XSFile XSSStdout = ( XSFile )&__XSSStderr;

/*!
 * @var         XSStderr
 * @abstract    XSFile object representing stderr
 */
XSFile XSSStderr = ( XSFile )&__XSSStderr;

/*!
 * @define      __XSFILE_INIT
 * @abstract    File initialization macro
 * @description This is needed for stdin, stdout and sterr, in order to
 *              initialize properly XSStdin, XSStdout and XSStderr.
 */
#define __XSFILE_INIT( f )          \
if( f->need_init == YES )           \
{                                   \
    if( f->stdin == YES )           \
    {                               \
        f->fp        = stdin;       \
        f->need_init = NO;          \
    }                               \
    else if( f->stdout == YES )     \
    {                               \
        f->fp        = stdout;      \
        f->need_init = NO;          \
    }                               \
    else if( f->stderr == YES )     \
    {                               \
        f->fp        = stderr;      \
        f->need_init = NO;          \
    }                               \
}

XSFile XSFile_Open( const char * filename, XSFileOpenMode openMode )
{
    FILE      * fp;
    __XSFile  * file;
    char        mode[ 4 ];
    BOOL        binary;
    
    memset( mode, 0, 4 );
    
    binary   = ( openMode & XSFileOpenModeBinary ) ? YES : NO;
    openMode = openMode & 0xFE;
    
    switch( ( int )openMode )
    {
        case XSFileOpenModeRead:
            
            strcat( mode, ( binary ) ? "rb" : "r" );
            break;
            
        case XSFileOpenModeWrite:
            
            strcat( mode, ( binary ) ? "wb" : "r" );
            break;
            
        case XSFileOpenModeAppend:
            
            strcat( mode, ( binary ) ? "ab" : "r" );
            break;
            
        case XSFileOpenModeApendAtEnd:
            
            strcat( mode, ( binary ) ? "ab+" : "a" );
            break;
            
        case XSFileOpenModeUpdate:
            
            strcat( mode, ( binary ) ? "rb+" : "r+" );
            break;
            
        case XSFileOpenModeUpdateDiscard:
            
            strcat( mode, ( binary ) ? "wb+" : "w+" );
            break;
    }
    
    if( binary )
    {
        strcat( mode, "b" );
    }
    
    if( NULL == ( fp = fopen( filename, mode ) ) )
    {
        return NULL;
    }
    
    if( NULL == ( file = __XSFile_Alloc() ) )
    {
        return NULL;
    }
    
    file->fp = fp;
    
    memset(  file->filename,      0, FILENAME_MAX );
    memset(  file->mode,          0, 4 );
    memset(  &( file->stat_buf ), 0, sizeof( struct stat ) );
    strcpy(  file->filename, filename );
    strncpy( file->mode, mode, 3 );
    __XSFile_UpdateStat( file );
    
    file->need_init  = NO;
    file->bit_buffer = 0;
    file->bit_count  = 0;
    file->bit_offset = 0;
    file->readable   = NO;
    file->writeable  = NO;
    
    if( strncmp( mode, "r", 1 ) == 0 )
    {
        file->readable  = YES;
        file->writeable = ( strlen( mode ) > 1 && strncmp( mode + 1, "+", 1 ) ) ? YES : NO;
    }
    else if( strncmp( mode, "w", 1 ) == 0 )
    {
        file->readable  = ( strlen( mode ) > 1 && strncmp( mode + 1, "+", 1 ) ) ? YES : NO;
        file->writeable = YES;
    }
    else if( strncmp( mode, "a", 1 ) == 0 )
    {
        file->readable  = ( strlen( mode ) > 1 && strncmp( mode + 1, "+", 1 ) ) ? YES : NO;
        file->writeable = YES;
    }
    
    return ( XSFile )file;
}

XSInteger XSFile_Flush( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    return fflush( _f->fp );
}

XSInteger XSFile_Close( XSFile file )
{
    XSInteger   res;
    __XSFile *  _f;
    
    _f = ( __XSFile * )file;
    
    __XSFile_WriteAlign( _f );
    
    res = fclose( _f->fp );
    
    XSRelease( _f );
    
    return res;
}

XSInteger XSFile_Printf( XSFile file, const char * format, ... )
{
    XSInteger   res;
    va_list     arg;
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    __XSFile_WriteAlign( _f );
    
    va_start( arg, format );
    
    res = vfprintf( _f->fp, format, arg );
    
    va_end( arg );
    
    return res;
}

XSInteger XSFile_VPrintf( XSFile file, const char * format, va_list arg )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    __XSFile_WriteAlign( _f );
    
    return vfprintf( _f->fp, format, arg );
}

XSInteger XSFile_Getc( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    return fgetc( _f->fp );
}

XSInteger XSFile_Putc( XSFile file, XSInteger c )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    __XSFile_WriteAlign( _f );
    
    return fputc( c, _f->fp );
}

XSInteger XSFile_Puts( XSFile file, const char * s )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    __XSFile_WriteAlign( _f );
    
    return fputs( s, _f->fp );
}

size_t XSFile_Read( XSFile file, void * ptr, size_t size, size_t nobj )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    return fread( ptr, size, nobj, _f->fp );
}

size_t XSFile_Write( XSFile file, const void * ptr, size_t size, size_t nobj )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    __XSFile_WriteAlign( _f );
    
    return fwrite( ptr, size, nobj, _f->fp );
}

XSInteger XSFile_Seek( XSFile file, XSInteger offset, XSFileSeekPosition origin )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    return fseek( _f->fp, offset, origin );
}

XSInteger XSFile_Tell( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    return ftell( _f->fp );
}

void XSFile_Rewind( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    rewind( _f->fp );
}

XSInteger XSFile_GetPos( XSFile file, fpos_t * ptr )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    return fgetpos( _f->fp, ptr );
}

XSInteger XSFile_SetPos( XSFile file, const fpos_t * ptr )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    return fsetpos( _f->fp, ptr );
}

void XSFile_ClearErr( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    clearerr( _f->fp );
}

XSInteger XSFile_EndOfFile( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    return feof( _f->fp );
}

XSInteger XSFile_Error( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    return ferror( _f->fp );
}

const char * XSFile_Filename( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    if( _f->stdin == YES )
    {
        return "stdin";
    }
    else if( _f->stdout == YES )
    {
        return "stdout";
    }
    else if( _f->stderr == YES )
    {
        return "stderr";
    }
    else
    {
        return _f->filename;
    }
}

const char * XSFile_OpenMode( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    if( _f->stdin == YES )
    {
        return "r";
    }
    else if( _f->stdout == YES )
    {
        return "a";
    }
    else if( _f->stderr == YES )
    {
        return "a";
    }
    else
    {
        return _f->mode;
    }
}

BOOL XSFile_IsReadable( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    if( _f->stdin == true )
    {
        return YES;
    }
    else if( _f->stdout == true )
    {
        return NO;
    }
    else if( _f->stderr == true )
    {
        return NO;
    }
    else
    {
        return _f->readable;
    }
}

BOOL XSFile_IsWriteable( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFILE_INIT( _f );
    
    if( _f->stdin == true )
    {
        return NO;
    }
    else if( _f->stdout == true )
    {
        return YES;
    }
    else if( _f->stderr == true )
    {
        return YES;
    }
    else
    {
        return _f->writeable;
    }
}

BOOL XSFile_Copy( XSFile file, char * new_name )
{
    FILE        * fp1;
    FILE        * fp2;
    size_t        length;
    unsigned char buffer[ 1024 ];
    const char  * name;
    
    name = XSFile_Filename( file );
    
    if( NULL == ( fp1 = fopen( name, "rb" ) ) )
    {
        return NO;
    }
    
    if( NULL == ( fp2 = fopen( name, "wb" ) ) )
    {
        fclose( fp1 );
        
        return NO;
    }
    
    while( ( length = fread( buffer, sizeof( unsigned char ), 1024, fp1 ) ) )
    {
        if( fwrite( buffer, sizeof( unsigned char ), length, fp2 ) != length )
        {
            fclose( fp1 );
            fclose( fp2 );
            remove( new_name );
            
            return NO;
        }
    }
    
    fclose( fp1 );
    fclose( fp2 );
    
    return YES;
}

XSInteger XSFile_GetBit( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    if( _f->readable == false )
    {
        return 0;
    }
    
    _f->bit_offset++;
    _f->bit_offset++;
    
    if( _f->bit_offset > 8 )
    {
        if( fread( &( _f->bit_buffer ), sizeof( char ), 1, _f->fp ) != 1 )
        {
            _f->bit_offset = 1;
            
            return -1;
        }
    }
    
    return ( _f->bit_buffer >> ( 8 - _f->bit_offset ) & 1 );
}

XSInteger XSFile_PutBit( XSFile file, uint8_t bit )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    if( _f->writeable == false )
    {
        return -1;
    }
    
    _f->bit_buffer |= ( _f->bit_buffer << 1 | ( bit & 1 ) );
    _f->bit_count  += 1;
    
    if( _f->bit_count == 8 )
    {
        __XSFile_WriteAlign( _f );
    }
    
    return 0;
}

XSInteger XSFile_GetBits( XSFile file, XSUInteger count )
{
    XSInteger    bits;
    XSUInteger   i;
    __XSFile   * _f;
    
    _f = ( __XSFile * )file;
    
    if( _f->readable == false )
    {
        return -1;
    }
    
    bits = 0;
    
    for( i = 0; i < count; i++ )
    {
        bits |= ( ( bits << 1 ) | XSFile_GetBit( file ) );
    }
    
    return bits;
}

XSInteger XSFile_PutBits( XSFile file, uint64_t bits, XSUInteger count )
{
    XSUInteger   i;
    XSUInteger   bytes;
    uint8_t      bit;
    __XSFile   * _f;
    
    _f = ( __XSFile * )file;
    
    if( _f->writeable == false )
    {
        return -1;
    }
    
    bytes  = ( XSUInteger )floor( count / 8 );
    count -= bytes * 8;
    
    if( bytes > 0 )
    {
        fwrite( &bits, sizeof( uint8_t ), bytes, _f->fp );
    }
    
    bits &= 0xFF;
    
    for( i = 0; i < count; i++ )
    {
        bit = bits >> ( ( count - 1 ) - i );
        
        XSFile_PutBit( file, bit );
    }
    
    return 0;
}

dev_t XSFile_DeviceID( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return _f->stat_buf.st_dev;
}

ino_t XSFile_SerialNumber( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return _f->stat_buf.st_ino;
}

nlink_t XSFile_NumberOfLinks( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return _f->stat_buf.st_nlink;
}

uid_t XSFile_UID( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return _f->stat_buf.st_uid;
}

gid_t XSFile_GID( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return _f->stat_buf.st_gid;
}

size_t XSFile_Size( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    __XSFile_UpdateStat( _f );
    
    return _f->stat_buf.st_size;
}

XSFloat XSFile_HumanReadableSize( XSFile file, char unit[] )
{
    size_t   bytes;
    XSFloat  size;
    __XSFile * _f;
    
    _f    = ( __XSFile * )file;
    bytes = XSFile_Size( file );
    
    memset( unit, 0, 3 );
    
    if( bytes < 1000000 )
    {
        size = ( XSFloat )bytes / ( XSFloat )1000;
        
        strcpy( unit, "KB" );
    }
    else if( bytes < 1000000000 )
    {
        size = ( ( XSFloat )bytes / ( XSFloat )1000 ) / ( XSFloat )1000;
        
        strcpy( unit, "MB" );
    }
    else
    {
        size = ( ( ( XSFloat )bytes / ( XSFloat )1000 ) / ( XSFloat )1000 ) / ( XSFloat )1000;
        
        strcpy( unit, "GB" );
    }
    
    return size;
}

time_t XSFile_AccessTime( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return _f->stat_buf.st_atime;
}

time_t XSFile_ModifictaionTime( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return _f->stat_buf.st_mtime;
}

time_t XSFile_CreationTime( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return _f->stat_buf.st_ctime;
}

BOOL XSFile_IsBlockDevice( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IFMT ) == S_IFBLK ) ) ? YES : NO;
}

BOOL XSFile_IsCharacterDevice( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IFMT ) == S_IFCHR ) ) ? YES : NO;
}

BOOL XSFile_IsFIFO( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IFMT ) == S_IFIFO ) ) ? YES : NO;
}

BOOL XSFile_IsRegularFile( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IFMT ) == S_IFREG ) ) ? YES : NO;
}

BOOL XSFile_IsDirectory( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IFMT ) == S_IFDIR ) ) ? YES : NO;
}

BOOL XSFile_IsLink( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IFMT ) == S_IFLNK ) ) ? YES : NO;
}

BOOL XSFile_IsSocket( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IFMT ) == S_IFSOCK ) ) ? YES : NO;
}

BOOL XSFile_IsUserReadable( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IRWXU ) == S_IRUSR ) ) ? YES : NO;
}

BOOL XSFile_IsUserWriteable( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IRWXU ) == S_IWUSR ) ) ? YES : NO;
}

BOOL XSFile_ISUserExecutable( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IRWXU ) == S_IXUSR ) ) ? YES : NO;
}

BOOL XSFile_IsGroupReadable( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IRWXG ) == S_IRGRP ) ) ? YES : NO;
}

BOOL XSFile_IsGroupWriteable( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IRWXG ) == S_IWGRP ) ) ? YES : NO;
}

BOOL XSFile_IsGroupExecutable( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IRWXG ) == S_IXGRP ) ) ? YES : NO;
}

BOOL XSFile_IsWorldReadable( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IRWXO ) == S_IROTH ) ) ? YES : NO;
}

BOOL XSFile_IsWorldWriteable( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IRWXO ) == S_IWOTH ) ) ? YES : NO;
}

BOOL XSFile_IsWorldExecutable( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( ( ( _f->stat_buf.st_mode & S_IRWXO ) == S_IXOTH ) ) ? YES : NO;
}

BOOL XSFile_HasSUID( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( _f->stat_buf.st_mode & S_ISUID ) ? YES : NO;
}

BOOL XSFile_HasSGID( XSFile file )
{
    __XSFile * _f;
    
    _f = ( __XSFile * )file;
    
    return ( _f->stat_buf.st_mode & S_ISGID ) ? YES : NO;
}
