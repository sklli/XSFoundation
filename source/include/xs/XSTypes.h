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
 * @header      
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    
 */

#ifndef _XS_TYPES_H_
#define _XS_TYPES_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XSConstants.h"
#include "../std/std.h"

/*******************************************************************************
 * Boolean data-type
 ******************************************************************************/

#ifndef OBJC_BOOL_DEFINED
    
    typedef signed char BOOL;
    #define YES ( BOOL )1
    #define NO  ( BOOL )0
    #define OBJC_BOOL_DEFINED
    
#endif

/*******************************************************************************
 * Standard typedefs
 ******************************************************************************/

typedef unsigned char           Boolean;
typedef unsigned char           UInt8;
typedef signed char             SInt8;
typedef unsigned short          UInt16;
typedef signed short            SInt16;
typedef unsigned int            UInt32;
typedef signed int              SInt32;
typedef uint64_t                UInt64;
typedef int64_t                 SInt64;
typedef float                   Float32;
typedef double                  Float64;
typedef UInt8                   Byte;
typedef SInt8                   SignedByte;
typedef unsigned short          UniChar;
typedef unsigned long           UniCharCount;
typedef unsigned char         * StringPtr;
typedef const unsigned char   * ConstStringPtr;
typedef unsigned char           Str255[ 256 ];
typedef const unsigned char   * ConstStr255Param;
typedef SInt16                  RegionCode;
typedef SInt16                  LangCode;
typedef SInt16                  ScriptCode;
typedef UInt32                  FourCharCode;
typedef FourCharCode            OSType;
typedef SInt32                  OSStatus;
typedef SInt16                  OSErr;
typedef UInt8                   UTF8Char;
typedef UInt16                  UTF16Char;
typedef UInt32                  UTF32Char;

#if __LP64__
    
    typedef long          XSInteger;
    typedef unsigned long XSUInteger;
    typedef double        XSFloat;
    
#else
    
    typedef int          XSInteger;
    typedef unsigned int XSUInteger;
    typedef float        XSFloat;
    
#endif

/*!
 * @typedef     XSPoint
 * @abstract    Point data-type
 * @field       x   The X coordinate of the point
 * @field       y   The Y coordinate of the point
 */
typedef struct _XSPoint
{
    XSFloat x;
    XSFloat y;
}
XSPoint;

/*!
 * @typedef     XSSize
 * @abstract    Size data-type
 * @field       width   The width of the size
 * @field       height  The height of the size
 */
typedef struct _XSSize
{
    XSFloat width;
    XSFloat height;
}
XSSize;

/*!
 * @typedef     XSRect
 * @abstract    Rectangle data-type
 * @field       origin  The origin point of the rectangle
 * @field       size    The size of the rectangle
 */
typedef struct _XSRect
{
    XSPoint origin;
    XSSize  size;
}
XSRect;

/*!
 * @typedef     XSRange 
 * @abstract    Range data-type
 * @field       location    The start of the range
 * @field       length      The length of the range
 */
typedef struct _XSRange
{
    XSUInteger location;
    XSUInteger length;
}
XSRange;

/*!
 * @define      XSUIntegerMax
 * @abstract    Not found value for the XSRange.location field
 */
#define XSNotFound XSUIntegerMax

/*!
 * @typedef     XSEdgeInset 
 * @abstract    Inset distances
 * @field       left    The left coordinate
 * @field       top     The top coordiante
 * @field       right   The right coordinate
 * @field       bottom  The bottom coordinate
 */
typedef struct _XSEdgeInsets
{
    XSFloat left;
    XSFloat top;
    XSFloat right;
    XSFloat bottom;
}
XSEdgeInsets;

/*!
 * @typedef     XSByteOrder
 * @abstract    Byte-order data-type
 * @field       XS_UnknownByteOrder     Unknown byte order
 * @field       XS_LittleEndian         Little endian byte order
 * @field       XS_BigEndian            Big endian byte order
 */
typedef enum _XSByteOrder
{
   XS_UnknownByteOrder = 0,
   XS_LittleEndian     = 1,
   XS_BigEndian        = 2
}
XSByteOdrer;

/*!
 * @enum
 * @abstract    Enumeration for the XSComparisonResult data-type
 * @field       XSOrderedAscending      Order is ascending
 * @field       XSOrderedSame           Order is same
 * @field       XSOrderedDescending     Order is descending
 */
enum
{
   XSOrderedAscending  = -1,
   XSOrderedSame       = 0,
   XSOrderedDescending = 1
};

/*!
 * @typedef     XSComparisonResult
 * @abstract    Comaprison result data-type
 */
typedef XSInteger XSComparisonResult;

/*!
 * @typedef     XSDecimal
 * @abstract    Decimal number representation
 * @field       exponent        The exponent of the decimal number
 * @field       length          The length of the decimal number
 * @field       isNegative      Whether the decimal number is negative
 * @field       isCompact       Whether the decimal numer is compact
 * @field       reserved        Reserved bits
 * @field       mantissa        The manstissa for the decimal number
 */
typedef struct _XSDecimal
{
    signed int     exponent   : 8;
    unsigned int   length     : 4;
    unsigned int   isNegative : 1;
    unsigned int   isCompact  : 1;
    unsigned int   reserved   : 18;
    unsigned short mantissa[ XSDecimalMaxSize ];
}
XSDecimal;

/* XSString is required here as the objects description callbacks use that type */
#include "XSString.h"

/*!
 * @typedef     XSTypeID
 * @abstract    Type ID foe the registered runtime classes
 */
typedef unsigned long XSTypeID;

/*!
 * @typedef     XSTypeRef
 * @abstract    Baisc type for the objects (used mainly in XSRuntime_CreateInstance) 
 */
typedef const void  * XSTypeRef;

/*!
 * @typedef     XSRuntimeClass
 * @abstract    XSFoundation runtime class
 * @field       classname   The name of the class
 * @field       init        The class constructor
 * @field       dealloc     The class destructor
 * @field       copy        The object's copy callback
 * @field       description The object's description callback (used in XSLog)
 */
typedef struct _XSRuntimeClass
{
    const char * className;
    void         ( * init        )( void * object );
    void         ( * dealloc     )( void * object );
    void         ( * copy        )( void * source, void * destination );
    XSStringRef  ( * description )( void * object );
}
XSRuntimeClass;

/*!
 * @typedef     XSRuntimeBase
 * @abstract    Base for the runtime classes
 * @description This sructure MUST be the first member of all XSFoundation
 *              classes.
 * @field       isa     A pointer to the class structure for the object
 */
typedef struct _XSRuntimeBase
{
    XSRuntimeClass * isa;
}
XSRuntimeBase;

/*!
 * @typedef     id
 * @abstract    Polymorphism support - Generic type for all XSFoundation objects
 */
typedef XSRuntimeBase * id;

/*!
 * @typedef     Class
 * @abstract    Polymorphism support - Generic type for all XSFoundation classes
 */
typedef XSRuntimeClass * Class;

/*!
 * @define      nil
 * @abstract    NULL pointer for the 'id' type
 */
#define nil	( id )0

/*!
 * @define      Nil
 * @abstract    NULL pointer for the 'Class' type
 */
#define Nil	( Class )0

XS_EXTERN_C_END

#endif /* _XS_TYPES_H_ */
