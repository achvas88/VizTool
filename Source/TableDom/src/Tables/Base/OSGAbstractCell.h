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

#ifndef _OSGABSTRACTCELL_H_
#define _OSGABSTRACTCELL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractCellBase.h"
#include "boost/any.hpp"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractCell class. See \ref
           PageContribTableDomAbstractCell for a description.
*/

class OSG_CONTRIBTABLEDOM_DLLMAPPING AbstractCell : public AbstractCellBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractCellBase Inherited;
    typedef AbstractCell     Self;

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

	virtual void setValue(const boost::any theValue) = 0;
	virtual boost::any getValue(void) const = 0;
	virtual Cell* getCell(UInt32 value) const = 0;
	virtual Cell* createRow(UInt32 value) = 0;
	virtual Cell* createColumn(UInt32 value) = 0;
	virtual void print(void) const = 0;
	virtual UInt32 getMaximumColumn(void) const = 0;
	virtual UInt32 getMaximumRow(void) const = 0;
	virtual void setMaximumColumn(UInt32 value) = 0;
	virtual void setMaximumRow(UInt32 value) = 0; 
	
	
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AbstractCellBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractCell(void);
    AbstractCell(const AbstractCell &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractCell(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractCellBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractCell &source);
};

typedef AbstractCell *AbstractCellP;

OSG_END_NAMESPACE

#include "OSGAbstractCellBase.inl"
#include "OSGAbstractCell.inl"

#endif /* _OSGABSTRACTCELL_H_ */
