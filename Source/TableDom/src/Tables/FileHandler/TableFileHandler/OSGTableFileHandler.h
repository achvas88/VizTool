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

#ifndef _OSGTABLEFILEHANDLER_H_
#define _OSGTABLEFILEHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTableDomDef.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>

#include "OSGBaseTypes.h"
#include "OSGTableFileType.h"
#include "OSGPathType.h"
#include "OSGSingletonHolder.h"

#include "OSGTable.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBTABLEDOM_DLLMAPPING TableFileHandlerBase
{
     /*==========================  PUBLIC  =================================*/
   public:
 
     /*---------------------------------------------------------------------*/
     virtual ~TableFileHandlerBase(void);
 
     /*---------------------------------------------------------------------*/
	 virtual TableFileTypeP getFileType(const std::string& FileExtension, UInt32 Flags = TableFileType::OSG_READ_SUPPORTED |
                                              TableFileType::OSG_WRITE_SUPPORTED);
 
	 virtual std::vector<std::string> getSuffixList(UInt32 flags = TableFileType::OSG_READ_SUPPORTED |
                                              TableFileType::OSG_WRITE_SUPPORTED) const;
 
     /*---------------------------------------------------------------------*/
     typedef void (*progresscbfp) (UInt32 p);
     void setReadProgressCB(progresscbfp fp);
     progresscbfp getReadProgressCB(void);
 
     /*---------------------------------------------------------------------*/
     virtual TableDOMTransitPtr		read(std::istream &InputStream, const std::string& Extension);
  
	 virtual TableDOMTransitPtr		read(const  BoostPath& FilePath);
	
	 virtual TableDOMTransitPtr		forceRead(const  BoostPath& FilePath);
	 

  
     /*---------------------------------------------------------------------*/
	 virtual bool write(TableDOM* const Doc, std::ostream &OutputStream, const std::string& Extension,bool Compress = false);
     virtual bool write(TableDOM* const Doc, const BoostPath& FilePath, bool Compress = false);
	 virtual bool forceWrite(TableDOM* const Doc, const BoostPath& FilePath, bool Compress = false);
 
     /*---------------------------------------------------------------------*/
     //virtual bool               setOptions(const Char8 *suffix, const Char8 *options);
     //virtual const Char8        *getOptions(const Char8 *suffix);

     const BoostPath& getRootFilePath(void) const;
 
     /*=========================  PROTECTED  ===============================*/
   protected:
 
     typedef std::vector<TableFileTypeP> FileTypeVector;
	 typedef std::map <std::string, FileTypeVector> FileTypeMap;
 
     /*---------------------------------------------------------------------*/
            FileTypeMap       _SuffixTypeMap;
 
 
     bool addTableFileType(TableFileTypeP FileType);
     bool subTableFileType(TableFileTypeP FileType);
     
     /*---------------------------------------------------------------------*/
     TableFileHandlerBase(void);
     TableFileHandlerBase(const TableFileHandlerBase &obj);
 
     /*==========================  PRIVATE  ================================*/
   private:
 
    template <class SingletonT>
    friend class SingletonHolder;
    
     friend class OSG_CONTRIBTABLEDOM_DLLMAPPING TableFileType;
     
     void operator =(const TableFileHandlerBase &source);
 
     typedef struct
     {
         UInt64 length;
         std::istream *is;
     } progressS;
 
     void startReadProgressThread(std::istream &is);
     void stopReadProgressThread(void);
     static void readProgress(void *data);
 
     progresscbfp    _ReadProgressFP;
     progressS       _ProgressData;
     bool            _ReadReady;

     BoostPath _RootFilePath;
};

typedef SingletonHolder<TableFileHandlerBase> TableFileHandler;

typedef TableFileHandler* TableFileHandlerP;

OSG_END_NAMESPACE

#include "OSGTableFileHandler.inl"

#endif /* _OSGTableFILEHANDLER_H_ */


