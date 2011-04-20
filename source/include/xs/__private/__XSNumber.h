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
 * @header      __XSNumber.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Private XSNumber class definitions
 */

#ifndef ___XS_NUMBER_H_
#define ___XS_NUMBER_H_
#pragma once

#include "../XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XS.h"

#define __XSNUMBER_TYPE_BOOL        0x0001
#define __XSNUMBER_TYPE_SCHAR       0x0002
#define __XSNUMBER_TYPE_UCHAR       0x0004
#define __XSNUMBER_TYPE_SSHORT      0x0008
#define __XSNUMBER_TYPE_USHORT      0x0010
#define __XSNUMBER_TYPE_SINT        0x0020
#define __XSNUMBER_TYPE_UINT        0x0040
#define __XSNUMBER_TYPE_SLONG       0x0080
#define __XSNUMBER_TYPE_ULONG       0x0100
#define __XSNUMBER_TYPE_SLONGLONG   0x0200
#define __XSNUMBER_TYPE_ULONGLONG   0x0400
#define __XSNUMBER_TYPE_FLOAT       0x0800
#define __XSNUMBER_TYPE_DOUBLE      0x1000
#define __XSNUMBER_TYPE_SINTEGER    0x2000
#define __XSNUMBER_TYPE_UINTEGER    0x4000
#define __XSNUMBER_TYPE_ALL         0x7FFF

/*!
 * @typdef      __XSNumber
 * @abastract   XSNumber class
 * @field       __class     Runtime class
 */
typedef struct __XSNumber_Struct
{
    XSRuntimeClass      __class;
    uint16_t            types;
    BOOL                boolValue;
    signed char         sCharValue;
    unsigned char       uCharValue;
    signed short        sShortValue;
    unsigned short      uShortValue;
    signed int          sIntValue;
    unsigned int        uIntValue;
    signed long         sLongValue;
    unsigned long       uLongValue;
    signed long long    sLongLongValue;
    unsigned long long  uLongLongValue;
    float               floatValue;
    double              doubleValue;
    XSInteger           sIntegerValue;
    XSUInteger          uIntegerValue;
    
}
__XSNumber;

/*!
 * @function    __XSNumber_Initialize
 * @abstract    Runtime initialization
 * @result      void
 */
void __XSNumber_Initialize( void );

/*!
 * @function    __XSNumber_ToString
 * @abstract    Object description
 * @param       object  A pointer to the object
 * @result      The object's description
 */
XSString __XSNumber_ToString( XSObject object );

/*!
 * @function    __XSNumber_Equals
 * @abstract    Object comparison
 * @param       object1 The first object to compare
 * @param       object1 The second object to compare
 * @result      YES if both objects are equals, otherwise NO
 */
BOOL __XSNumber_Equals( XSObject object1, XSObject object2 );

uint64_t __XSNumber_GetUInt64Value( __XSNumber * n );

XS_EXTERN_C_END

#endif /* ___XS_NUMBER_H_ */
