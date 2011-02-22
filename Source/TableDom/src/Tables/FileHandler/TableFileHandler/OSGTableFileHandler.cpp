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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEUSERINTERFACELIB

#include "OSGConfig.h"

#include "OSGTableFileHandler.h"
#include <fstream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/algorithm/string.hpp>

#include "OSGSingletonHolder.ins"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TableFileHandlerBase
A TableFileHandlerBase. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_SINGLETON_INST(TableFileHandlerBase, addPostFactoryExitFunction)

template class SingletonHolder<TableFileHandlerBase>;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

bool TableFileHandlerBase::addTableFileType(TableFileTypeP FileType)
{
    bool retCode = false;

	std::vector<std::string>::const_iterator FileSuffixItor;
         FileTypeMap   ::iterator FileSuffixMapSearch;

	std::string Suffix;

	for(  FileSuffixItor  = FileType->getSuffixList().begin();
          FileSuffixItor != FileType->getSuffixList().end();
        ++FileSuffixItor)
    {
        Suffix = (*FileSuffixItor);
		boost::algorithm::to_lower(Suffix);

        FileSuffixMapSearch = TableFileHandler::the()->_SuffixTypeMap.find(Suffix);

        if (FileSuffixMapSearch != TableFileHandler::the()->_SuffixTypeMap.end())
        {
            TableFileHandler::the()->_SuffixTypeMap[Suffix].push_back(FileType);

            SWARNING << "Added an file type with suffix "
                     << Suffix
                     << " non overriding at the end of the list"
                     << std::endl;
        }
        else
        {
            FileTypeVector pTmpList;

            pTmpList.push_back(FileType);

            TableFileHandler::the()->_SuffixTypeMap[Suffix] = pTmpList;

            retCode = true;
        }
    }

    return retCode;
}

bool TableFileHandlerBase::subTableFileType(TableFileTypeP FileType)
{
    bool retCode = false;

	std::vector<std::string>::const_iterator FileSuffixItor;
         FileTypeMap   ::iterator FileSuffixMapSearch;

    std::string Suffix;

    for(  FileSuffixItor  = FileType->getSuffixList().begin();
          FileSuffixItor != FileType->getSuffixList().end();
        ++FileSuffixItor)
    {
        Suffix = (*FileSuffixItor);
		boost::algorithm::to_lower(Suffix);

        FileSuffixMapSearch = TableFileHandler::the()->_SuffixTypeMap.find(Suffix);
        if (FileSuffixMapSearch != TableFileHandler::the()->_SuffixTypeMap.end())
        {
            TableFileHandler::the()->_SuffixTypeMap.erase(FileSuffixMapSearch);
            retCode = true;
        }
    }
    return retCode;
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

TableFileTypeP TableFileHandlerBase::getFileType(const std::string& FileExtension, UInt32 Flags)
{
	FileTypeMap::const_iterator SearchItor(_SuffixTypeMap.find(FileExtension));

	if(SearchItor != _SuffixTypeMap.end())
	{
		for(FileTypeVector::const_iterator VecItor(SearchItor->second.begin()) ; VecItor != SearchItor->second.end() ; ++VecItor)
		{
			if((*VecItor)->getFlags() & Flags)
			{
				return (*VecItor);
			}
		}
		return NULL;
	}
	else
	{
		return NULL;
	}
}

std::vector<std::string> TableFileHandlerBase::getSuffixList(UInt32 flags) const
{
	std::vector<std::string> FileTypesResult;

	for(FileTypeMap::const_iterator MapItor(_SuffixTypeMap.begin()) ; MapItor != _SuffixTypeMap.end() ; ++MapItor)
	{
		for(FileTypeVector::const_iterator VecItor(MapItor->second.begin()) ; VecItor != MapItor->second.end() ; ++VecItor)
		{
			if((*VecItor)->getFlags() & flags)
			{
				std::vector<std::string> Suffixes((*VecItor)->getSuffixList());
				for(std::vector<std::string>::const_iterator SuffixItor(Suffixes.begin()) ; SuffixItor<Suffixes.end() ; ++SuffixItor)
				{
					FileTypesResult.push_back(*SuffixItor);
				}
			}
		}
	}

	return FileTypesResult;
}

 void TableFileHandlerBase::setReadProgressCB(progresscbfp fp)
 {
	 stopReadProgressThread();
     _ReadProgressFP = fp;
 }

 TableFileHandlerBase::progresscbfp TableFileHandlerBase::getReadProgressCB(void)
 {
	 return _ReadProgressFP;
 }


 TableDOMTransitPtr TableFileHandlerBase::read(std::istream &InputStream, const std::string& Extension)
 {
	 TableDOMRefPtr Result;
	 //Get the FileType for this extension
	 TableFileTypeP TheFileType(getFileType(Extension, TableFileType::OSG_READ_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TableFileHandlerBase::read(): Cannot read Field Container stream, because no File types support " << Extension <<  " extension." << std::endl;
		return TableDOMTransitPtr(NULL);
	 }
	 else
	 {
		 //Read from the input stream
		 startReadProgressThread(InputStream);
		 Result = TheFileType->read(InputStream, Extension);
		 stopReadProgressThread();
	 }
	 return TableDOMTransitPtr(Result);
 }

 TableDOMTransitPtr TableFileHandlerBase::read(const BoostPath& FilePath)
 {
	 TableDOMRefPtr Result;
	 //Determine if the file exists
	 if(!boost::filesystem::exists(FilePath))
	 {
		SWARNING << "TableFileHandlerBase::read(): " << FilePath.string() << " does not exists." << std::endl;
		return TableDOMTransitPtr(NULL);
	 }

	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

     //Get the Parent Directory Path of the file
     _RootFilePath = FilePath;
     _RootFilePath.remove_leaf();

	 //Get the FileType for this extension
	 TableFileTypeP TheFileType(getFileType(Extension, TableFileType::OSG_READ_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TableFileHandlerBase::read(): Cannot read Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return TableDOMTransitPtr(NULL);
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ifstream InputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!InputStream)
		 {
			SWARNING << "TableFileHandlerBase::read(): Couldn't open input stream for file " << FilePath.string() << std::endl;
			return TableDOMTransitPtr(NULL);
		 }
		 else
		 {
             //Read from the input stream
             startReadProgressThread(InputStream);
             Result = TheFileType->read(InputStream, FilePath.string());
             stopReadProgressThread();
             
			 InputStream.close();
		 }
	 }

	 return TableDOMTransitPtr(Result);
 }

 
 TableDOMTransitPtr TableFileHandlerBase::forceRead(const BoostPath& FilePath)
 {
	 TableDOMRefPtr Result;
	 //Determine if the file exists
	 if(!boost::filesystem::exists(FilePath))
	 {
		SWARNING << "TableFileHandlerBase::read(): " << FilePath.string() << " does not exists." << std::endl;
		return TableDOMTransitPtr(NULL);
	 }

	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

     //Get the Parent Directory Path of the file
     _RootFilePath = FilePath;
     _RootFilePath.remove_leaf();

	 //Get the FileType of a "txt" file (Forcing the document to be opened as a txt file)
	 TableFileTypeP TheFileType(getFileType("csv", TableFileType::OSG_READ_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TableFileHandlerBase::read(): Cannot read Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return TableDOMTransitPtr(NULL);
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ifstream InputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!InputStream)
		 {
			SWARNING << "TableFileHandlerBase::read(): Couldn't open input stream for file " << FilePath.string() << std::endl;
			return TableDOMTransitPtr(NULL);
		 }
		 else
		 {
             //Read from the input stream
             startReadProgressThread(InputStream);
             Result = TheFileType->read(InputStream, FilePath.string());
             stopReadProgressThread();
             
			 InputStream.close();
		 }
	 }

	return TableDOMTransitPtr(Result);
 }

bool TableFileHandlerBase::write(TableDOM* const Doc, std::ostream &OutputStream, const std::string& Extension,bool Compress)
{
	 //Get the FileType for this extension
	 TableFileTypeP TheFileType(getFileType(Extension, TableFileType::OSG_WRITE_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TableFileHandlerBase::write(): Cannot write Field Container outstream, because no File types support " << Extension <<  " extension." << std::endl;
		return false;
	 }
	 else
	 {
		 if(Compress)
		 {
		 }
		 else
		 {
		 }
		 return TheFileType->write(Doc, OutputStream, Extension);
	 }
}

bool TableFileHandlerBase::write(TableDOM* const Doc, const BoostPath& FilePath, bool Compress)
{
	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

	 _RootFilePath = FilePath;
     _RootFilePath.remove_filename();

	 //Get the FileType for this extension
	 TableFileTypeP TheFileType(getFileType(Extension, TableFileType::OSG_WRITE_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TableFileHandlerBase::write(): Cannot write Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return false;
	 }
	 else
	 {
		 //Open up the input stream of the file
		 std::ofstream OutputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!OutputStream)
		 {
			SWARNING << "TableFileHandlerBase::write(): Couldn't open output stream for file " << FilePath.string() << std::endl;
			return false;
		 }
		 else
		 {
			 bool Result;
			 Result = write(Doc, OutputStream, Extension, Compress);
			 OutputStream.close();
			 return Result;
		 }
	 }
}


bool TableFileHandlerBase::forceWrite(TableDOM* const Doc, const BoostPath& FilePath, bool Compress)
{
	 //Determine the file extension
	 std::string Extension(boost::filesystem::extension(FilePath));
	 boost::algorithm::trim_if(Extension,boost::is_any_of("."));

	 _RootFilePath = FilePath;
     _RootFilePath.remove_filename();

	 //Get the FileType for this extension
	 TableFileTypeP TheFileType(getFileType("csv", TableFileType::OSG_WRITE_SUPPORTED));

	 //Is that extension supported for reading
	 if(TheFileType == NULL)
	 {
		SWARNING << "TableFileHandlerBase::write(): Cannot write Field Container file: " << FilePath.string() << ", because no File types support " << Extension <<  " extension." << std::endl;
		return false;
	 }
	 else
	 {
		 //Open up the output stream of the file
		 std::ofstream OutputStream(FilePath.string().c_str(), std::ios::binary);

		 if(!OutputStream)
		 {
			SWARNING << "TableFileHandlerBase::write(): Couldn't open output stream for file " << FilePath.string() << std::endl;
			return false;
		 }
		 else
		 {
			 bool Result;
			 Result = write(Doc, OutputStream, "csv", Compress);
			 OutputStream.close();
			 return Result;
		 }
	 }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void TableFileHandlerBase::startReadProgressThread(std::istream &is)
{
    if(_ReadProgressFP == NULL)
        return;

    // get length of the stream.
    _ProgressData.is = &is;
    is.seekg(0, std::ios::end);
    _ProgressData.length = is.tellg();
    is.seekg(0, std::ios::beg);

    ThreadRefPtr pt = dynamic_cast<Thread *>(
            ThreadManager::the()->findThread("OSG::FileIOReadProgressThread"));

    if(pt == NULL)
        pt = dynamic_pointer_cast<Thread>(
                ThreadManager::the()->getThread("OSG::FileIOReadProgressThread",1));

    _ReadReady = false;
    if(pt != NULL)
        pt->runFunction(readProgress, 0, NULL);
    else
        SWARNING << "Couldn't create read progress thread!" << std::endl;
}

void TableFileHandlerBase::stopReadProgressThread(void)
{
    if(_ReadProgressFP == NULL)
        return;

    Thread* pt = dynamic_cast<Thread *>(
            ThreadManager::the()->findThread("OSG::FileIOReadProgressThread"));

    if(pt != NULL)
    {
        // terminate thread
        _ReadReady = true;
        Thread::join(pt);
    }
}

void TableFileHandlerBase::readProgress(void *data)
{
    UInt32 p = 0;
    while(p < 100 && !TableFileHandler::the()->_ReadReady)
    {
        if(!TableFileHandler::the()->_ProgressData.is->eof() &&
           !TableFileHandler::the()->_ProgressData.is->bad())
        {
            UInt64 pos = TableFileHandler::the()->_ProgressData.is->tellg();
            p = UInt32((pos * 100) / TableFileHandler::the()->_ProgressData.length);
            if(p > 100)
                p = 100;
        }
        else
        {
            p = 100;
        }

        TableFileHandler::the()->_ReadProgressFP(p);
        osgSleep(100);
    }
    if(p < 100)
        TableFileHandler::the()->_ReadProgressFP(100);
}

/*----------------------- constructors & destructors ----------------------*/

TableFileHandlerBase::TableFileHandlerBase(void) :
    _ReadProgressFP(NULL),
    _ProgressData(),
    _ReadReady(false)
{
}

TableFileHandlerBase::TableFileHandlerBase(const TableFileHandlerBase &obj)
{
	SWARNING << "In TableFileHandlerBase copy constructor" << std::endl;
}

TableFileHandlerBase::~TableFileHandlerBase(void)
{
}

/*----------------------------- class specific ----------------------------*/

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

