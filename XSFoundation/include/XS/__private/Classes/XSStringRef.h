/*******************************************************************************
 * XSFoundation - XEOS C Foundation Library
 * 
 * Copyright (c) 2010-2014, Jean-David Gadina - www.xs-labs.com
 * All rights reserved.
 * 
 * XEOS Software License - Version 1.0 - December 21, 2012
 * 
 * Permission is hereby granted, free of charge, to any person or organisation
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to deal in the Software, with or without
 * modification, without restriction, including without limitation the rights
 * to use, execute, display, copy, reproduce, transmit, publish, distribute,
 * modify, merge, prepare derivative works of the Software, and to permit
 * third-parties to whom the Software is furnished to do so, all subject to the
 * following conditions:
 * 
 *      1.  Redistributions of source code, in whole or in part, must retain the
 *          above copyright notice and this entire statement, including the
 *          above license grant, this restriction and the following disclaimer.
 * 
 *      2.  Redistributions in binary form must reproduce the above copyright
 *          notice and this entire statement, including the above license grant,
 *          this restriction and the following disclaimer in the documentation
 *          and/or other materials provided with the distribution, unless the
 *          Software is distributed by the copyright owner as a library.
 *          A "library" means a collection of software functions and/or data
 *          prepared so as to be conveniently linked with application programs
 *          (which use some of those functions and data) to form executables.
 * 
 *      3.  The Software, or any substancial portion of the Software shall not
 *          be combined, included, derived, or linked (statically or
 *          dynamically) with software or libraries licensed under the terms
 *          of any GNU software license, including, but not limited to, the GNU
 *          General Public License (GNU/GPL) or the GNU Lesser General Public
 *          License (GNU/LGPL).
 * 
 *      4.  All advertising materials mentioning features or use of this
 *          software must display an acknowledgement stating that the product
 *          includes software developed by the copyright owner.
 * 
 *      5.  Neither the name of the copyright owner nor the names of its
 *          contributors may be used to endorse or promote products derived from
 *          this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT OWNER AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, TITLE AND NON-INFRINGEMENT ARE DISCLAIMED.
 * 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER, CONTRIBUTORS OR ANYONE DISTRIBUTING
 * THE SOFTWARE BE LIABLE FOR ANY CLAIM, DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN ACTION OF CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF OR IN CONNECTION WITH
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

/* $Id$ */

/*!
 * @header      XSStringRef.h
 * @copyright   (c) 2010-2014 - Jean-David Gadina - www.xs-labs.com
 * @author      Jean-David Gadina - www.xs-labs.com
 * @abstract    Private definitions for XSStringRef.h
 * @discussion  ...
 */

#ifndef __XS_H__
#error "Please include '<XS/XS.h>' instead of this file!"
#endif

#ifndef __XS___PRIVATE_CLASSES_XS_STRING_H__
#define __XS___PRIVATE_CLASSES_XS_STRING_H__

#include <XS/XSTypes.h>
#include <XS/XSMacros.h>

/*!
 * @typedef     __XSString_Properties
 * @abstract    String properties
 */
typedef enum
{
    __XSString_PropertiesMutable = 0x01  /*! String is mutable */
}
__XSString_Properties;

/*!
 * @struct      __XSString
 * @abstract    Structure for XSString
 */
struct __XSString
{
    char              * cString;        /*! The C string */
    XSRecursiveLockRef  lock;           /*! The lock for thread-safety */
    XSUInteger          length;         /* The length */
    XSUInteger          capacity;       /*! The string capacity */
    int                 properties;     /*! The string properties */
    char                 _pad_0[ 4 ];   /*! Padding */
};

/*!
 * @var         __XSString_ClassID
 * @abstract    Class ID
 */
XS_EXTERN XSClassID __XSString_ClassID;

/*!
 * @var         __XSString_Class
 * @abstract    Class info
 */
XS_EXTERN XSClassInfo __XSString_Class;

/*!
 * @function    __XSString_Initialize
 * @abstract    Class initializer
 */
XSStatic void __XSString_Initialize( void );

/*!
 * @function    __XSString_Constructor
 * @abstract    Class constructor callback
 * @param       object      The object beeing construct
 * @return      The new object
 */
XSStringRef __XSString_Constructor( XSStringRef object );

/*!
 * @function    __XSString_Destructor
 * @abstract    Class destructor callback
 * @param       object      The object beeing destruct
 */
void __XSString_Destructor( XSStringRef object );

/*!
 * @function    __XSString_Copy
 * @abstract    Class copy callback
 * @param       source      The object to copy
 * @param       destination The object beeing copied
 * @result      The copied object
 */
XSStringRef __XSString_Copy( XSStringRef source, XSStringRef destination );

/*!
 * @function    __XSString_Equals
 * @abstract    Class equals callback
 * @param       object1     The first object to compare
 * @param       object2     The second object to compare
 * @return      True if both objects are equals, otherwise false
 */
bool __XSString_Equals( XSStringRef object1, XSStringRef object2 );

/*!
 * @function    __XSString_ToString
 * @abstract    Class to-string callback
 * @param       object      The object for which to get a description
 * @return      The object's description
 */
const char * __XSString_ToString( XSStringRef object );

/*!
 * @function    __XSString_Create
 * @abstract    Creates an XSString object
 * @return      The XSString object
 */
XSStatic struct __XSString * __XSString_Create( void );

/*!
 * @function    __XSString_Lock
 * @abstract    Locks the internal string lock if necessary
 * @param       object      The string object
 * @discussion  Locking will only occure if the string is mutable, as immutable
 *              strings are de-facto thread-safe. This allows the same code
 *              for both string types, with a performance gain on immutable ones.
 */
void __XSString_Lock( XSStringRef object );

/*!
 * @function    __XSString_Unlock
 * @abstract    Unlocks the internal string lock if necessary
 * @param       object      The string object
 * @discussion  Unlocking will only occure if the string is mutable, as immutable
 *              strings are de-facto thread-safe. This allows the same code
 *              for both string types, with a performance gain on immutable ones.
 */
void __XSString_Unlock( XSStringRef object );

#endif /* __XS___PRIVATE_CLASSES_XS_STRING_H__ */
