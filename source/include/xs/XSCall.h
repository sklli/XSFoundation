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
 * @file        __XSCall.h
 * @brief       Call functions
 * @author      Jean-David Gadina <macmade@eosgarden.com>
 */

#ifndef _XS_CALL_H_
#define _XS_CALL_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

void XSCall_Void( XSMethod * method, void * context );
char XSCall_Char( XSMethod * method, void * context );
short XSCall_Short( XSMethod * method, void * context );
int XSCall_Int( XSMethod * method, void * context );
long XSCall_Long( XSMethod * method, void * context );
long long XSCall_LongLong( XSMethod * method, void * context );
float XSCall_Float( XSMethod * method, void * context );
double XSCall_Double( XSMethod * method, void * context );
void * XSCall_Pointer( XSMethod * method, void * context );

XS_EXTERN_C_END

#endif /* _XS_CALL_H_ */
