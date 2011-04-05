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
 * @header      XSFile.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#ifndef _XS_FILE_H_
#define _XS_FILE_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XS.h"

/*!
 * @typedef     XSFileRef
 * @abstract    Opaque type for the XSFile objects
 */
typedef struct XSFile * XSFileRef;

/*!
 * @typedef     XSFileOpenMode
 * @abstract    Open modes for XSFileRef
 * @description A specific mode can be ORed with XSFileOpenModeText
 *              XSFileOpenModeBinary to specify if working with text or binary
 *              files
 * @field       XSFileOpenModeText          Text mode
 * @field       XSFileOpenModeBinary        Binary mode
 * @field       XSFileOpenModeRead          "r" - Text reading
 * @field       XSFileOpenModeWrite         "w" - Text writing
 * @field       XSFileOpenModeAppend        "a" - Text append
 * @field       XSFileOpenModeApendAtEnd    "a+" - Text append, reading, and writing at end
 * @field       XSFileOpenModeUpdate        "r+" - Text update (reading and writing)
 * @field       XSFileOpenModeUpdateDiscard "w+" - Text update discarding previous content (if any)
 */
typedef enum
{
    XSFileOpenModeText          = 0x00,
    XSFileOpenModeBinary        = 0x01,
    XSFileOpenModeRead          = 0x02,
    XSFileOpenModeWrite         = 0x04,
    XSFileOpenModeAppend        = 0x06,
    XSFileOpenModeApendAtEnd    = 0x08,
    XSFileOpenModeUpdate        = 0x0A,
    XSFileOpenModeUpdateDiscard = 0x0E
}
XSFileOpenMode;

/*!
 * @typedef     XSFileSeekPosition
 * @abstract    Origin position for the file seek operations
 * @field       XSFileSeekPositionCurent    Current position
 * @field       XSFileSeekPositionStart     Start of the file
 * @field       XSFileSeekPositionEnd       End of the file
 * @field       XSFileOpenModeReadSet       Specific position
 */
typedef enum
{
    XSFileSeekPositionCurent = SEEK_CUR,
    XSFileSeekPositionStart  = 0,
    XSFileSeekPositionEnd    = SEEK_END,
    XSFileOpenModeReadSet    = SEEK_SET
}
XSFileSeekPosition;

/*!
 * @var         XSStdin
 * @abstract    XSFileRef object representing stdin
 */
extern XSFileRef XSStdin;

/*!
 * @var         XSStdout
 * @abstract    XSFileRef object representing stdout
 */
extern XSFileRef XSStdout;

/*!
 * @var         XSStderr
 * @abstract    XSFileRef object representing stderr
 */
extern XSFileRef XSStderr;

/*!
 * @abstract    Creates an XSFileRef instance and opens the represented file.
 * @description This function may return NULL if the represented file has not
 *              been opened.
 * @param       filename    The name of the file
 * @param       openMode    The file open mode (see XSFileOpenMode)
 * @result      The instance of XSFileRef
 */
XSFileRef XSFile_Open( const char * filename, XSFileOpenMode openMode );

/*!
 * @function    
 * @abstract    Flushes the file stream stream
 * @param       file    The file object
 * @result      Zero on success or EOF on error
 */
XSInteger XSFile_Flush( XSFileRef file );

/*!
 * @function    XSFile_Close
 * @abstract    Closes the file stream (after flushing, if output stream)
 * @discussion  You're still responsible to release the file object after
 *              calling this function.
 * @param       file    The file object
 * @result      EOF on error, zero otherwise.
 */
XSInteger XSFile_Close( XSFileRef file );

/*!
 * @function    XSFile_Printf
 * @abstract    Converts (according to format format) and writes output to the file
 * @param       file    The file object
 * @result      The number of characters written, or negative value on error
 */
XSInteger XSFile_Printf( XSFileRef file, const char * format, ... );

/*!
 * @function    XSFile_VPrintf
 * @abstract    Equivalent to fprintf with variable argument list replaced by arg.
 * @param       file    The file object
 * @param       arg     The variable arguments list
 * @result      The number of characters written, or negative value on error
 */
XSInteger XSFile_VPrintf( XSFileRef file, const char * format, va_list arg );

/*!
 * @function    XSFile_Getc
 * @abstract    Returns the next character from the file.
 * @param       file    The file object
 * @result      The character or EOF on error
 */
XSInteger XSFile_Getc( XSFileRef file );

/*!
 * @function    XSFile_Putc
 * @abstract    Writes a character to the file
 * @param       file    The file object
 * @param       c       The character to write
 * @result      The character or EOF on error
 */
XSInteger XSFile_Putc( XSFileRef file, XSInteger c );

/*!
 * @function    XSFile_Puts
 * @abstract    Writes a C string to the file
 * @param       file    The file object
 * @result      Non-negative on success or EOF on error.
 */
XSInteger XSFile_Puts( XSFileRef file, const char * s );

/*!
 * @function    XSFile_Read
 * @abstract    Reads from the file
 * @param       file    The file object
 * @param       ptr     A pointer to the memory location in which the data will be placed.
 * @param       file    The size of the objects to read
 * @param       file    The number of objects to read
 * @result      The number of objects read
 */
size_t XSFile_Read( XSFileRef file, void * ptr, size_t size, size_t nobj );

/*!
 * @function    XSFile_Write
 * @abstract    Writes to the file
 * @param       file    The file object
 * @param       ptr     The data to write
 * @param       file    The size of the objects to write
 * @param       file    The number of objects to write
 * @result      The number of objects written
 */
size_t XSFile_Write( XSFileRef file, const void * ptr, size_t size, size_t nobj );

/*!
 * @function    XSFile_Seek
 * @abstract    Sets file position for the file and clears end-of-file indicator
 * @description For a binary stream, file position is set to offset bytes from
 *              the position indicated by origin: beginning of file for
 *              SEEK_SET, current position for SEEK_CUR, or end of file for
 *              SEEK_END. Behaviour is similar for a text stream, but offset
 *              must be zero or, for SEEK_SET only, a value returned by ftell.
 * @param       file    The file object
 * @param       origin  The seek origin (see XSFileSeekPosition)
 * @result      Non-zero on error.
 */
XSInteger XSFile_Seek( XSFileRef file, XSInteger offset, XSFileSeekPosition origin );

/*!
 * @function    XSFile_Tell
 * @abstract    Gets the current file position
 * @param       file    The file object
 * @result      The position or -1 on error
 */
XSInteger XSFile_Tell( XSFileRef file );

/*!
 * @function    XSFile_Rewind
 * @abstract    Rewinds to the beginning of the file and clears the error indicators
 * return       void
 */
void XSFile_Rewind( XSFileRef file );

/*!
 * @function    XSFile_GetPos
 * @abstract    Stores the current file position
 * @param       file    The file object
 * @param       ptr     A pointer where tos store the file position
 * @result      Non-zero on error
 */
XSInteger XSFile_GetPos( XSFileRef file, fpos_t * ptr );

/*!
 * @function    XSFile_SetPos
 * @abstract    Sets the current file position
 * @param       file    The file object
 * @param       ptr     The file position
 * @result      Non-zero on error
 */
XSInteger XSFile_SetPos( XSFileRef file, const fpos_t * ptr );

/*!
 * @function    XSFile_ClearErr
 * @abstract    Clears end-of-file and error indicators
 * @param       file    The file object
 * @result      void
 */
void XSFile_ClearErr( XSFileRef file );

/*!
 * @function    XSFile_EndOfFile
 * @abstract    Checks for the end of the file
 * @param       file    The file object
 * @result      Non-zero if end-of-file indicator is set
 */
XSInteger XSFile_EndOfFile( XSFileRef file );

/*!
 * @function    XSFile_Error
 * @abstract    Checks for the error indicator
 * @param       file    The file object
 * @result      Non-zero if error indicator is set
 */
XSInteger XSFile_Error( XSFileRef file );

/*!
 * @function    XSFile_Filename
 * @abstract    Gets the filename
 * @param       file    The file object
 * @result      The name of the file
 */
const char * XSFile_Filename( XSFileRef file );

/*!
 * @function    XSFile_OpenMode
 * @abstract    Gets the file's open mode
 * @param       file    The file object
 * @result      The file's open mode
 */
const char * XSFile_OpenMode( XSFileRef file );

/*!
 * @function    XSFile_IsReadable
 * @abstract    Checks if the file is readable 
 * @param       file    The file object
 * @result      true if the file is readable, otherwise false
 */
BOOL XSFile_IsReadable( XSFileRef file );

/*!
 * @function    XSFile_IsWriteable
 * @abstract    Checks if the file is writeable 
 * @param       file    The file object
 * @result      true if the file is writeable, otherwise false
 */
BOOL XSFile_IsWriteable( XSFileRef file );

/*!
 * @function    XSFile_Copy
 * @abstract    Copies the file to another destination
 * @param       file    The file object
 * @result      True if the file was copeid, otherwise false
 */
BOOL XSFile_Copy( XSFileRef file, char * new_name );

/*!
 * @function    XSFile_GetBit
 * @abstract    Gets the next bit in the file
 * @param       file    The file object
 * @result      
 */
XSInteger XSFile_GetBit( XSFileRef file );

/*!
 * @function    XSFile_PutBit
 * @abstract    Writes a bit in the file
 * @param       file    The file object
 * @result      
 */
XSInteger XSFile_PutBit( XSFileRef file, uint8_t bit );

/*!
 * @function    XSFile_GetBits
 * @abstract    Gets bits from the file
 * @param       file    The file object
 * @result      
 */
XSInteger XSFile_GetBits( XSFileRef file, XSUInteger count );

/*!
 * @function    XSFile_PutBits
 * @abstract    Write bits to the file
 * @param       file    The file object
 * @result      
 */
XSInteger XSFile_PutBits( XSFileRef file, uint64_t bits, XSUInteger count );

/*!
 * @function    XSFile_DeviceID
 * @abstract    
 * @param       file    The file object
 * @result      
 */
dev_t XSFile_DeviceID( XSFileRef file );

/*!
 * @function    XSFile_SerialNumber
 * @abstract    
 * @param       file    The file object
 * @result      
 */
ino_t XSFile_SerialNumber( XSFileRef file );

/*!
 * @function    XSFile_NumberOfLinks
 * @abstract    
 * @param       file    The file object
 * @result      
 */
nlink_t XSFile_NumberOfLinks( XSFileRef file );

/*!
 * @function    XSFile_UID
 * @abstract    
 * @param       file    The file object
 * @result      
 */
uid_t XSFile_UID( XSFileRef file );

/*!
 * @function    XSFile_GID
 * @abstract    
 * @param       file    The file object
 * @result      
 */
gid_t XSFile_GID( XSFileRef file );

/*!
 * @function    XSFile_Size
 * @abstract    
 * @param       file    The file object
 * @result      
 */
size_t XSFile_Size( XSFileRef file );

/*!
 * @function    XSFile_HumanReadableSize
 * @abstract    
 * @param       file    The file object
 * @result      
 */
XSFloat XSFile_HumanReadableSize( XSFileRef file, char unit[] );

/*!
 * @function    XSFile_AccessTime
 * @abstract    
 * @param       file    The file object
 * @result      
 */
time_t XSFile_AccessTime( XSFileRef file );

/*!
 * @function    XSFile_ModifictaionTime
 * @abstract    
 * @param       file    The file object
 * @result      
 */
time_t XSFile_ModifictaionTime( XSFileRef file );

/*!
 * @function    XSFile_CreationTime
 * @abstract    
 * @param       file    The file object
 * @result      
 */
time_t XSFile_CreationTime( XSFileRef file );

/*!
 * @function    XSFile_IsBlockDevice
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsBlockDevice( XSFileRef file );

/*!
 * @function    XSFile_IsCharacterDevice
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsCharacterDevice( XSFileRef file );

/*!
 * @function    XSFile_IsFIFO
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsFIFO( XSFileRef file );

/*!
 * @function    XSFile_IsRegularFile
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsRegularFile( XSFileRef file );

/*!
 * @function    XSFile_IsDirectory
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsDirectory( XSFileRef file );

/*!
 * @function    XSFile_IsLink
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsLink( XSFileRef file );

/*!
 * @function    XSFile_IsSocket
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsSocket( XSFileRef file );

/*!
 * @function    XSFile_IsUserReadable
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsUserReadable( XSFileRef file );

/*!
 * @function    XSFile_IsUserWriteable
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsUserWriteable( XSFileRef file );

/*!
 * @function    XSFile_ISUserExecutable
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_ISUserExecutable( XSFileRef file );

/*!
 * @function    XSFile_IsGroupReadable
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsGroupReadable( XSFileRef file );

/*!
 * @function    XSFile_IsGroupWriteable
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsGroupWriteable( XSFileRef file );

/*!
 * @function    XSFile_IsGroupExecutable
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsGroupExecutable( XSFileRef file );

/*!
 * @function    XSFile_IsWorldReadable
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsWorldReadable( XSFileRef file );

/*!
 * @function    XSFile_IsWorldWriteable
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsWorldWriteable( XSFileRef file );

/*!
 * @function    XSFile_IsWorldExecutable
 * @abstract    
 * @param       file    The file object
 * @result      
 */
BOOL XSFile_IsWorldExecutable( XSFileRef file );

/*!
 * @function    XSFile_HasSUID
 * @abstract    Checks if the file has the SUID bit set
 * @param       file    The file object
 * @result      True if the SUID bit is set, otherwise false
 */
BOOL XSFile_HasSUID( XSFileRef file );

/*!
 * @function    XSFile_HasSGID
 * @abstract    Checks if the file has the SGID bit set
 * @param       file    The file object
 * @result      True if the SGID bit is set, otherwise false
 */
BOOL XSFile_HasSGID( XSFileRef file );

XS_EXTERN_C_END

#endif /* _XS_FILE_H_ */
