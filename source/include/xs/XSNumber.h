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
 * @header      XSNumber.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    XSNumber class functions
 */

#ifndef _XS_NUMBER_H_
#define _XS_NUMBER_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

/*!
 * @typedef     XSNumber
 * @abstract    Opaque type for the XSNumber objects
 */
typedef struct XSNumber * XSNumber;

/*!
 * @function    XSNumber_Alloc
 * @abstract    Object allocator
 * @result      The allocated object
 */
XSStatic XSNumber XSNumber_Alloc( void );

/*!
 * @function    XSNumber_Init
 * @abstract    Creates a number
 * @param       xsThis      The number object
 * @param       value       The BOOL value
 * @result      The number object
 */
XSObject XSNumber_Init( XSObject xsThis );

/*!
 * @function    XSNumber_InitWithBool
 * @abstract    Creates a number with a BOOL value
 * @param       xsThis      The number object
 * @param       value       The BOOL value
 * @result      The number object
 */
XSNumber XSNumber_InitWithBool( XSNumber xsThis, BOOL value );

/*!
 * @function    XSNumber_InitWithChar
 * @abstract    Creates a number with a char value
 * @param       xsThis      The number object
 * @param       value       The char value
 * @result      The number object
 */
XSNumber XSNumber_InitWithChar( XSNumber xsThis, char value );

/*!
 * @function    XSNumber_InitWithUnsignedChar
 * @abstract    Creates a number with an unsigned char value
 * @param       xsThis      The number object
 * @param       value       The unsigned char value
 * @result      The number object
 */
XSNumber XSNumber_InitWithUnsignedChar( XSNumber xsThis, unsigned char value );

/*!
 * @function    XSNumber_InitWithShort
 * @abstract    Creates a number with a short value
 * @param       xsThis      The number object
 * @param       value       The short value
 * @result      The number object
 */
XSNumber XSNumber_InitWithShort( XSNumber xsThis, short value );

/*!
 * @function    XSNumber_InitWithUnsignedShort
 * @abstract    Creates a number with an unsigned short value
 * @param       xsThis      The number object
 * @param       value       The unsigned short value
 * @result      The number object
 */
XSNumber XSNumber_InitWithUnsignedShort( XSNumber xsThis, unsigned short value );

/*!
 * @function    XSNumber_InitWithInt
 * @abstract    Creates a number with an int value
 * @param       xsThis      The number object
 * @param       value       The int value
 * @result      The number object
 */
XSNumber XSNumber_InitWithInt( XSNumber xsThis, int value );

/*!
 * @function    XSNumber_InitWithUnsignedInt
 * @abstract    Creates a number with an unsigned int value
 * @param       xsThis      The number object
 * @param       value       The unsigned int value
 * @result      The number object
 */
XSNumber XSNumber_InitWithUnsignedInt( XSNumber xsThis, unsigned int value );

/*!
 * @function    XSNumber_InitWithLong
 * @abstract    Creates a number with a long value
 * @param       xsThis      The number object
 * @param       value       The long value
 * @result      The number object
 */
XSNumber XSNumber_InitWithLong( XSNumber xsThis, long value );

/*!
 * @function    XSNumber_InitWithUnsignedLong
 * @abstract    Creates a number with an unsigned long value
 * @param       xsThis      The number object
 * @param       value       The unsigned long value
 * @result      The number object
 */
XSNumber XSNumber_InitWithUnsignedLong( XSNumber xsThis, unsigned long value );

/*!
 * @function    XSNumber_InitWithLongLong
 * @abstract    Creates a number with a long long value
 * @param       xsThis      The number object
 * @param       value       The long long value
 * @result      The number object
 */
XSNumber XSNumber_InitWithLongLong( XSNumber xsThis, long long value );

/*!
 * @function    XSNumber_InitWithUnsignedLongLong
 * @abstract    Creates a number with an unsigned long long value
 * @param       xsThis      The number object
 * @param       value       The unsigned long long value
 * @result      The number object
 */
XSNumber XSNumber_InitWithUnsignedLongLong( XSNumber xsThis, unsigned long long value );

/*!
 * @function    XSNumber_InitWithFloat
 * @abstract    Creates a number with a float value
 * @param       xsThis      The number object
 * @param       value       The float value
 * @result      The number object
 */
XSNumber XSNumber_InitWithFloat( XSNumber xsThis, float value );

/*!
 * @function    XSNumber_InitWithDouble
 * @abstract    Creates a number with a double value
 * @param       xsThis      The number object
 * @param       value       The double value
 * @result      The number object
 */
XSNumber XSNumber_InitWithDouble( XSNumber xsThis, double value );

/*!
 * @function    XSNumber_InitWithInteger
 * @abstract    Creates a number with an integer value
 * @param       xsThis      The number object
 * @param       value       The integer value
 * @result      The number object
 */
XSNumber XSNumber_InitWithInteger( XSNumber xsThis, XSInteger value );

/*!
 * @function    XSNumber_InitWithUnsignedInteger
 * @abstract    Creates a number with an unsigned integer value
 * @param       xsThis      The number object
 * @param       value       The unsigned integer value
 * @result      The number object
 */
XSNumber XSNumber_InitWithUnsignedInteger( XSNumber xsThis, XSUInteger value );

void XSNumber_SetBool( XSNumber xsThis, BOOL value );

void XSNumber_SetChar( XSNumber xsThis, char value );

void XSNumber_SetUnsignedChar( XSNumber xsThis, unsigned char value );

void XSNumber_SetShort( XSNumber xsThis, short value );

void XSNumber_SetUnsignedShort( XSNumber xsThis, unsigned short value );

void XSNumber_SetInt( XSNumber xsThis, int value );

void XSNumber_SetUnsignedInt( XSNumber xsThis, unsigned int value );

void XSNumber_SetLong( XSNumber xsThis, long value );

void XSNumber_SetUnsignedLong( XSNumber xsThis, unsigned long value );

void XSNumber_SetLongLong( XSNumber xsThis, long long value );

void XSNumber_SetUnsignedLongLong( XSNumber xsThis, unsigned long long value );

void XSNumber_SetFloat( XSNumber xsThis, float value );

void XSNumber_SetDouble( XSNumber xsThis, double value );

void XSNumber_SetInteger( XSNumber xsThis, XSInteger value );

void XSNumber_SetUnsignedInteger( XSNumber xsThis, XSUInteger value );

BOOL XSNumber_GetBool( XSNumber xsThis );

char XSNumber_GetChar( XSNumber xsThis );

unsigned char XSNumber_GetUnsignedChar( XSNumber xsThis );

short XSNumber_GetShort( XSNumber xsThis );

unsigned short XSNumber_GetUnsignedShort( XSNumber xsThis );

int XSNumber_GetInt( XSNumber xsThis );

unsigned int XSNumber_GetUnsignedInt( XSNumber xsThis );

long XSNumber_GetLong( XSNumber xsThis );

unsigned long XSNumber_GetUnsignedLong( XSNumber xsThis );

long long XSNumber_GetLongLong( XSNumber xsThis );

unsigned long long XSNumber_GetUnsignedLongLong( XSNumber xsThis );

float XSNumber_GetFloat( XSNumber xsThis );

double XSNumber_GetDouble( XSNumber xsThis );

XSInteger XSNumber_GetInteger( XSNumber xsThis );

XSUInteger XSNumber_GetUnsignedInteger( XSNumber xsThis );

XS_EXTERN_C_END

#endif /* _XS_NUMBER_H_ */
