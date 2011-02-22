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

#define OSG_COMPILETABLEDOMLIB

#include "OSGConfig.h"

#include "OSGCSVFileType.h"
#include "windows.h"
 

OSG_BEGIN_NAMESPACE


SYSTEMTIME now;

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CSVFileType
A CSVFileType. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CSVFileType*  CSVFileType::_the(new CSVFileType());

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

CSVFileType *CSVFileType::the(void)
{
	return _the;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::string CSVFileType::getName(void) const
{
	return std::string("CSVFileType");	// unnecessary function . Can be removed . There for convenience
}


void CSVFileType::removeSlashRandSlashN(std::string &word)
{
	std::string Temp="";
	for(UInt32 i=0;i<word.length();i++)
	{
		if(word[i]!='\r' && word[i]!='\n')
		{
			Temp+=word[i];
		}
	}
	word = Temp;
}


TableDOMTransitPtr CSVFileType::read(std::istream &InputStream,
	                     const std::string& FileNameOrExtension)
{
	PlainTableDOMRefPtr Result = PlainTableDOM::create();

	std::string text;
	UInt32 rowCount = 0;
	while(std::getline(InputStream,text))
	{
   	   std::string token="";
	   UInt32 columnCount = 0;
	   for(UInt32 i=0;i<text.size();i++)
	   {
		   if(text[i]==',')
		   {
			Result->insertValue(rowCount,columnCount,boost::any(token));
			columnCount++;
			token="";
		   }
		   else
		   {
			token+=text[i];
		   }
	   }
	   removeSlashRandSlashN(token);
	   Result->insertValue(rowCount,columnCount,boost::any(token));

	   if(Result->getRootCell()->getMaximumColumn() < columnCount+1 )
	   {
			Result->getRootCell()->setMaximumColumn(columnCount+1);
	   }

	   rowCount++;
	}

	if(Result->getRootCell()->getMaximumRow() < rowCount )
	{
		Result->getRootCell()->setMaximumRow(rowCount);
	}

	return TableDOMTransitPtr(Result);
}

bool CSVFileType::write(TableDOM* const Doc, std::ostream &OutputStream,
                    const std::string& FileNameOrExtension)
{
	PlainTableDOMRefPtr TheTable = dynamic_cast<PlainTableDOM*>(Doc);
	
	PlainTableDOMBranchCellRefPtr RootCell;
	RootCell = dynamic_cast<PlainTableDOMBranchCell*>(TheTable->getRootCell());	
	
	
	if(!RootCell) 
	{
		return false;
	}
	else
	{
		std::string rowInString="";
		std::map<UInt32,CellRefPtr> theChildrenMap = RootCell->getChildrenMap();
		
		for(std::map<UInt32,CellRefPtr>::const_iterator Itr(theChildrenMap.begin()) ; Itr!=theChildrenMap.end(); Itr++)
		{
			Cell* temp1 = Itr->second;
			PlainTableDOMBranchCellRefPtr theRow = dynamic_cast<PlainTableDOMBranchCell*>(temp1);

			std::map<UInt32,CellRefPtr> theChildrenMapofRow = theRow->getChildrenMap();
			rowInString="";
			for(std::map<UInt32,CellRefPtr>::const_iterator Itr2(theChildrenMapofRow.begin()) ; Itr2!=theChildrenMapofRow.end(); Itr2++)
			{
				Cell* temp2= Itr2->second;
				PlainTableDOMLeafCellRefPtr theCol = dynamic_cast<PlainTableDOMLeafCell*>(temp2);
				rowInString += boost::any_cast<std::string>(theCol->getValue()) + ",";
			}
			rowInString = rowInString.substr(0,rowInString.size()-1);
			OutputStream<<rowInString<<std::endl;
		}
		
		return true;
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CSVFileType::CSVFileType(void) : Inherited(TableFileType::ExtensionVector(1, std::string("csv")),
        TableFileType::OSG_READ_SUPPORTED | TableFileType::OSG_WRITE_SUPPORTED)
{
}

CSVFileType::CSVFileType(const CSVFileType &obj) : Inherited(obj)
{
}

CSVFileType::~CSVFileType(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE

