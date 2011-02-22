/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGPLAINTABLEDOM_H_
#define _OSGPLAINTABLEDOM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPlainTableDOMBase.h"
#include <boost/any.hpp>

OSG_BEGIN_NAMESPACE

/*! \brief PlainTableDOM class. See \ref
           PageContribTableDomPlainTableDOM for a description.
*/

class OSG_CONTRIBTABLEDOM_DLLMAPPING PlainTableDOM : public PlainTableDOMBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PlainTableDOMBase Inherited;
    typedef PlainTableDOM     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;


	virtual void insertValue(UInt32 row,UInt32 column,const boost::any value);

	virtual void print(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PlainTableDOMBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PlainTableDOM(void);
    PlainTableDOM(const PlainTableDOM &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PlainTableDOM(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PlainTableDOMBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PlainTableDOM &source);
};

typedef PlainTableDOM *PlainTableDOMP;

OSG_END_NAMESPACE

#include "OSGPlainTableDOMBase.inl"
#include "OSGPlainTableDOM.inl"

#endif /* _OSGPLAINTABLEDOM_H_ */
