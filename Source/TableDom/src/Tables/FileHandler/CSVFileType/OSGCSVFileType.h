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
#ifndef _OSGCSVFILETYPE_H_
#define _OSGCSVFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTableDomDef.h"

#include <boost/function.hpp>
#include <utility>
#include "OSGTableFileType.h"
#include "OSGTableFileHandler.h"
#include "OSGContainerIdMapper.h"
#include "OSGFieldContainer.h"

#include "OSGPlainTableDOM.h"
#include "OSGPlainTableDOMBranchCell.h"
#include "OSGPlainTableDOMLeafCell.h"

#include "string"

OSG_BEGIN_NAMESPACE


class OSG_CONTRIBTABLEDOM_DLLMAPPING CSVFileType : public TableFileType
{
/*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    static CSVFileType *the(void);

    /*---------------------------------------------------------------------*/
    virtual std::string getName(void) const;

    /*---------------------------------------------------------------------*/
    virtual ~CSVFileType(void);

    /*---------------------------------------------------------------------*/
     virtual TableDOMTransitPtr read(std::istream &is,
		                     const std::string& FileNameOrExtension);

    /*---------------------------------------------------------------------*/
     virtual bool write(TableDOM* const Doc, std::ostream &os,
                        const std::string& FileNameOrExtension);

    
    /*=========================  PROTECTED  ===============================*/
protected:

	void removeSlashRandSlashN(std::string& word);

    typedef TableFileType Inherited;
    static       CSVFileType*  _the;

    /*---------------------------------------------------------------------*/
    CSVFileType(void);

    CSVFileType(const CSVFileType &obj);

    /*==========================  PRIVATE  ================================*/
private:

    void operator =(const CSVFileType &source);
};

typedef CSVFileType* CSVFileTypeP;

OSG_END_NAMESPACE

#include "OSGCSVFileType.inl"

#endif /* _OSGCSVFILETYPE_H_ */


