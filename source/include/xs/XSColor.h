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
 * @header      XSData.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    XSColor class functions
 */

#ifndef _XS_COLOR_H_
#define _XS_COLOR_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

/*!
 * @typedef     XSColor
 * @abstract    Opaque type for the XSColor objects
 */
typedef struct XSColor * XSColor;

/*!
 * @function    __XSColor_Alloc
 * @abstract    Object allocator
 * @result      The allocated object
 */
XSStatic XSColor XSColor_Alloc( void );

/*!
 * @function    XSColor_Init
 * @abstract    Initialize a color object
 * @param       xsThis  The color object
 * @result      The color object
 */
XSObject XSColor_Init( XSObject xsThis );

/*!
 * @function    XSColor_InitWithRGB
 * @abstract    Creates a color with RGB components
 * @param       xsThis  The color object
 * @param       r       The red value
 * @param       g       The green value
 * @param       b       The blue value
 * @result      The color object
 */
XSColor XSColor_InitWithRGB( XSColor xsThis, XSFloat r, XSFloat g, XSFloat b );

/*!
 * @function    XSColor_InitWithHSL
 * @abstract    Creates a color with RGB components
 * @param       xsThis  The color object
 * @param       h       The hue value
 * @param       s       The saturation value
 * @param       l       The luminance value
 * @result      The color object
 */
XSColor XSColor_InitWithHSL( XSColor xsThis, XSFloat h, XSFloat s, XSFloat l );

/*!
 * @function    XSColor_InitWithHSV
 * @abstract    Creates a color with HSL components
 * @param       xsThis  The color object
 * @param       h       The hue value
 * @param       s       The saturation value
 * @param       v       The value value
 * @result      The color object
 */
XSColor XSColor_InitWithHSV( XSColor xsThis, XSFloat h, XSFloat s, XSFloat v );

/*!
 * @function    XSColor_InitWithRGBA
 * @abstract    Creates a color with RGB components
 * @param       xsThis  The color object
 * @param       r       The red value
 * @param       g       The green value
 * @param       b       The blue value
 * @param       a       The alpha value
 * @result      The color object
 */
XSColor XSColor_InitWithRGBA( XSColor xsThis, XSFloat r, XSFloat g, XSFloat b, XSFloat a );

/*!
 * @function    XSColor_InitWithHSLA
 * @abstract    Creates a color with RGB components
 * @param       xsThis  The color object
 * @param       h       The hue value
 * @param       s       The saturation value
 * @param       l       The luminance value
 * @param       a       The alpha value
 * @result      The color object
 */
XSColor XSColor_InitWithHSLA( XSColor xsThis, XSFloat h, XSFloat s, XSFloat l, XSFloat a );

/*!
 * @function    XSColor_InitWithHSVA
 * @abstract    Creates a color with HSL components
 * @param       xsThis  The color object
 * @param       h       The hue value
 * @param       s       The saturation value
 * @param       v       The value value
 * @param       a       The alpha value
 * @result      The color object
 */
XSColor XSColor_InitWithHSVA( XSColor xsThis, XSFloat h, XSFloat s, XSFloat v, XSFloat a );

/*!
 * @function    XSColor_BlackColor
 * @abstract    Creates a color with HSVA components
 * @result      The color object
 */
XSAutoreleased XSStatic XSColor XSColor_BlackColor( void );

/*!
 * @function    XSColor_WhiteColor
 * @abstract    Create a black color object
 * @result      The color object
 */
XSAutoreleased XSStatic XSColor XSColor_WhiteColor( void );

/*!
 * @function    XSColor_RedColor
 * @abstract    Creates a red color object
 * @result      The color object
 */
XSAutoreleased XSStatic XSColor XSColor_RedColor( void );

/*!
 * @function    XSColor_GreenColor
 * @abstract    Creates a green color object
 * @result      The color object
 */
XSAutoreleased XSStatic XSColor XSColor_GreenColor( void );

/*!
 * @function    XSColor_BlueColor
 * @abstract    Creates a blue color object
 * @result      The color object
 */
XSAutoreleased XSStatic XSColor XSColor_BlueColor( void );

/*!
 * @function    XSColor_GetRed
 * @abstract    Get the red component
 * @param       xsThis  The color object
 * @result      The red component
 */
XSFloat XSColor_GetRed( XSColor xsThis );

/*!
 * @function    XSColor_GetGreen
 * @abstract    Get the green component
 * @param       xsThis  The color object
 * @result      The green component
 */
XSFloat XSColor_GetGreen( XSColor xsThis );

/*!
 * @function    XSColor_GetBlue
 * @abstract    Get the blue component
 * @param       xsThis  The color object
 * @result      The blue component
 */
XSFloat XSColor_GetBlue( XSColor xsThis );

/*!
 * @function    XSColor_GetHue
 * @abstract    Get the hue component
 * @param       xsThis  The color object
 * @result      The hue component
 */
XSFloat XSColor_GetHue( XSColor xsThis );

/*!
 * @function    XSColor_GetSaturation
 * @abstract    Get the saturation component
 * @param       xsThis  The color object
 * @result      The saturation component
 */
XSFloat XSColor_GetSaturation( XSColor xsThis );

/*!
 * @function    XSColor_GetLuminance
 * @abstract    Get the luminance component
 * @param       xsThis  The color object
 * @result      The luminance component
 */
XSFloat XSColor_GetLuminance( XSColor xsThis );

/*!
 * @function    XSColor_GetValue
 * @abstract    Get the value component
 * @param       xsThis  The color object
 * @result      The value component
 */
XSFloat XSColor_GetValue( XSColor xsThis );

/*!
 * @function    XSColor_GetAlpha
 * @abstract    Get the alpha component
 * @param       xsThis  The color object
 * @result      The alpha component
 */
XSFloat XSColor_GetAlpha( XSColor xsThis );

/*!
 * @function    XSColor_SetRed
 * @abstract    Sets the red component
 * @param       xsThis  The color object
 * @param       v       The red component
 * @result      void
 */
void XSColor_SetRed( XSColor xsThis, XSFloat v );

/*!
 * @function    XSColor_SetGreen
 * @abstract    Sets the green component
 * @param       xsThis  The color object
 * @param       v       The green component
 * @result      void
 */
void XSColor_SetGreen( XSColor xsThis, XSFloat v );

/*!
 * @function    XSColor_SetBlue
 * @abstract    Sets the blue component
 * @param       xsThis  The color object
 * @param       v       The blue component
 * @result      void
 */
void XSColor_SetBlue( XSColor xsThis, XSFloat v );

/*!
 * @function    XSColor_SetHue
 * @abstract    Sets the hue component
 * @param       xsThis  The color object
 * @param       v       The hue component
 * @result      void
 */
void XSColor_SetHue( XSColor xsThis, XSFloat v );

/*!
 * @function    XSColor_SetSaturation
 * @abstract    Sets the saturation component
 * @param       xsThis  The color object
 * @param       v       The saturation component
 * @result      void
 */
void XSColor_SetSaturation( XSColor xsThis, XSFloat v );

/*!
 * @function    XSColor_SetLuminance
 * @abstract    Sets the luminance component
 * @param       xsThis  The color object
 * @param       v       The luminance component
 * @result      void
 */
void XSColor_SetLuminance( XSColor xsThis, XSFloat v );

/*!
 * @function    XSColor_SetValue
 * @abstract    Sets the value component
 * @param       xsThis  The color object
 * @param       v       The value component
 * @result      void
 */
void XSColor_SetValue( XSColor xsThis, XSFloat v );

/*!
 * @function    XSColor_SetAlpha
 * @abstract    Sets the alpha component
 * @param       xsThis  The color object
 * @param       v       The alpha component
 * @result      void
 */
void XSColor_SetAlpha( XSColor xsThis, XSFloat v );

XS_EXTERN_C_END

#endif /* _XS_COLOR_H_ */
