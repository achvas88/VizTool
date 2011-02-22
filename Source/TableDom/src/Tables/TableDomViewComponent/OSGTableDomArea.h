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

#ifndef _OSGTABLEDOMAREA_H_
#define _OSGTABLEDOMAREA_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTableDomAreaBase.h"
#include "OSGColorLayerFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief TableDomArea class. See \ref
           PageContribTableDomTableDomArea for a description.
*/

class OSG_CONTRIBTABLEDOM_DLLMAPPING TableDomArea : public TableDomAreaBase
{
  protected:


	  void createDefaultFont(void);
	  void createDefaultLayer(void);
	  

    /*==========================  PUBLIC  =================================*/

  public:


    typedef TableDomAreaBase Inherited;
    typedef TableDomArea     Self;

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
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);


	virtual void drawInternal(Graphics * const TheGraphics, Real32 Opacity = 1.0f) const;

	void loadFile(const BoostPath& pathOfFile);
	void saveFile(const BoostPath& pathOfFile);
	


	virtual void focusGained(FocusEventDetails* const details);
	virtual void focusLost(FocusEventDetails* const details);
	virtual void mouseReleased(MouseEventDetails* const details);
    void mouseDragged(MouseEventDetails* const details);
	void mouseDraggedAfterArming(MouseEventDetails* const details);
	void keyTyped(KeyEventDetails* const details);
	virtual void mouseClicked(MouseEventDetails* const details);
	virtual void mousePressed(MouseEventDetails* const details);

	void updatePreferredSize(void);
	virtual Vec2f getContentRequestedSize(void) const;

	virtual Vec2f getPreferredScrollableViewportSize(void);
    virtual Int32 getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft,
                                             const Pnt2f& VisibleRectBottomRight, 
                                             const UInt32& orientation, 
                                             const Int32& direction);

  	virtual Int32 getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, 
                                              const Pnt2f& VisibleRectBottomRight, 
                                              const UInt32& orientation, 
                                              const Int32& direction);
    //Return true if a viewport should always force the height of this Scrollable to match the height of the viewport.
    virtual bool getScrollableTracksViewportHeight(void);

    //Return true if a viewport should always force the width of this Scrollable to match the width of the viewport.
    virtual bool getScrollableTracksViewportWidth(void);

    //Return true if a viewport should always force the height of this Scrollable to be at at least the height of the viewport.
    virtual bool getScrollableHeightMinTracksViewport(void);

    //Return true if a viewport should always force the width of this Scrollable to be at at least the width of the viewport.
    virtual bool getScrollableWidthMinTracksViewport(void);

	UInt32 getTopmostVisibleLineNumber(void);
	UInt32 getLinesToBeDisplayed(void);
	Real32 getHeightOfLine(void);
	
	

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

	
	
	void handleTableModelChanged();

	//Gives notification that an attribute or set of attributes changed.
    void handleTableChanged(TableDOMEventDetails* const details);

	//Gives notification that there was an insert of something into the document.
	void handleTableInsert(TableDOMEventDetails* const details);

	//Gives notification when something has been removed
	void handleTableRemove(TableDOMEventDetails* const details);


    boost::signals2::connection _TableChangedConnection,
                                _TableInsertConnection,
                                _TableRemoveConnection;

    // Variables should all be in TableDomAreaBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TableDomArea(void);
    TableDomArea(const TableDomArea &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TableDomArea(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TableDomAreaBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TableDomArea &source);
};

typedef TableDomArea *TableDomAreaP;

OSG_END_NAMESPACE

#include "OSGTableDomAreaBase.inl"
#include "OSGTableDomArea.inl"

#endif /* _OSGTABLEDOMAREA_H_ */
