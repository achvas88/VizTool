/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class TableDOMEventDetails!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &TableDOMEventDetailsBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 TableDOMEventDetailsBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 TableDOMEventDetailsBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/


//! Get the value of the TableDOMEventDetails::_sfTableDOM field.
inline
TableDOM * TableDOMEventDetailsBase::getTableDOM(void) const
{
    return _sfTableDOM.getValue();
}

//! Set the value of the TableDOMEventDetails::_sfTableDOM field.
inline
void TableDOMEventDetailsBase::setTableDOM(TableDOM * const value)
{
    editSField(TableDOMFieldMask);

    _sfTableDOM.setValue(value);
}
//! Get the value of the TableDOMEventDetails::_sfRow field.

inline
UInt32 &TableDOMEventDetailsBase::editRow(void)
{
    editSField(RowFieldMask);

    return _sfRow.getValue();
}

//! Get the value of the TableDOMEventDetails::_sfRow field.
inline
      UInt32  TableDOMEventDetailsBase::getRow(void) const
{
    return _sfRow.getValue();
}

//! Set the value of the TableDOMEventDetails::_sfRow field.
inline
void TableDOMEventDetailsBase::setRow(const UInt32 value)
{
    editSField(RowFieldMask);

    _sfRow.setValue(value);
}
//! Get the value of the TableDOMEventDetails::_sfColumn field.

inline
UInt32 &TableDOMEventDetailsBase::editColumn(void)
{
    editSField(ColumnFieldMask);

    return _sfColumn.getValue();
}

//! Get the value of the TableDOMEventDetails::_sfColumn field.
inline
      UInt32  TableDOMEventDetailsBase::getColumn(void) const
{
    return _sfColumn.getValue();
}

//! Set the value of the TableDOMEventDetails::_sfColumn field.
inline
void TableDOMEventDetailsBase::setColumn(const UInt32 value)
{
    editSField(ColumnFieldMask);

    _sfColumn.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void TableDOMEventDetailsBase::execSync (      TableDOMEventDetailsBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (TableDOMFieldMask & whichField))
        _sfTableDOM.syncWith(pFrom->_sfTableDOM);

    if(FieldBits::NoField != (RowFieldMask & whichField))
        _sfRow.syncWith(pFrom->_sfRow);

    if(FieldBits::NoField != (ColumnFieldMask & whichField))
        _sfColumn.syncWith(pFrom->_sfColumn);
}
#endif


inline
const Char8 *TableDOMEventDetailsBase::getClassname(void)
{
    return "TableDOMEventDetails";
}
OSG_GEN_CONTAINERPTR(TableDOMEventDetails);

OSG_END_NAMESPACE
