/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             Achyuthan Vasanth (achvas88@gmail.com)*
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

#ifndef _OSGTABLEDOM_H_
#define _OSGTABLEDOM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableDOMBase.h"
#include "OSGCell.h"   

OSG_BEGIN_NAMESPACE

/*! \brief TableDOM class. See \ref
           PageContribTableDomTableDOM for a description.
*/

class OSG_CONTRIBTABLEDOM_DLLMAPPING TableDOM : public TableDOMBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TableDOMBase Inherited;
    typedef TableDOM     Self;

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

    /*! \}                                                                 */

	virtual UInt32 getRowLength(UInt32 row);
	virtual UInt32 getMaxHeight(void);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TableDOMBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableDOM(void);
    TableDOM(const TableDOM &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableDOM(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableDOMBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableDOM &source);
};

typedef TableDOM *TableDOMP;

OSG_END_NAMESPACE

#include "OSGTableDOMBase.inl"
#include "OSGTableDOM.inl"

#endif /* _OSGTABLEDOM_H_ */
