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

#ifndef _OSGPLAINTABLEDOMLEAFCELL_H_
#define _OSGPLAINTABLEDOMLEAFCELL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPlainTableDOMLeafCellBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PlainTableDOMLeafCell class. See \ref
           PageContribTableDomPlainTableDOMLeafCell for a description.
*/

class OSG_CONTRIBTABLEDOM_DLLMAPPING PlainTableDOMLeafCell : public PlainTableDOMLeafCellBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PlainTableDOMLeafCellBase Inherited;
    typedef PlainTableDOMLeafCell     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PlainTableDOMLeafCellBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PlainTableDOMLeafCell(void);
    PlainTableDOMLeafCell(const PlainTableDOMLeafCell &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PlainTableDOMLeafCell(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PlainTableDOMLeafCellBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PlainTableDOMLeafCell &source);
};

typedef PlainTableDOMLeafCell *PlainTableDOMLeafCellP;

OSG_END_NAMESPACE

#include "OSGPlainTableDOMLeafCellBase.inl"
#include "OSGPlainTableDOMLeafCell.inl"

#endif /* _OSGPLAINTABLEDOMLEAFCELL_H_ */
