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

#ifndef _OSGABSTRACTBRANCHCELL_H_
#define _OSGABSTRACTBRANCHCELL_H_
#ifdef __sgi
#pragma once
#endif

#include <map>
#include "OSGAbstractBranchCellBase.h"
#include "boost/any.hpp"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractBranchCell class. See \ref
           PageContribTableDomAbstractBranchCell for a description.
*/

class OSG_CONTRIBTABLEDOM_DLLMAPPING AbstractBranchCell : public AbstractBranchCellBase
{
  protected:

	  std::map<UInt32,CellRefPtr> childrenMap;
	  UInt32 maxRow;
	  UInt32 maxCol;

	  
    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractBranchCellBase Inherited;
    typedef AbstractBranchCell     Self;

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

	virtual void setValue(const boost::any theValue);
	virtual boost::any getValue(void) const;
	virtual Cell* getCell(UInt32 value) const;
	virtual Cell* createRow(UInt32 value) = 0;
	virtual Cell* createColumn(UInt32 value) = 0;
	virtual void print(void) const;
	virtual std::map<UInt32,CellRefPtr>& getChildrenMap(void);
	virtual UInt32 getMaximumColumn(void) const;
	virtual UInt32 getMaximumRow(void) const;
	virtual void setMaximumColumn(UInt32 value);
	virtual void setMaximumRow(UInt32 value); 

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AbstractBranchCellBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractBranchCell(void);
    AbstractBranchCell(const AbstractBranchCell &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractBranchCell(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractBranchCellBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractBranchCell &source);
};

typedef AbstractBranchCell *AbstractBranchCellP;

OSG_END_NAMESPACE

#include "OSGAbstractBranchCellBase.inl"
#include "OSGAbstractBranchCell.inl"

#endif /* _OSGABSTRACTBRANCHCELL_H_ */
