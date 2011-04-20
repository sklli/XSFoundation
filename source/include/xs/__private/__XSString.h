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
 * @header      __XSString.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Private XSString class definitions
 */

#ifndef ___XS_STRING_H_
#define ___XS_STRING_H_
#pragma once

#include "../XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XS.h"

/*!
 * @typdef      __XSString
 * @abastract   XSString class
 * @field       __class     Runtime class
 * @field       str         A pointer to the C string
 */
typedef struct __XSString_Struct
{
    XSRuntimeClass __class;
    XSUInteger     length;
    XSUInteger     capacity;
    XSUInteger     initialCapacity;
    char         * str;
}
__XSString;

/*!
 * @function    __XSString_Initialize
 * @abstract    Runtime initialization
 * @result      void
 */
void __XSString_Initialize( void );

/*!
 * @function    __XSString_Destruct
 * @abstract    Destructor
 * @param       object  A pointer to the object
 * @result      void
 */
void __XSString_Destruct( XSObject object );

/*!
 * @function    __XSString_Copy
 * @abstract    Object copy
 * @param       object  A pointer to the object
 * @result      void
 */
void __XSString_Copy( XSObject source, XSObject destination );

/*!
 * @function    __XSString_ToString
 * @abstract    Object description
 * @param       object  A pointer to the object
 * @result      The object's description
 */
XSString __XSString_ToString( XSObject object );

/*!
 * @function    __XSString_Equals
 * @abstract    Object comparison
 * @param       object1 The first object to compare
 * @param       object1 The second object to compare
 * @result      YES if both objects are equals, otherwise NO
 */
BOOL __XSString_Equals( XSObject object1, XSObject object2 );

XS_EXTERN_C_END

#endif /* ___XS_STRING_H_ */
