
// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"
#include <sstream>
#include "OSGBaseFunctions.h"
#include "OSGTransform.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGMatrix.h"
// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGSimpleStatisticsForeground.h"
#include "OSGGeometry.h"

// The general scene file loading handler
#include "OSGSceneFileHandler.h"

// Input
#include "OSGWindowUtils.h"

// UserInterface Headers
#include "OSGUIForeground.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"

// 03TextDomArea Headers
#include "OSGLayers.h"
#include "OSGButton.h"
#include "OSGLineBorder.h"
#include "OSGFlowLayout.h"
#include "OSGUIFont.h"
#include "OSGScrollPanel.h"
#include "OSGTextDomArea.h"
#include "OSGTextField.h"
#include "OSGAdvancedTextDomArea.h"
#include "OSGButton.h"
#include "OSGColorLayer.h"
#include "OSGLineBorder.h"
#include "OSGTextDomLayoutManager.h"
#include "OSGGlyphView.h"
#include "OSGSplitPanel.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGGridLayout.h"
#include "OSGUIRectangle.h"

#include "OSGPlainTableDOM.h"
#include "OSGCell.h"
#include "OSGTableFileHandler.h"
#include "OSGTableDomArea.h"
#include "OSGTableDomLayoutManager.h"
#include "OSGCellView.h"

#include <OSGMenu.h>
#include <OSGMenuItem.h>
#include <OSGMenuBar.h>

#include <OSGMaterialGroup.h>
#include <fstream>

#include "rapidxml.h"
#include "rapidxml_iterators.h"
#include "rapidxml_print.h"

#if !defined(NDEBUG)
#define BOOST_MULTI_INDEX_ENABLE_INVARIANT_CHECKING
#define BOOST_MULTI_INDEX_ENABLE_SAFE_MODE
#endif

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

#define MAXCUBESIZE 625.0

using boost::multi_index_container;
using namespace boost::multi_index;



// Activate the OpenSG namespace
OSG_USING_NAMESPACE



struct node
{
	UInt32 clusterID;
	std::string label;
	NodeRefPtr theNode;

	node(UInt32 clusterID_,std::string label_,NodeRefPtr theNode_):clusterID(clusterID_),label(label_),theNode(theNode_){}
	node(){}

	friend std::ostream& operator<<(std::ostream& os,const node& n)
	{
		os<<"\nCluster ID: "<<n.clusterID<<" Node label: "<<n.label<<std::endl;
		return os;
	}
};

/* tags for accessing the corresponding indices of employee_set */

struct clusterID{};
struct label{};
struct theNode{};


/* see Compiler specifics: Use of member_offset for info on
 * BOOST_MULTI_INDEX_MEMBER
 */

/* Define a multi_index_container of nodes with following indices:
 *   - a non-unique index sorted by node::clusterID,
 *   - a non-unique index sorted by node::label,
 *   - a unique index sorted by node::theNode.
 */

typedef multi_index_container<
  node,
  indexed_by<
    ordered_non_unique<
      tag<clusterID>,  BOOST_MULTI_INDEX_MEMBER(node,UInt32,clusterID)>,
    ordered_non_unique<
	tag<label>,BOOST_MULTI_INDEX_MEMBER(node,std::string,label)>,
    ordered_unique<
      tag<theNode>, BOOST_MULTI_INDEX_MEMBER(node,NodeRefPtr,theNode)> >
> node_set;


std::vector<node> get_by_clusterID(
 const node_set& s,
 UInt32 theID
)
{
	std::vector<node> result;
	typedef boost::multi_index::index<node_set,clusterID>::type id_sequence;
	const id_sequence& i= get<clusterID>(s);
	id_sequence::iterator itr = i.find(theID);
	for(; itr != i.end(); itr++)
	{
		if(itr->clusterID != theID) break;
		//std::cout<<"\nCluster ID: "<<itr->clusterID<<" Node label: "<<itr->label<<std::endl;
		result.push_back(*itr);
	}
	return result;
}


node get_by_theNode(
 const node_set& s,
 NodeRefPtr theNodePtr
)
{
	typedef boost::multi_index::index<node_set,theNode>::type node_sequence;
    const node_sequence& i= get<theNode>(s);
	node_sequence::iterator itr = i.find(theNodePtr);
	if(itr != i.end())
	{
		//std::cout<<"\nCluster ID: "<<itr->clusterID<<" Node label: "<<itr->label<<std::endl;
		return *itr;
	}
	node result;
	return result;
}

std::vector<node> get_by_label(
 const node_set& s,
 std::string thelabel
)
{
	std::vector<node> result;
	typedef boost::multi_index::index<node_set,label>::type label_sequence;
    const label_sequence& i= get<label>(s);

	label_sequence::iterator itr = i.find(thelabel);

	for(; itr != i.end(); itr++)
	{
		if(itr->label != thelabel) break;
		//std::cout<<"\nCluster ID: "<<itr->clusterID<<" Node label: "<<itr->label<<std::endl;
		result.push_back(*itr);
	}

	return result;
}

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

std::map< Int32,Pnt3f > cubePoints;
float cubeSize = 25.f;
enum cameraManipulation {FROM,AT,BOTH};
enum modes {THE3DBARS,PEARSON_DEGREESORT,PEARSON_CORRELATIONSORT,PEARSON_UNSORTED};
static int theMode = THE3DBARS;
node_set nodeDetailsTable;
NodeRefPtr allTranNode;
static Int32 biggestCluster = 0;
static Int32 biggestClusterNoOfNodes = 0;
static Int32 smallestCluster = 99999;
static Int32 smallestClusterNoOfNodes = 99999;
static std::string highestDegree = "Highest Degree";
static Int32 highestDegreeValue = 0;
static std::string leastDegree = "Least Degree";
static Int32 leastDegreeValue = 99999;

std::vector<NodeRefPtr> highlightedNodes;
ViewportRefPtr TutorialViewport;
ChunkMaterialRefPtr GreenBackgroundMaterial,YellowBackgroundMaterial;
UIFontRefPtr _Font;
AdvancedTextDomAreaRefPtr detailsTextDOMArea;
InternalWindowRefPtr NotepadInternalWindow;
static std::string datasetPath="";
static bool isVisualized = false;
bool NotepadVisible;
AdvancedTextDomAreaRefPtr theNotepad;
TableDomAreaRefPtr TheTableDomArea;
ScrollPanelRefPtr TableAreaScrollPanel;
InternalWindowRefPtr StatisticsInternalWindow;

ChunkMaterialRefPtr createGreenMaterial(void);
ChunkMaterialRefPtr createYellowMaterial(void);

		// The Menubar Declarations
MenuBarRefPtr	_MainMenuBar;

// The Menus Declarations
MenuRefPtr		_ProjectMenu;
MenuRefPtr		_ViewMenu;
MenuRefPtr		_VisualizationMenu;
MenuRefPtr		_ExportMenu;
 
// The Project Menu Items Declarations
MenuItemRefPtr _NewProjectItem;
MenuItemRefPtr _LoadProjectItem;
MenuItemRefPtr _SaveProjectItem;
MenuItemRefPtr _LoadDataSetItem;
MenuItemRefPtr _ExitItem;
 
// The View Menu Items Declarations
MenuItemRefPtr _NotepadItem;

// The Visualization Menu Items Declarations
MenuItemRefPtr _3dBarsItem;
MenuRefPtr _PearsonViewMenuItem;
MenuItemRefPtr _DegreeSortItem;
MenuItemRefPtr _UnsortedItem;
MenuItemRefPtr _CorrelationSortItem;

// The Export Menu Items Declarations
MenuItemRefPtr _ExportSelectedItem;

void setNotepadWindowVisible(bool isVisible, UIDrawingSurface* const NotepadDrawingSurface, WindowEventProducer* const TutorialWindow);
bool isNotepadWindowVisible(void);
void xmlExportScene(WindowEventProducer* const TutorialWindow);
InternalWindowTransitPtr createStatisticsWindow(void);


void handleBasicAction(ActionEventDetails* const details,WindowEventProducer* const TutorialWindow,UIDrawingSurface* const TutorialDrawingSurface)
{

	if(details->getSource() == _ExitItem)
    {
		TutorialWindow->closeWindow();
	}
	else if(details->getSource() == _DegreeSortItem)
	{
		theMode = PEARSON_DEGREESORT;

		TutorialDrawingSurface->closeWindow(StatisticsInternalWindow);
		StatisticsInternalWindow = createStatisticsWindow();
		TutorialDrawingSurface->openWindow(StatisticsInternalWindow);
	
	}
	else if(details->getSource() == _UnsortedItem)
	{
		theMode = PEARSON_UNSORTED;
		std::cout<<"\nView Mode changed to PEARSON_UNSORTED\n";
	}
	else if(details->getSource() == _CorrelationSortItem)
	{
		theMode = PEARSON_CORRELATIONSORT;
		std::cout<<"\nView Mode changed to PEARSON_CORRELATIONSORT\n";
	}
	else if(details->getSource() == _3dBarsItem)
	{
		theMode = THE3DBARS;
		TutorialDrawingSurface->closeWindow(StatisticsInternalWindow);
		StatisticsInternalWindow = createStatisticsWindow();
		TutorialDrawingSurface->openWindow(StatisticsInternalWindow);
	}
	else if(details->getSource() == _NotepadItem)
	{
		if(isNotepadWindowVisible() == true)
		{
			setNotepadWindowVisible(false,TutorialDrawingSurface,TutorialWindow);
			_NotepadItem->setText("Show Notepad");
		}
		else
		{
			setNotepadWindowVisible(true,TutorialDrawingSurface,TutorialWindow);
			_NotepadItem->setText("Hide Notepad");
		}
	}
	else if(details->getSource() == _ExportSelectedItem)
	{
		xmlExportScene(TutorialWindow);
	}
	
}


void xmlExportScene(WindowEventProducer* const TutorialWindow)
{
	std::vector<WindowEventProducer::FileDialogFilter> Filters;
	Filters.push_back(WindowEventProducer::FileDialogFilter("xml files","xml"));
	Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

	BoostPath SavePath = TutorialWindow->saveFileDialog("Save Note Window",
														Filters,
														std::string("newFile.xml"),
														BoostPath(".."),
														true);
	if(SavePath.string() != "")
    {
		std::ofstream ofs(SavePath.string().c_str(), std::ios::binary);
		if(!ofs)
		{
			std::cout<<"Error : xmlExportScene() - Not able to open file"<<std::endl;
		}
		else
		{
			rapidxml::xml_document<> doc;

			// xml declaration
			rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
			decl->append_attribute(doc.allocate_attribute("version", "1.0"));
			decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
			doc.append_node(decl);

			// root node
			rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element,
														   "VizToolProject");
			root->append_attribute(doc.allocate_attribute("version", "1.0"));
			doc.append_node(root);

			for(UInt32 i=0;i<highlightedNodes.size();i++)
			{
				rapidxml::xml_node<>* thenode = doc.allocate_node(rapidxml::node_element,
														   "Node");
				node result = get_by_theNode(nodeDetailsTable,highlightedNodes[i]); 
				//std::cout<<"result.label : "<<result.label<<std::endl;
				char *labl = doc.allocate_string(result.label.c_str());
				thenode->append_attribute(doc.allocate_attribute("Label",labl));

				std::string clusterIDS;
				std::stringstream in;
				in.clear();
				in<<result.clusterID;
				in>>clusterIDS;
				char *cIDS = doc.allocate_string(clusterIDS.c_str());
				//std::cout<<"result.clusterID : "<<clusterIDS<<std::endl;
				thenode->append_attribute(doc.allocate_attribute("clusterID",cIDS));
				root->append_node(thenode);
			}

			//rapidxml::print(std::cout, doc, rapidxml::print_newline_attributes);
			//std::ostream& ostr(ofs);
			rapidxml::print(static_cast<std::ostream&>(ofs), doc, rapidxml::print_newline_attributes);
			ofs.close();
		}
	}
}

void mousePressed(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
	if(e->getButton() == MouseEventDetails::BUTTON1)
    {
		/*if(!(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CONTROL))
		{
			for(int i=0;i<highlightedNodes.size();i++)
			{
				dynamic_cast<Geometry*>(highlightedNodes[i]->getCore())->setMaterial(createGreenMaterial());
			}
			highlightedNodes.clear();
		}*/

        Line ViewRay;

        TutorialViewport->getCamera()->calcViewRay( ViewRay, e->getX(),e->getY(), *TutorialViewport);

        IntersectAction *CastRayAction = IntersectAction::create();

        CastRayAction->setLine( ViewRay );
        CastRayAction->apply( TutorialViewport->getRoot() );             

        if (CastRayAction->didHit())
        {
            NodeRefPtr theNode = CastRayAction->getHitObject();
			if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CONTROL)
			{
				//check if theNode is in highlightedNodes List
				std::vector<NodeRefPtr>::iterator highlightedNodesItr = std::find(highlightedNodes.begin(),highlightedNodes.end(),theNode);
				if( highlightedNodesItr != highlightedNodes.end())
				{
					dynamic_cast<Geometry*>(theNode->getCore())->setMaterial(createGreenMaterial());
					highlightedNodes.erase(highlightedNodesItr);	
				}
				else
				{
					dynamic_cast<Geometry*>(theNode->getCore())->setMaterial(createYellowMaterial());
					highlightedNodes.push_back(theNode);
				}
			}
			else
			{
				if(find(highlightedNodes.begin(),highlightedNodes.end(),theNode) ==  highlightedNodes.end())
				{
					dynamic_cast<Geometry*>(theNode->getCore())->setMaterial(createYellowMaterial());
					highlightedNodes.push_back(theNode);
				}
			}
			detailsTextDOMArea->clear();
			for(UInt32 i=0;i<highlightedNodes.size();i++)
			{
				node result = get_by_theNode(nodeDetailsTable,highlightedNodes[i]); 
				std::stringstream in;
				in<<result.clusterID;
				std::string ins;
				in>>ins;
				detailsTextDOMArea->write("\r\n");
				detailsTextDOMArea->write("Cluster: " + ins +"\r\n");
				detailsTextDOMArea->write("Label: " + result.label+"\r\n");
				detailsTextDOMArea->write("_________________\r\n");
			}
	    }
    }
	if(e->getButton() == MouseEventDetails::BUTTON2)
    {
		detailsTextDOMArea->clear();
		for(UInt32 i=0;i<highlightedNodes.size();i++)
		{
			dynamic_cast<Geometry*>(highlightedNodes[i]->getCore())->setMaterial(createGreenMaterial());
		}
		highlightedNodes.clear();
	}
}

void mouseReleased(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
}

void mouseMoved(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
}

void mouseDragged(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
}

void transformBeacon(SimpleSceneManager *mgr, Int32 x, Int32 y, Int32 z,Int32 cameraManipulation);



bool isNotepadWindowVisible(void)
{
	return NotepadVisible;
}

void handleSaveButtonAction(ActionEventDetails* const details,
                            WindowEventProducer* const TutorialWindow,
                            AdvancedTextDomArea* const theTextEditor)
{
	std::vector<WindowEventProducer::FileDialogFilter> Filters;
	Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

	BoostPath SavePath = TutorialWindow->saveFileDialog("Save Note Window",
														Filters,
														std::string("newFile.txt"),
														BoostPath(".."),
														true);
	if(SavePath.string() != "")
    {
	    theTextEditor->getTheTextDomArea()->saveFile(SavePath);
    }

}

void handleLoadNoteButtonAction(ActionEventDetails* const details,
                            WindowEventProducer* const TutorialWindow,
                            AdvancedTextDomArea* const theTextEditor)
{
	std::vector<WindowEventProducer::FileDialogFilter> Filters;
	Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));
	
	std::vector<BoostPath> FilesToOpen;
	FilesToOpen = TutorialWindow->openFileDialog("Open File Window",
												Filters,
												BoostPath(".."),
												false);

    if(FilesToOpen.size() > 0)
    {
	    theTextEditor->getTheTextDomArea()->loadFile(FilesToOpen[0]);
    }
}


void setNotepadWindowVisible(bool isVisible, UIDrawingSurface* const NotepadDrawingSurface, WindowEventProducer* const TutorialWindow)
{
	if(isVisible == true)
	{
		NotepadVisible = true;
		if(NotepadInternalWindow)
		{
			NotepadDrawingSurface->openWindow(NotepadInternalWindow);
		}
		else
		{
			theNotepad = AdvancedTextDomArea::create();
			theNotepad->setPreferredSize(Vec2f(200,200));
			theNotepad->setText("Type your observations here");

			BorderLayoutConstraintsRefPtr theNotepadConstraints = OSG::BorderLayoutConstraints::create();
			theNotepadConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

			ScrollPanelRefPtr theNotepadScrollPanel = ScrollPanel::create();
			theNotepadScrollPanel->setPreferredSize(Vec2f(200,200));
			theNotepadScrollPanel->setViewComponent(theNotepad);
			theNotepadScrollPanel->setConstraints(theNotepadConstraints);

		
			GridLayoutRefPtr LoadSaveButtonPanelLayout = OSG::GridLayout::create();
			LoadSaveButtonPanelLayout->setRows(1);
			LoadSaveButtonPanelLayout->setColumns(2);


			ButtonRefPtr SaveButton = Button::create();
			SaveButton->setMinSize(Vec2f(50, 25));
			SaveButton->setPreferredSize(Vec2f(100, 50));
			SaveButton->setToolTipText("Click to save the note");
			SaveButton->setText("Save Note");
			SaveButton->connectActionPerformed(boost::bind(handleSaveButtonAction, _1, TutorialWindow,theNotepad.get()));

			
			ButtonRefPtr LoadButton = Button::create();
			LoadButton->setMinSize(Vec2f(50, 25));
			LoadButton->setPreferredSize(Vec2f(100, 50));
			LoadButton->setToolTipText("Click to Load a note");
			LoadButton->setText("Load Note");
			LoadButton->connectActionPerformed(boost::bind(handleLoadNoteButtonAction, _1, TutorialWindow,theNotepad.get()));
		

			BorderLayoutConstraintsRefPtr LoadSaveButtonPanelConstraints = OSG::BorderLayoutConstraints::create();
			LoadSaveButtonPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
    
			PanelRefPtr LoadSaveButtonPanel = Panel::create();
			LoadSaveButtonPanel->setPreferredSize(Vec2f(200, 55));
			LoadSaveButtonPanel->pushToChildren(LoadButton);
			LoadSaveButtonPanel->pushToChildren(SaveButton);
			LoadSaveButtonPanel->setLayout(LoadSaveButtonPanelLayout);
			LoadSaveButtonPanel->setConstraints(LoadSaveButtonPanelConstraints);

			BorderLayoutRefPtr NotepadInternalWindowLayout = OSG::BorderLayout::create();
			ColorLayerRefPtr NotepadInternalWindowBackground = OSG::ColorLayer::create();
			NotepadInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

			NotepadInternalWindow = OSG::InternalWindow::create();
			NotepadInternalWindow->pushToChildren(theNotepadScrollPanel);
			NotepadInternalWindow->pushToChildren(LoadSaveButtonPanel);
			NotepadInternalWindow->setLayout(NotepadInternalWindowLayout);
			NotepadInternalWindow->setBackgrounds(NotepadInternalWindowBackground);
			NotepadInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
			NotepadInternalWindow->setScalingInDrawingSurface(Vec2f(0.3f,0.5f));
			//NotepadInternalWindow->setMenuBar(_MainMenuBar);	// to be commented
			NotepadInternalWindow->setDrawTitlebar(true);
			NotepadInternalWindow->setResizable(true);
			NotepadInternalWindow->setTitle("Notepad");


			NotepadDrawingSurface->openWindow(NotepadInternalWindow);

		}
	}
	else
	{
		NotepadVisible = false;
		NotepadDrawingSurface->closeWindow(NotepadInternalWindow);
	}
}

void keyTyped(KeyEventDetails* const details, SimpleSceneManager *mgr,SplitPanel* ExampleSplitPanel,WindowEventProducer* const TutorialWindow,UIDrawingSurface* const TutorialDrawingSurface)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
	if(details->getKey() == KeyEventDetails::KEY_1 && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
		ExampleSplitPanel->setDividerPosition(.2); // this is a percentage
		ExampleSplitPanel->setDividerSize(5);
		// ExampleSplitPanel->setExpandable(false);
		ExampleSplitPanel->setMaxDividerPosition(0.2);
		ExampleSplitPanel->setMinDividerPosition(0.2);
        
    }
	if(details->getKey() == KeyEventDetails::KEY_2 && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
		ExampleSplitPanel->setDividerPosition(.0); // this is a percentage
		ExampleSplitPanel->setDividerSize(0);
		// ExampleSplitPanel->setExpandable(false);
		ExampleSplitPanel->setMaxDividerPosition(0.0);
		ExampleSplitPanel->setMinDividerPosition(0.0);
 
    }
	if(details->getKey() == KeyEventDetails::KEY_W)
    {
		transformBeacon(mgr,0,0,5,FROM);
    }
	if(details->getKey() == KeyEventDetails::KEY_A)
    {
		transformBeacon(mgr,-5,0,0,FROM);
    }
	if(details->getKey() == KeyEventDetails::KEY_S)
    {
		transformBeacon(mgr,0,0,-5,FROM);
		
    }
	if(details->getKey() == KeyEventDetails::KEY_D)
    {
		transformBeacon(mgr,5,0,0,FROM);
    }
	if(details->getKey() == KeyEventDetails::KEY_Z)
    {
		transformBeacon(mgr,0,5,0,FROM);
    }
	if(details->getKey() == KeyEventDetails::KEY_X)
    {
		transformBeacon(mgr,0,-5,0,FROM);
    }
	if(details->getKey() == KeyEventDetails::KEY_T)
    {
		transformBeacon(mgr,0,0,5,BOTH);
    }
	if(details->getKey() == KeyEventDetails::KEY_F)
    {
		transformBeacon(mgr,-5,0,0,BOTH);
    }
	if(details->getKey() == KeyEventDetails::KEY_G)
    {
		transformBeacon(mgr,0,0,-5,BOTH);
		
    }
	if(details->getKey() == KeyEventDetails::KEY_H)
    {
		transformBeacon(mgr,5,0,0,BOTH);
    }
	if(details->getKey() == KeyEventDetails::KEY_V)
    {
		transformBeacon(mgr,0,5,0,BOTH);
    }
	if(details->getKey() == KeyEventDetails::KEY_B)
    {
		transformBeacon(mgr,0,-5,0,BOTH);
    }
	if(details->getKey() == KeyEventDetails::KEY_I)
    {
		transformBeacon(mgr,0,0,5,AT);
    }
	if(details->getKey() == KeyEventDetails::KEY_J)
    {
		transformBeacon(mgr,-5,0,0,AT);
    }
	if(details->getKey() == KeyEventDetails::KEY_K)
    {
		transformBeacon(mgr,0,0,-5,AT);
		
    }
	if(details->getKey() == KeyEventDetails::KEY_L)
    {
		transformBeacon(mgr,5,0,0,AT);
    }
	if(details->getKey() == KeyEventDetails::KEY_R && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
		mgr->showAll();
    }
	/*if(details->getKey() == KeyEventDetails::KEY_N && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
	{
		if(isNotepadWindowVisible() == true)
			setNotepadWindowVisible(false,TutorialDrawingSurface,TutorialWindow);
		else
			setNotepadWindowVisible(true,TutorialDrawingSurface,TutorialWindow);
	}*/
	//mgr->redraw();
	
}


void handleLoadDatasetButtonAction(ActionEventDetails* const details,
                            WindowEventProducer* const TutorialWindow/*,
                            TableDomArea* const TheTableDomArea*/)
{
	std::vector<WindowEventProducer::FileDialogFilter> Filters;
	Filters.push_back(WindowEventProducer::FileDialogFilter("CSV Files","csv"));


	std::vector<BoostPath> FilesToOpen;
	FilesToOpen = TutorialWindow->openFileDialog("Open File Window",
												Filters,
												BoostPath(".."),
												false);

    if(FilesToOpen.size() > 0)
    {
	    TheTableDomArea->loadFile(FilesToOpen[0]);
		datasetPath = FilesToOpen[0].string();
    }
}

ChunkMaterialRefPtr createGreenMaterial(void){

	if(GreenBackgroundMaterial)
		return GreenBackgroundMaterial;
	
    GreenBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkRefPtr GreenBackgroundMaterialChunk = MaterialChunk::create();
    GreenBackgroundMaterialChunk->setAmbient(Color4f(0.0,1.0,0.0,1.0));
    GreenBackgroundMaterialChunk->setDiffuse(Color4f(0.0,1.0,0.0,1.0));
    GreenBackgroundMaterialChunk->setSpecular(Color4f(0.0,1.0,0.0,1.0));
    GreenBackgroundMaterial->addChunk(GreenBackgroundMaterialChunk);

    return GreenBackgroundMaterial;

}

ChunkMaterialRefPtr createYellowMaterial(void){

	if(YellowBackgroundMaterial)
		return YellowBackgroundMaterial;

    YellowBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkRefPtr YellowBackgroundMaterialChunk = MaterialChunk::create();
    YellowBackgroundMaterialChunk->setAmbient(Color4f(1.0,1.0,0.0,1.0));
    YellowBackgroundMaterialChunk->setDiffuse(Color4f(1.0,1.0,0.0,1.0));
    YellowBackgroundMaterialChunk->setSpecular(Color4f(1.0,1.0,0.0,1.0));
    YellowBackgroundMaterial->addChunk(YellowBackgroundMaterialChunk);

    return YellowBackgroundMaterial;

}

NodeTransitPtr createFrontFaceOfCube(WindowEventProducer* const TutorialWindow)
{
	LabelRefPtr theLabel = Label::create();
	//theLabel->setMinSize(Vec2f(theLabel, theLabel));
    theLabel->setMaxSize(Vec2f(cubeSize, cubeSize/2));
	theLabel->setPreferredSize(Vec2f(cubeSize, cubeSize/3));
	theLabel->setText("Sample Label");
	theLabel->setFont(_Font);

    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(0.0,1.0,0.0,0.5));

	LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

	InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
	MainInternalWindow->pushToChildren(theLabel);
	MainInternalWindow->setLayout(MainInternalWindowLayout);
	MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.f,1.f));
	MainInternalWindow->setDrawTitlebar(false);
	MainInternalWindow->setResizable(false);

	GraphicsRefPtr TutorialGraphics = Graphics2D::create();

	UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        //TutorialDrawingSurface->setEventProducer(TutorialWindow);
  
	TutorialDrawingSurface->openWindow(MainInternalWindow);
	


	UIRectangleRefPtr ExampleUIRectangle = UIRectangle::create();
        ExampleUIRectangle->setPoint(Pnt3f(-cubeSize/2,-cubeSize/2,cubeSize/2));
        ExampleUIRectangle->setWidth(cubeSize);
        ExampleUIRectangle->setHeight(cubeSize);
        ExampleUIRectangle->setDrawingSurface(TutorialDrawingSurface);
    
    NodeRefPtr ExampleUIRectangleNode = OSG::Node::create();
        ExampleUIRectangleNode->setCore(ExampleUIRectangle);

	return NodeTransitPtr(ExampleUIRectangleNode);

}

NodeTransitPtr createCube(UInt32 side,WindowEventProducer* const TutorialWindow)
{
	// GeoPTypes will define the types of primitives to be used
    GeoUInt8PropertyRecPtr type = GeoUInt8Property::create();
    type->addValue(GL_QUADS);

	GeoUInt32PropertyRecPtr length = GeoUInt32Property::create();
    length->addValue(4 * 5);

	// GeoPnt3fProperty stores the positions of all vertices used in
    // this specific geometry core
    GeoPnt3fPropertyRecPtr pos = GeoPnt3fProperty::create();
	for(int i=0;i<8;i++)
		pos->addValue(cubePoints[i] * side/2.f);

	// GeoColor3fProperty stores all color values that will be used
    GeoColor3fPropertyRecPtr colors = GeoColor3fProperty::create();
    for (int x = 0; x < 8; x++)
        colors->addValue(Color3f(0,0,1));

	GeoVec3fPropertyRecPtr norms = GeoVec3fProperty::create();
        norms->addValue(Vec3f(-1,1,1));
        norms->addValue(Vec3f(1,1,1));
        norms->addValue(Vec3f(1,-1,1));
		norms->addValue(Vec3f(-1,-1,1));
		norms->addValue(Vec3f(-1,1,-1));
        norms->addValue(Vec3f(1,1,-1));
        norms->addValue(Vec3f(1,-1,-1));
		norms->addValue(Vec3f(-1,-1,-1));

	// indices points to all relevant data used by the 
    // provided primitives
    GeoUInt32PropertyRecPtr indices = GeoUInt32Property::create();
        
/*		indices->addValue(0);
		indices->addValue(3);
		indices->addValue(2);
		indices->addValue(1);
*/		
		indices->addValue(4);
		indices->addValue(7);
		indices->addValue(6);
		indices->addValue(5);

		indices->addValue(4);
		indices->addValue(7);
		indices->addValue(3);
		indices->addValue(0);

		indices->addValue(5);
		indices->addValue(6);
		indices->addValue(2);
		indices->addValue(1);

		indices->addValue(4);
		indices->addValue(0);
		indices->addValue(1);
		indices->addValue(5);

		indices->addValue(7);
		indices->addValue(3);
		indices->addValue(2);
		indices->addValue(6);

		GeometryRefPtr geo = Geometry::create();
    
		geo->setTypes    (type   );
		geo->setLengths  (length );
		geo->setIndices  (indices);
		geo->setPositions(pos    );
		geo->setNormals  (norms  );
		geo->setColors   (colors );
		geo->setMaterial(createGreenMaterial());

		NodeRecPtr root = Node::create();
		root->setCore(geo);

		NodeRefPtr frontFace = createFrontFaceOfCube(TutorialWindow);

		NodeRefPtr holder = Node::create();
		holder->setCore(MaterialGroup::create());
		holder->addChild(root);
		holder->addChild(frontFace);

		return NodeTransitPtr(holder);
}


void populatePoints()
{
	cubePoints[0] = Pnt3f(-1,1,1);
	cubePoints[1] = Pnt3f(1,1,1);
	cubePoints[2] = Pnt3f(1,-1,1);
	cubePoints[3] = Pnt3f(-1,-1,1);
	cubePoints[4] = Pnt3f(-1,1,-1);
	cubePoints[5] = Pnt3f(1,1,-1);
	cubePoints[6] = Pnt3f(1,-1,-1);
	cubePoints[7] = Pnt3f(-1,-1,-1);
}



void create3DScene(/*TableDomArea* const TheTableDomArea,*/
							SimpleSceneManager* mgr,
							Node* scene,
							WindowEventProducer* const TutorialWindow)
{
	if(TheTableDomArea && TheTableDomArea->getTableDOMModel() && TheTableDomArea->getTableDOMModel()->getRootCell())
	{
		if(theMode == THE3DBARS)
		{
			CellRefPtr rootCell = TheTableDomArea->getTableDOMModel()->getRootCell();
			Int32 rows = rootCell->getMaximumRow();
			Int32 cols = rootCell->getMaximumColumn();

			cubeSize = MAXCUBESIZE/(rows * cols * 1.f);
			Matrix mat;
			mat.setTranslate(-1* cubeSize/2.f, -1* rows * cubeSize/2.f ,-1* cubeSize/2.f);
			TransformRefPtr allTranCore = Transform::create();
			allTranCore->setMatrix(mat);
			allTranNode = Node::create();
			allTranNode->setCore(allTranCore);

			for(Int32 i=0;i<rows;i++)
			{
				Matrix mat;
				mat.setTranslate(0.0,((rows - 1 - i) * cubeSize) /*+ ((rows - 1 - i) * 3.0)*/,0.0);
				TransformRefPtr theRowTranCore = Transform::create();
				theRowTranCore->setMatrix(mat);
				NodeRefPtr theRowTranNode = Node::create();
				theRowTranNode->setCore(theRowTranCore);


				int actual_colms = 0;
				for(UInt32 j=0;j<cols;j++)
				{	
					CellRefPtr theRow = rootCell->getCell(i);
					if(theRow)
					{
						CellRefPtr theCell = theRow->getCell(j);
						if(theCell)
						{
							std::string theString = boost::any_cast<std::string>(theCell->getValue());
							if(theString != "") actual_colms++;
						}
					}
				}
				if(actual_colms >= biggestClusterNoOfNodes) 
				{
					biggestClusterNoOfNodes = actual_colms;
					biggestCluster = i;
				}
				if(actual_colms <= smallestClusterNoOfNodes) 
				{
					smallestClusterNoOfNodes = actual_colms;
					smallestCluster = i;
				}
				if(actual_colms==0)actual_colms++;
				Real32 column_width = cubeSize/actual_colms *1.f;

				int count = 0;
				for(UInt32 j=0;j<cols;j++)
				{
					CellRefPtr theRow = rootCell->getCell(i);
					if(theRow)
					{
						CellRefPtr theCell = theRow->getCell(j);
						if(theCell)
						{
							std::string theString = boost::any_cast<std::string>(theCell->getValue());
							
							if(theString != "")
							{
								NodeRefPtr theCuboid = /*createCube(cubeSize,TutorialWindow);*/	makeBox(cubeSize/*column_width*/, cubeSize, cubeSize, 1, 1, 1);
								dynamic_cast<Geometry*>(theCuboid->getCore())->setMaterial(createGreenMaterial());
								//tableToNodesMap[i][theString] = theCuboid;
								nodeDetailsTable.insert(node(i,theString,theCuboid));

								Matrix mat;
								mat.setTranslate((count * cubeSize/*column_width*/) /*+ (count * 3.0)*/,0.0,0.0);
								TransformRefPtr theCuboidTranCore = Transform::create();
								theCuboidTranCore->setMatrix(mat);
								NodeRefPtr theCuboidTranNode = Node::create();
								theCuboidTranNode->setCore(theCuboidTranCore);

								theCuboidTranNode->addChild(theCuboid);

								theRowTranNode->addChild(theCuboidTranNode);
								count++;
							}
						}
					}
				}
				allTranNode->addChild(theRowTranNode);
			}
			scene->addChild(allTranNode);
		}
		else if(theMode == PEARSON_CORRELATIONSORT)
		{
			
		}
		else if(theMode == PEARSON_DEGREESORT)
		{
			
		}
		else if(theMode == PEARSON_UNSORTED)
		{
			
		}
		
	}
}


void transformBeacon(SimpleSceneManager *m_SSMgr,Int32 x, Int32 y, Int32 z,Int32 cameraManipulation)
{
	Navigator *nav = m_SSMgr->getNavigator();
	
	if(cameraManipulation == FROM)
	{
		Pnt3f from = nav->getFrom();
		nav->setFrom(Pnt3f(from.x()+x,from.y()+y,from.z()+z));
	}
	if(cameraManipulation == AT)
	{
		Pnt3f at = nav->getAt();
		nav->setAt(Pnt3f(at.x()+x,at.y()+y,at.z()+z));
	}
	if(cameraManipulation == BOTH)
	{
		Pnt3f from = nav->getFrom();
		nav->setFrom(Pnt3f(from.x()+x,from.y()+y,from.z()+z));
		Pnt3f at = nav->getAt();
		nav->setAt(Pnt3f(at.x()+x,at.y()+y,at.z()+z));
	}
	nav->updateCameraTransformation();
    
}


void removingPreviouScene(Node* scene)
{
	if(allTranNode)
	{
		scene->subChild(allTranNode);
		allTranNode = NULL;
	}
}

void handleVisualizeButtonAction(ActionEventDetails* const details,
                            WindowEventProducer* const TutorialWindow,
                            /*TableDomArea* const TheTableDomArea,*/
							SimpleSceneManager* mgr,
							Node* scene)
{
	isVisualized = true;
	nodeDetailsTable.clear();
	biggestCluster = 0;
	biggestClusterNoOfNodes = 0;
	smallestCluster = 99999;
	smallestClusterNoOfNodes = 99999;

	removingPreviouScene(scene);
	create3DScene(/*TheTableDomArea,*/mgr,scene,TutorialWindow);

	mgr->showAll();
}





void handleviewLargestClusterButtonAction(ActionEventDetails* const details)
{
	for(int i=0;i<highlightedNodes.size();i++)
	{
		dynamic_cast<Geometry*>(highlightedNodes[i]->getCore())->setMaterial(createGreenMaterial());
	}
	highlightedNodes.clear();
	char biggestClusterC[255];
	sprintf(biggestClusterC,"%d",biggestCluster);
	std::string biggestClusterS= biggestClusterC;
	char biggestClusterNoOfNodesC[255];
	sprintf(biggestClusterNoOfNodesC,"%d",biggestClusterNoOfNodes);
	std::string biggestClusterNoOfNodesS= biggestClusterNoOfNodesC;
	detailsTextDOMArea->clear();
	detailsTextDOMArea->write("Largest Cluster:" + biggestClusterS + "\r\n");
	detailsTextDOMArea->write("Number of nodes:" + biggestClusterNoOfNodesS + "\r\n");
	detailsTextDOMArea->write("The Nodes:\r\n");

	std::vector<node> result = get_by_clusterID(nodeDetailsTable,biggestCluster);
	for(UInt32 i=0;i<result.size();i++)
	{
		detailsTextDOMArea->write(result[i].label+"\r\n");
		// TODO : need to deal with the case when materialGroup is the core
		dynamic_cast<Geometry*>(result[i].theNode->getCore())->setMaterial(createYellowMaterial());
		highlightedNodes.push_back(result[i].theNode);
	}
	
}

void handleviewSmallestClusterButtonAction(ActionEventDetails* const details)
{
	for(int i=0;i<highlightedNodes.size();i++)
	{
		dynamic_cast<Geometry*>(highlightedNodes[i]->getCore())->setMaterial(createGreenMaterial());
	}
	highlightedNodes.clear();
	char smallestClusterC[255];
	sprintf(smallestClusterC,"%d",smallestCluster);
	std::string smallestClusterS= smallestClusterC;
	char smallestClusterNoOfNodesC[255];
	sprintf(smallestClusterNoOfNodesC,"%d",smallestClusterNoOfNodes);
	std::string smallestClusterNoOfNodesS= smallestClusterNoOfNodesC;
	detailsTextDOMArea->clear();
	detailsTextDOMArea->write("Smallest Cluster:" + smallestClusterS + "\r\n");
	detailsTextDOMArea->write("Number of nodes:" + smallestClusterNoOfNodesS + "\r\n");

	detailsTextDOMArea->write("The Nodes:\r\n");

	
	std::vector<node> result = get_by_clusterID(nodeDetailsTable,smallestCluster);
	for(UInt32 i=0;i<result.size();i++)
	{
		detailsTextDOMArea->write(result[i].label+"\r\n");
		dynamic_cast<Geometry*>(result[i].theNode->getCore())->setMaterial(createYellowMaterial());
		highlightedNodes.push_back(result[i].theNode);
	}

}

void handleclusterIDGoButtonButtonAction(ActionEventDetails* const details,TableDomArea *TheTableDomArea,TextField* clusterIDField)
{
	for(int i=0;i<highlightedNodes.size();i++)
	{
		dynamic_cast<Geometry*>(highlightedNodes[i]->getCore())->setMaterial(createGreenMaterial());
	}
	highlightedNodes.clear();

	CellRefPtr rootCell = TheTableDomArea->getTableDOMModel()->getRootCell();
	UInt32 maxRow = rootCell->getMaximumRow();

	std::istringstream is(clusterIDField->getText());
	Int32 givenRow;
	is>>givenRow;

	if(givenRow >= maxRow) 
	{
		detailsTextDOMArea->clear();
		detailsTextDOMArea->write("Invalid Cluster ID\r\n");
	}
	else
	{
		char theClusterC[255];
		sprintf(theClusterC,"%d",givenRow);
		std::string theClusterS= theClusterC;

		//std::map<std::string,NodeRefPtr> theRow = tableToNodesMap[givenRow];

		std::vector<node> result = get_by_clusterID(nodeDetailsTable,givenRow);
	

		char theClusterNoOfNodesC[255];
		sprintf(theClusterNoOfNodesC,"%d",result.size());
		std::string theClusterNoOfNodesS= theClusterNoOfNodesC;
		detailsTextDOMArea->clear();
		detailsTextDOMArea->write("the Cluster:" + theClusterS + "\r\n");
		detailsTextDOMArea->write("Number of nodes:" + theClusterNoOfNodesS + "\r\n");

		detailsTextDOMArea->write("The Nodes:\r\n");

		for(UInt32 i=0;i<result.size();i++)
		{
			detailsTextDOMArea->write(result[i].label+"\r\n");
			dynamic_cast<Geometry*>(result[i].theNode->getCore())->setMaterial(createYellowMaterial());
			highlightedNodes.push_back(result[i].theNode);
		}

	}

}

void handleLoadProject(ActionEventDetails* const details,WindowEventProducer* const TutorialWindow,/* TableDomArea* TheTableDomArea,*/SimpleSceneManager* mgr, Node* scene,UIDrawingSurface* const TutorialDrawingSurface )
{
	std::vector<WindowEventProducer::FileDialogFilter> Filters;
	Filters.push_back(WindowEventProducer::FileDialogFilter("Viztool Project Files","viz"));


	std::vector<BoostPath> FilesToOpen;
	FilesToOpen = TutorialWindow->openFileDialog("Open File Window",
												Filters,
												BoostPath(".."),
												false);

    if(FilesToOpen.size() > 0)
    {
	    //TheTableDomArea->loadFile(FilesToOpen[0]);
		std::ifstream ifs(FilesToOpen[0].string().c_str());
		std::string xmlString = "";
		std::string line;
		while(getline(ifs,line))xmlString += line + "\r\n";
		std::vector<char> xml_copy(xmlString.begin(), xmlString.end());
		xml_copy.push_back('\0');

		rapidxml::xml_document<> doc;
		doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&xml_copy[0]);
		rapidxml::xml_node<>* cur_node = doc.first_node("VizToolProject");

		// setting the Mode
		std::string modeString = cur_node->first_node("Mode")->first_attribute("ID")->value();
		UInt32 modeVal;
		std::stringstream is;
		is<<modeString;
		is>>modeVal;
		theMode = modeVal;

		// setting the IsVisualized
		std::string isVisualizedString = cur_node->first_node("Visualization")->first_attribute("Value")->value();
		UInt32 isVisualizedVal;
		is<<isVisualizedString;
		is>>isVisualizedVal;
		isVisualized = isVisualizedVal;

		// setting the notepad
		std::string notepadString = cur_node->first_node("Notepad")->first_attribute("Visible")->value();
		UInt32 notepadVal;
		is.clear();
		is<<notepadString;
		is>>notepadVal;

		if(notepadVal)
		{
			setNotepadWindowVisible(true,TutorialDrawingSurface,TutorialWindow);
			_NotepadItem->setText("Hide Notepad");
		}
		else
		{
			setNotepadWindowVisible(false,TutorialDrawingSurface,TutorialWindow);
			_NotepadItem->setText("Show Notepad");
		}

		// populating the table
		std::string datapathString = cur_node->first_node("Dataset")->first_attribute("Path")->value();
		BoostPath theDataPath(datapathString);
		TheTableDomArea->loadFile(theDataPath);

		datasetPath = theDataPath.string();

		// visualizing the data
		if(isVisualized)
			handleVisualizeButtonAction(NULL,TutorialWindow/*,TheTableDomArea*/,mgr,scene);

		// setting the camera beacon matrix
		std::string matrixString = cur_node->first_node("Camera")->first_attribute("Matrix")->value();
		Matrix m;
		Real32 value;
		UInt32 i=0,j=0;
		
		boost::char_separator<char> sep(",");
		boost::tokenizer<boost::char_separator<char>> tokens(matrixString, sep);

		std::stringstream ss;

		BOOST_FOREACH(std::string t, tokens)
		{
			ss.clear();
			ss<<t;
			ss>>value;
			m[i][j] = value;
			j++;
			if(j==4)
			{
			  i++;
			  j=0;
			}
		}
		
		//dynamic_cast<Transform*>(mgr->getNavigator()->getViewport()->getCamera()->getBeacon()->getCore())->setMatrix(m);
		mgr->getNavigator()->set(m);
		mgr->getNavigator()->updateCameraTransformation();
		
		std::stringstream iss;
		UInt32 clusterID;
		std::string label;
		std::string clusterIDS;

		cur_node = cur_node->first_node("Node");

		detailsTextDOMArea->clear();

		do
		{
			if(!cur_node) 
			{
				//std::cout<<"No more nodes"<<std::endl;
				break;
			}
			label = cur_node->first_attribute("Label")->value();
			clusterIDS = cur_node->first_attribute("ClusterID")->value();
			
			iss.clear();
			iss<<clusterIDS;
			iss>>clusterID;

			// do some calculation for highlighting this node
			std::vector<node> result = get_by_label(nodeDetailsTable,label);

			if(result.size()<=0) 
			{
				detailsTextDOMArea->clear();
				detailsTextDOMArea->write("handleLoadProject Error: Node not found\r\n");
				break;
			}
			else
			{
				
				for(UInt32 i=0;i<result.size();i++)
				{
					if(clusterID == result[i].clusterID)
					{
						char theClusterC[255];
						sprintf(theClusterC,"%d",result[i].clusterID);
						std::string theClusterS= theClusterC;

						detailsTextDOMArea->write("\r\n");

						detailsTextDOMArea->write("the Cluster:" + theClusterS + "\r\n");

						dynamic_cast<Geometry*>(result[i].theNode->getCore())->setMaterial(createYellowMaterial());
						highlightedNodes.push_back(result[i].theNode);

						detailsTextDOMArea->write("_________________\r\n");
						break;
					}
				}
			}
			cur_node = cur_node->next_sibling("Node");
		}while(cur_node);
	}
}

void handleSaveProject(ActionEventDetails* const details,WindowEventProducer* const TutorialWindow, /*TableDomArea* TheTableDomArea,*/SimpleSceneManager* mgr)
{
	std::vector<WindowEventProducer::FileDialogFilter> Filters;
	Filters.push_back(WindowEventProducer::FileDialogFilter("VizTool project files","viz"));
	Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

	BoostPath SavePath = TutorialWindow->saveFileDialog("Save Note Window",
														Filters,
														std::string("newProject.viz"),
														BoostPath(".."),
														true);
	if(SavePath.string() != "")
    {
		std::ofstream ofs(SavePath.string().c_str(), std::ios::binary);
		if(!ofs)
		{
			std::cout<<"Error : handleSaveProject() - Not able to open file"<<std::endl;
		}
		else
		{
			rapidxml::xml_document<> doc;

			// xml declaration
			rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
			decl->append_attribute(doc.allocate_attribute("version", "1.0"));
			decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
			doc.append_node(decl);

			// root node
			rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element,
														   "VizToolProject");
			root->append_attribute(doc.allocate_attribute("version", "1.0"));
			doc.append_node(root);

			// node for mode 
			rapidxml::xml_node<>* theModeNode = doc.allocate_node(rapidxml::node_element,"Mode");
			std::string theModeS;
			std::stringstream in;
			in.clear();
			in<<theMode;
			in>>theModeS;
			char *mS = doc.allocate_string(theModeS.c_str());
			theModeNode->append_attribute(doc.allocate_attribute("ID",mS));
			root->append_node(theModeNode);

			// is data being visualized?
			rapidxml::xml_node<>* theIsVisualizedNode = doc.allocate_node(rapidxml::node_element,"Visualization");
			std::string theIsVisualizedNodeS;
			in.clear();
			in<<isVisualized;
			in>>theIsVisualizedNodeS;
			char *vnS = doc.allocate_string(theIsVisualizedNodeS.c_str());
			theIsVisualizedNode->append_attribute(doc.allocate_attribute("Value",vnS));
			root->append_node(theIsVisualizedNode);

			// camera transformation export
			Matrix cameraTransformation = dynamic_cast<Transform*>(mgr->getNavigator()->getViewport()->getCamera()->getBeacon()->getCore())->getMatrix();
			
			rapidxml::xml_node<>* theCameraTransNode = doc.allocate_node(rapidxml::node_element,"Camera");
			std::string xS;
			in.clear();
			in<<cameraTransformation[0][0]<<",";
			in<<cameraTransformation[0][1]<<",";
			in<<cameraTransformation[0][2]<<",";
			in<<cameraTransformation[0][3]<<",";
			in<<cameraTransformation[1][0]<<",";
			in<<cameraTransformation[1][1]<<",";
			in<<cameraTransformation[1][2]<<",";
			in<<cameraTransformation[1][3]<<",";
			in<<cameraTransformation[2][0]<<",";
			in<<cameraTransformation[2][1]<<",";
			in<<cameraTransformation[2][2]<<",";
			in<<cameraTransformation[2][3]<<",";
			in<<cameraTransformation[3][0]<<",";
			in<<cameraTransformation[3][1]<<",";
			in<<cameraTransformation[3][2]<<",";
			in<<cameraTransformation[3][3];
			in>>xS;
			char *xxS = doc.allocate_string(xS.c_str());
			theCameraTransNode->append_attribute(doc.allocate_attribute("Matrix",xxS));
			root->append_node(theCameraTransNode);
			
			// data table export 
			rapidxml::xml_node<>* theDatasetNode = doc.allocate_node(rapidxml::node_element,"Dataset");
			char *dsS = doc.allocate_string(datasetPath.c_str());
			theDatasetNode->append_attribute(doc.allocate_attribute("Path",dsS));
			root->append_node(theDatasetNode);

			
			rapidxml::xml_node<>* notepadVisibleNode = doc.allocate_node(rapidxml::node_element,"Notepad");
			std::string visibleS;
			in.clear();
			in<<NotepadVisible;
			in>>visibleS;
			char *vS = doc.allocate_string(visibleS.c_str());
			notepadVisibleNode->append_attribute(doc.allocate_attribute("Visible",vS));
			root->append_node(notepadVisibleNode);


			for(UInt32 i=0;i<highlightedNodes.size();i++)
			{
				rapidxml::xml_node<>* thenode = doc.allocate_node(rapidxml::node_element,
														   "Node");
				node result = get_by_theNode(nodeDetailsTable,highlightedNodes[i]); 
				char *labl = doc.allocate_string(result.label.c_str());
				thenode->append_attribute(doc.allocate_attribute("Label",labl));

				std::string clusterIDS;
				std::stringstream in;
				in.clear();
				in<<result.clusterID;
				in>>clusterIDS;
				char *cIDS = doc.allocate_string(clusterIDS.c_str());
				thenode->append_attribute(doc.allocate_attribute("ClusterID",cIDS));
				root->append_node(thenode);
			}

			//rapidxml::print(std::cout, doc, rapidxml::print_newline_attributes);
			//std::ostream& ostr(ofs);
			rapidxml::print(static_cast<std::ostream&>(ofs), doc, rapidxml::print_newline_attributes);
			ofs.close();
		}
	}
}

void handlenodeIDGoButtonButtonAction(ActionEventDetails* const details,TextField* nodeIDField)
{
	for(int i=0;i<highlightedNodes.size();i++)
	{
		dynamic_cast<Geometry*>(highlightedNodes[i]->getCore())->setMaterial(createGreenMaterial());
	}
	highlightedNodes.clear();

	std::string nodeString = nodeIDField->getText();

	Int32 givenRow = -1;

	std::vector<node> result = get_by_label(nodeDetailsTable,nodeString);

	if(result.size()<=0) 
	{
		detailsTextDOMArea->clear();
		detailsTextDOMArea->write("Error: Node not found\r\n");
	}
	else
	{
		detailsTextDOMArea->clear();
		for(UInt32 i=0;i<result.size();i++)
		{
			char theClusterC[255];
			sprintf(theClusterC,"%d",result[i].clusterID);
			std::string theClusterS= theClusterC;
			detailsTextDOMArea->write("the Cluster:" + theClusterS + "\r\n");

			dynamic_cast<Geometry*>(result[i].theNode->getCore())->setMaterial(createYellowMaterial());
			highlightedNodes.push_back(result[i].theNode);

			detailsTextDOMArea->write("_________________\r\n");
		}
	}

}


InternalWindowTransitPtr createStatisticsWindow(void)
{

	InternalWindowRefPtr StatisticsInternalWindow = OSG::InternalWindow::create();
	StatisticsInternalWindow->setAlignmentInDrawingSurface(Vec2f(1.0f,0.0f));
	StatisticsInternalWindow->setScalingInDrawingSurface(Vec2f(0.2f,1.f));
	StatisticsInternalWindow->setDrawTitlebar(true);
	StatisticsInternalWindow->setResizable(true);
	StatisticsInternalWindow->setTitle("Statistics");
		

	if(theMode == THE3DBARS)
	{
		/*LabelRefPtr statLabel = Label::create();
		statLabel->setMinSize(Vec2f(50, 25));
		statLabel->setMaxSize(Vec2f(200, 100));
		statLabel->setPreferredSize(Vec2f(150, 20));
		statLabel->setAlignment(Vec2f(0.0f,0.5f));
		statLabel->setText("Statistics");*/

		//biggestCluster;
		//biggestClusterNoOfNodes;

		LabelRefPtr biggestClusterLabel = Label::create();
		biggestClusterLabel->setMinSize(Vec2f(50, 25));
		biggestClusterLabel->setMaxSize(Vec2f(200, 100));
		biggestClusterLabel->setPreferredSize(Vec2f(150, 20));
		biggestClusterLabel->setAlignment(Vec2f(0.0f,0.5f));
		std::string biggestClusterS;
		std::stringstream iss(biggestCluster);
		iss>>biggestClusterS;
		biggestClusterLabel->setText("Biggest Cluster: " + biggestClusterS);

		LabelRefPtr biggestClusterNoOfNodesLabel = Label::create();
		biggestClusterNoOfNodesLabel->setMinSize(Vec2f(50, 25));
		biggestClusterNoOfNodesLabel->setMaxSize(Vec2f(200, 100));
		biggestClusterNoOfNodesLabel->setPreferredSize(Vec2f(150, 20));
		biggestClusterNoOfNodesLabel->setAlignment(Vec2f(0.5f,0.5f));
		std::string biggestClusterNoOfNodesS;
		iss.clear();
		iss<<(biggestClusterNoOfNodes);
		iss>>biggestClusterNoOfNodesS;
		biggestClusterNoOfNodesLabel->setText("Number of nodes: " + biggestClusterNoOfNodesS);

		LabelRefPtr smallestClusterLabel = Label::create();
		smallestClusterLabel->setMinSize(Vec2f(50, 25));
		smallestClusterLabel->setMaxSize(Vec2f(200, 100));
		smallestClusterLabel->setPreferredSize(Vec2f(150, 20));
		smallestClusterLabel->setAlignment(Vec2f(0.0f,0.5f));
		std::string smallestClusterS;
		iss.clear();
		iss<<(smallestCluster);
		iss>>smallestClusterS;
		smallestClusterLabel->setText("Smallest Cluster: " + smallestClusterS);

		LabelRefPtr smallestClusterNoOfNodesLabel = Label::create();
		smallestClusterNoOfNodesLabel->setMinSize(Vec2f(50, 25));
		smallestClusterNoOfNodesLabel->setMaxSize(Vec2f(200, 100));
		smallestClusterNoOfNodesLabel->setPreferredSize(Vec2f(150, 20));
		smallestClusterNoOfNodesLabel->setAlignment(Vec2f(0.5f,0.5f));
		std::string smallestClusterNoOfNodesS;
		iss.clear();
		iss<<(smallestClusterNoOfNodes);
		iss>>smallestClusterNoOfNodesS;
		smallestClusterNoOfNodesLabel->setText("Number of nodes: " + smallestClusterNoOfNodesS);

/*		ButtonRefPtr viewLargestClusterButton = Button::create();
		viewLargestClusterButton->setMinSize(Vec2f(50, 25));
		viewLargestClusterButton->setMaxSize(Vec2f(200, 100));
		viewLargestClusterButton->setPreferredSize(Vec2f(150, 20));
		viewLargestClusterButton->setToolTipText("Click to view the largest cluster");
		viewLargestClusterButton->setText("View Largest Cluster");
		viewLargestClusterButton->connectActionPerformed(boost::bind(handleviewLargestClusterButtonAction, _1));

		ButtonRefPtr viewSmallestClusterButton = Button::create();
		viewSmallestClusterButton->setMinSize(Vec2f(50, 25));
		viewSmallestClusterButton->setMaxSize(Vec2f(200, 100));
		viewSmallestClusterButton->setPreferredSize(Vec2f(150, 20));
		viewSmallestClusterButton->setToolTipText("Click to view the smallest cluster");
		viewSmallestClusterButton->setText("View Smallest Cluster");
		viewSmallestClusterButton->connectActionPerformed(boost::bind(handleviewSmallestClusterButtonAction, _1));
*/
		LabelRefPtr clusterIDLabel = Label::create();
		clusterIDLabel->setMinSize(Vec2f(50, 25));
		clusterIDLabel->setMaxSize(Vec2f(200, 100));
		clusterIDLabel->setPreferredSize(Vec2f(150, 20));
		clusterIDLabel->setText("cluster ID:");

		TextFieldRefPtr clusterIDTextField = OSG::TextField::create();
		clusterIDTextField->setText("");
		clusterIDTextField->setEmptyDescText("Enter Cluster ID here");
		clusterIDTextField->setPreferredSize(Vec2f(150.0f,20.0f));

		ButtonRefPtr clusterIDGoButton = Button::create();
		clusterIDGoButton->setMinSize(Vec2f(50, 25));
		clusterIDGoButton->setMaxSize(Vec2f(200, 100));
		clusterIDGoButton->setPreferredSize(Vec2f(150, 20));
		clusterIDGoButton->setText("Go >>");
		clusterIDGoButton->connectActionPerformed(boost::bind(handleclusterIDGoButtonButtonAction, _1,TheTableDomArea,clusterIDTextField.get()));

		LabelRefPtr nodeIDLabel = Label::create();
		nodeIDLabel->setMinSize(Vec2f(50, 25));
		nodeIDLabel->setMaxSize(Vec2f(200, 100));
		nodeIDLabel->setPreferredSize(Vec2f(150, 20));
		nodeIDLabel->setText("node string:");

		TextFieldRefPtr nodeIDTextField = OSG::TextField::create();
		nodeIDTextField->setText("");
		nodeIDTextField->setEmptyDescText("Enter node string here");
		nodeIDTextField->setPreferredSize(Vec2f(150.0f,20.0f));

		ButtonRefPtr nodeIDGoButton = Button::create();
		nodeIDGoButton->setMinSize(Vec2f(50, 25));
		nodeIDGoButton->setMaxSize(Vec2f(200, 100));
		nodeIDGoButton->setPreferredSize(Vec2f(150, 20));
		nodeIDGoButton->setText("Go >>");
		nodeIDGoButton->connectActionPerformed(boost::bind(handlenodeIDGoButtonButtonAction, _1,nodeIDTextField.get()));

		LabelRefPtr detailsLabel = Label::create();
		detailsLabel->setMinSize(Vec2f(50, 25));
		detailsLabel->setMaxSize(Vec2f(200, 100));
		detailsLabel->setPreferredSize(Vec2f(150, 20));
		detailsLabel->setText("Details:");

		detailsTextDOMArea = AdvancedTextDomArea::create();
		detailsTextDOMArea->setPreferredSize(Vec2f(200,200));
		detailsTextDOMArea->setEditable(false);
		detailsTextDOMArea->setText("Details");

		ScrollPanelRefPtr detailsTextDOMAreaScrollPanel = ScrollPanel::create();
		detailsTextDOMAreaScrollPanel->setPreferredSize(Vec2f(150,150));
		detailsTextDOMAreaScrollPanel->setViewComponent(detailsTextDOMArea);

		
		FlowLayoutRefPtr PanelFlowLayout2 = OSG::FlowLayout::create();
		PanelFlowLayout2->setHorizontalGap(3);
		PanelFlowLayout2->setVerticalGap(3);

		
		//StatisticsPanel->pushToChildren(statLabel);
		//StatisticsPanel->pushToChildren(viewLargestClusterButton);
		//StatisticsPanel->pushToChildren(viewSmallestClusterButton);
		StatisticsInternalWindow->pushToChildren(clusterIDLabel);
		StatisticsInternalWindow->pushToChildren(clusterIDTextField);
		StatisticsInternalWindow->pushToChildren(clusterIDGoButton);
		StatisticsInternalWindow->pushToChildren(nodeIDLabel);
		StatisticsInternalWindow->pushToChildren(nodeIDTextField);
		StatisticsInternalWindow->pushToChildren(nodeIDGoButton);
		StatisticsInternalWindow->pushToChildren(detailsLabel);
		StatisticsInternalWindow->pushToChildren(detailsTextDOMAreaScrollPanel);
		StatisticsInternalWindow->setLayout(PanelFlowLayout2);
		
	}
	else if(theMode == PEARSON_CORRELATIONSORT)
	{

	}
	else if(theMode == PEARSON_UNSORTED)
	{

	}
	else if(theMode == PEARSON_DEGREESORT)
	{
		// Details : 
		// Highest Degree node - The value - 2 labels 
		// Least Degree node - The value - 2 labels
		// given a node - display details - label + textarea + button + TextDomArea
		// all in a grid layout

		LabelRefPtr highestDegreeLabel = Label::create();
		highestDegreeLabel->setMinSize(Vec2f(50, 25));
		highestDegreeLabel->setMaxSize(Vec2f(250, 100));
		highestDegreeLabel->setPreferredSize(Vec2f(200, 20));
		highestDegreeLabel->setAlignment(Vec2f(0.5f,0.0f));
		std::string highestDegreeS;
		std::stringstream iss(highestDegree);
		iss>>highestDegreeS;
		highestDegreeLabel->setText("Highest Degree Node: " + highestDegreeS);

		LabelRefPtr highestDegreeValueLabel = Label::create();
		highestDegreeValueLabel->setMinSize(Vec2f(50, 25));
		highestDegreeValueLabel->setMaxSize(Vec2f(200, 100));
		highestDegreeValueLabel->setPreferredSize(Vec2f(150, 20));
		highestDegreeValueLabel->setAlignment(Vec2f(0.5f,0.0f));
		std::string highestDegreeValueS;
		iss.clear();
		iss<<(highestDegreeValue);
		iss>>highestDegreeValueS;
		highestDegreeValueLabel->setText("Value: " + highestDegreeValueS);

		LabelRefPtr leastDegreeLabel = Label::create();
		leastDegreeLabel->setMinSize(Vec2f(50, 25));
		leastDegreeLabel->setMaxSize(Vec2f(250, 100));
		leastDegreeLabel->setPreferredSize(Vec2f(200, 20));
		leastDegreeLabel->setAlignment(Vec2f(0.5f,0.0f));
		std::string leastDegreeS;
		iss.clear();
		iss<<(leastDegree);
		iss>>leastDegreeS;
		leastDegreeLabel->setText("Least Degree Node: " + leastDegreeS);

		LabelRefPtr leastDegreeValueLabel = Label::create();
		leastDegreeValueLabel->setMinSize(Vec2f(50, 25));
		leastDegreeValueLabel->setMaxSize(Vec2f(200, 100));
		leastDegreeValueLabel->setPreferredSize(Vec2f(150, 20));
		leastDegreeValueLabel->setAlignment(Vec2f(0.5f,0.0f));
		std::string leastDegreeValueS;
		iss.clear();
		iss<<(leastDegreeValue);
		iss>>leastDegreeValueS;
		leastDegreeValueLabel->setText("Value: " + leastDegreeValueS);

		LabelRefPtr nodeIDLabel = Label::create();
		nodeIDLabel->setMinSize(Vec2f(50, 25));
		nodeIDLabel->setMaxSize(Vec2f(200, 100));
		nodeIDLabel->setPreferredSize(Vec2f(150, 20));
		nodeIDLabel->setText("node string:");

		TextFieldRefPtr nodeIDTextField = OSG::TextField::create();
		nodeIDTextField->setText("");
		nodeIDTextField->setEmptyDescText("Enter node string here");
		nodeIDTextField->setPreferredSize(Vec2f(150.0f,20.0f));

		ButtonRefPtr nodeIDGoButton = Button::create();
		nodeIDGoButton->setMinSize(Vec2f(50, 25));
		nodeIDGoButton->setMaxSize(Vec2f(200, 100));
		nodeIDGoButton->setPreferredSize(Vec2f(150, 20));
		nodeIDGoButton->setText("Go >>");
		//nodeIDGoButton->connectActionPerformed(boost::bind(handlenodeIDGoButtonButtonAction, _1,nodeIDTextField.get()));

		LabelRefPtr detailsLabel = Label::create();
		detailsLabel->setMinSize(Vec2f(50, 25));
		detailsLabel->setMaxSize(Vec2f(200, 100));
		detailsLabel->setPreferredSize(Vec2f(150, 20));
		detailsLabel->setText("Details:");

		detailsTextDOMArea = AdvancedTextDomArea::create();
		detailsTextDOMArea->setPreferredSize(Vec2f(200,200));
		detailsTextDOMArea->setEditable(false);
		detailsTextDOMArea->setText("Details");

		ScrollPanelRefPtr detailsTextDOMAreaScrollPanel = ScrollPanel::create();
		detailsTextDOMAreaScrollPanel->setPreferredSize(Vec2f(150,150));
		detailsTextDOMAreaScrollPanel->setViewComponent(detailsTextDOMArea);

		//GridLayoutRefPtr TheGridLayout = OSG::GridLayout::create();
		//TheGridLayout->setRows(9);
		//TheGridLayout->setColumns(1);

		FlowLayoutRefPtr PanelFlowLayout2 = OSG::FlowLayout::create();
		PanelFlowLayout2->setHorizontalGap(3);
		PanelFlowLayout2->setVerticalGap(3);

		StatisticsInternalWindow->pushToChildren(highestDegreeLabel);
		StatisticsInternalWindow->pushToChildren(highestDegreeValueLabel);
		StatisticsInternalWindow->pushToChildren(leastDegreeLabel);
		StatisticsInternalWindow->pushToChildren(leastDegreeValueLabel);
		StatisticsInternalWindow->pushToChildren(nodeIDLabel);
		StatisticsInternalWindow->pushToChildren(nodeIDTextField);
		StatisticsInternalWindow->pushToChildren(nodeIDGoButton);
		StatisticsInternalWindow->pushToChildren(detailsLabel);
		StatisticsInternalWindow->pushToChildren(detailsTextDOMAreaScrollPanel);
		//StatisticsInternalWindow->setPreferredSize(Vec2f(200.f,600.f));
		StatisticsInternalWindow->setLayout(/*TheGridLayout*/PanelFlowLayout2);

	}
	

	return InternalWindowTransitPtr(StatisticsInternalWindow);
}

void handleNewProject(ActionEventDetails* const details,WindowEventProducer* const TutorialWindow,/* TableDomArea* TheTableDomArea,*/SimpleSceneManager* mgr, Node* scene,UIDrawingSurface* const TutorialDrawingSurface)
{
	theMode = THE3DBARS;

	setNotepadWindowVisible(false,TutorialDrawingSurface,TutorialWindow);
	_NotepadItem->setText("Show Notepad");

	nodeDetailsTable.clear();
	highlightedNodes.clear();
	biggestCluster = 0;
	biggestClusterNoOfNodes = 0;
	smallestCluster = 99999;
	smallestClusterNoOfNodes = 99999;
	removingPreviouScene(scene);

	isVisualized = false;

	detailsTextDOMArea->clear();

	if(theNotepad)
		theNotepad->setText("Type your observations here");

	TheTableDomArea = TableDomArea::create();
	TheTableDomArea->setPreferredSize(Vec2f(300,200));
	TableAreaScrollPanel->setViewComponent(TheTableDomArea);

	datasetPath = "";

}

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

		// Create the Drawing Surface
        UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();

        // Create the SimpleSceneManager helper
		SimpleSceneManager sceneManager;
        
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));
		TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));


		_Font = UIFont::create();
		_Font->setFamily("SANS");
		_Font->setGap(1);
		_Font->setGlyphPixelSize(12);
		_Font->setSize(5);
		_Font->setTextureWidth(0);
		_Font->setStyle(TextFace::STYLE_PLAIN);

//		createMenuBar();

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);


		//NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
		populatePoints();
//		X = 0,Y = 0,Z = 40;
		NodeRefPtr scene;
        // Make Main Scene Node and add the Torus
        scene = Node::create();
        scene->setCore(Group::create());
        //scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRefPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

			    
	
		TheTableDomArea = TableDomArea::create();
		TheTableDomArea->setPreferredSize(Vec2f(300,200));
	    //TheTableDomArea->loadFile(BoostPath("D:\\Work_Office_RA\\OpenSGToolBox\\Examples\\Tutorial\\TableDom\\Data\\SampleOutput.csv"));
		//datasetPath = "D:\\Work_Office_RA\\OpenSGToolBox\\Examples\\Tutorial\\TableDom\\Data\\SampleOutput.csv";
		TableAreaScrollPanel = ScrollPanel::create();
        TableAreaScrollPanel->setPreferredSize(Vec2f(200,200));
	    TableAreaScrollPanel->setViewComponent(TheTableDomArea);


	    ButtonRefPtr LoadButton = Button::create();
	    LoadButton->setMinSize(Vec2f(50, 25));
        LoadButton->setMaxSize(Vec2f(200, 100));
        LoadButton->setPreferredSize(Vec2f(200, 50));
        LoadButton->setToolTipText("Click to open a file browser window");
        LoadButton->setText("Load Dataset");
		LoadButton->connectActionPerformed(boost::bind(handleLoadDatasetButtonAction, _1, TutorialWindow.get()/*, TheTableDomArea.get()*/));


		LabelRefPtr tableLabel = Label::create();
		tableLabel->setMinSize(Vec2f(50, 25));
        tableLabel->setMaxSize(Vec2f(200, 100));
		tableLabel->setPreferredSize(Vec2f(100, 50));
		tableLabel->setText("Dataset");

		ButtonRefPtr VisualizeButton = Button::create();
	    VisualizeButton->setMinSize(Vec2f(50, 25));
        VisualizeButton->setMaxSize(Vec2f(200, 100));
        VisualizeButton->setPreferredSize(Vec2f(100, 50));
        VisualizeButton->setToolTipText("Click to visualize the data");
        VisualizeButton->setText("Visualize Data");
		VisualizeButton->connectActionPerformed(boost::bind(handleVisualizeButtonAction, _1, TutorialWindow.get(), /*TheTableDomArea.get(),*/&sceneManager,scene.get()));
	
		FlowLayoutRefPtr PanelFlowLayout = OSG::FlowLayout::create();
		PanelFlowLayout->setHorizontalGap(3);
		PanelFlowLayout->setVerticalGap(3);

		PanelRefPtr ExampleSplitPanelPanel1 = OSG::Panel::create();
		ExampleSplitPanelPanel1->pushToChildren(LoadButton);
		ExampleSplitPanelPanel1->pushToChildren(tableLabel);
		ExampleSplitPanelPanel1->pushToChildren(TableAreaScrollPanel);
		ExampleSplitPanelPanel1->pushToChildren(VisualizeButton);
		ExampleSplitPanelPanel1->setLayout(PanelFlowLayout);


		//PanelRefPtr StatisticsPanel = createStatisticsPanel(TheTableDomArea.get());

/*	    BorderLayoutConstraintsRefPtr ExampleSplitPanel2Constraints = OSG::BorderLayoutConstraints::create();
		ExampleSplitPanel2Constraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

		SplitPanelRefPtr ExampleSplitPanel2 = OSG::SplitPanel::create();
		ExampleSplitPanel2->setConstraints(ExampleSplitPanel2Constraints);
		ExampleSplitPanel2->setMaxComponent(StatisticsPanel);
		ExampleSplitPanel2->setDividerPosition(.80); // this is a percentage
		ExampleSplitPanel2->setDividerSize(5);
		ExampleSplitPanel2->setExpandable(false);
		//ExampleSplitPanel2->setMaxDividerPosition(0.80);
		//ExampleSplitPanel2->setMinDividerPosition(0.80);

*/


    
		BorderLayoutRefPtr MainInternalWindowLayout = OSG::BorderLayout::create();
		BorderLayoutConstraintsRefPtr ExampleSplitPanelConstraints = OSG::BorderLayoutConstraints::create();
		ExampleSplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);


		SplitPanelRefPtr ExampleSplitPanel = OSG::SplitPanel::create();

		ExampleSplitPanel->setConstraints(ExampleSplitPanelConstraints);
		ExampleSplitPanel->setMinComponent(ExampleSplitPanelPanel1);
		//ExampleSplitPanel->setMaxComponent(ExampleSplitPanel2);
		
		ExampleSplitPanel->setDividerPosition(.20); // this is a percentage
		ExampleSplitPanel->setDividerSize(5);
		ExampleSplitPanel->setExpandable(false);
		//ExampleSplitPanel->setMaxDividerPosition(0.20);
		//ExampleSplitPanel->setMinDividerPosition(0.20);

	
	// The Project Menu Items Definitions
	_NewProjectItem = MenuItem::create();				
    _NewProjectItem->setText("New Project");
	_NewProjectItem->setAcceleratorKey(KeyEventDetails::KEY_N);
    _NewProjectItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _NewProjectItem->setMnemonicKey(KeyEventDetails::KEY_N);
	_NewProjectItem->connectActionPerformed(boost::bind(handleNewProject, _1,TutorialWindow.get(),&sceneManager,scene.get(),TutorialDrawingSurface.get()));

	_LoadProjectItem = MenuItem::create();				
    _LoadProjectItem->setText("Load Project");
	_LoadProjectItem->setAcceleratorKey(KeyEventDetails::KEY_O);
    _LoadProjectItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _LoadProjectItem->setMnemonicKey(KeyEventDetails::KEY_O);
	_LoadProjectItem->connectActionPerformed(boost::bind(handleLoadProject, _1,TutorialWindow.get(),/*TheTableDomArea.get(),*/&sceneManager,scene.get(),TutorialDrawingSurface.get()));

	_SaveProjectItem = MenuItem::create();				
    _SaveProjectItem->setText("Save Project");
	_SaveProjectItem->setAcceleratorKey(KeyEventDetails::KEY_S);
    _SaveProjectItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _SaveProjectItem->setMnemonicKey(KeyEventDetails::KEY_S);
	_SaveProjectItem->connectActionPerformed(boost::bind(handleSaveProject, _1,TutorialWindow.get(),/*TheTableDomArea.get(),*/&sceneManager));

	_LoadDataSetItem = MenuItem::create();				
    _LoadDataSetItem->setText("Load Dataset");
	_LoadDataSetItem->setAcceleratorKey(KeyEventDetails::KEY_L);
    _LoadDataSetItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _LoadDataSetItem->setMnemonicKey(KeyEventDetails::KEY_L);
	_LoadDataSetItem->connectActionPerformed(boost::bind(handleLoadDatasetButtonAction, _1, TutorialWindow.get()/*, TheTableDomArea.get()*/));

	_ExitItem = MenuItem::create();				
    _ExitItem->setText("Exit");
    _ExitItem->setAcceleratorKey(KeyEventDetails::KEY_X);
    _ExitItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _ExitItem->setMnemonicKey(KeyEventDetails::KEY_Q);
	_ExitItem->connectActionPerformed(boost::bind(handleBasicAction, _1,TutorialWindow.get(),TutorialDrawingSurface.get()));
	
	// The View Menu Items Definitions
	_NotepadItem = MenuItem::create();				
    _NotepadItem->setText("Show Notepad");
    _NotepadItem->setAcceleratorKey(KeyEventDetails::KEY_T);
    _NotepadItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _NotepadItem->setMnemonicKey(KeyEventDetails::KEY_T);
	_NotepadItem->connectActionPerformed(boost::bind(handleBasicAction, _1,TutorialWindow.get(),TutorialDrawingSurface.get()));

	// The Visualization Menu Items Definitions
	_3dBarsItem = MenuItem::create();				
    _3dBarsItem->setText("3D Bars");
	_3dBarsItem->connectActionPerformed(boost::bind(handleBasicAction, _1,TutorialWindow.get(),TutorialDrawingSurface.get()));
	
	_DegreeSortItem = MenuItem::create();				
    _DegreeSortItem->setText("Degree sort");
	_DegreeSortItem->connectActionPerformed(boost::bind(handleBasicAction, _1,TutorialWindow.get(),TutorialDrawingSurface.get()));

	_UnsortedItem = MenuItem::create();				
    _UnsortedItem->setText("Unsorted");
	_UnsortedItem->connectActionPerformed(boost::bind(handleBasicAction, _1,TutorialWindow.get(),TutorialDrawingSurface.get()));

	_CorrelationSortItem = MenuItem::create();				
    _CorrelationSortItem->setText("Correlation sort");
    _CorrelationSortItem->connectActionPerformed(boost::bind(handleBasicAction, _1,TutorialWindow.get(),TutorialDrawingSurface.get()));

	_PearsonViewMenuItem = Menu::create();				
    _PearsonViewMenuItem->setText("Pearson Visualization");
	_PearsonViewMenuItem->addItem(_DegreeSortItem);
	_PearsonViewMenuItem->addItem(_UnsortedItem);
	_PearsonViewMenuItem->addItem(_CorrelationSortItem);

	// The Export Menu Items Definitions
	_ExportSelectedItem = MenuItem::create();				
    _ExportSelectedItem->setText("Export Selected Nodes");
    _ExportSelectedItem->setAcceleratorKey(KeyEventDetails::KEY_E);
    _ExportSelectedItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _ExportSelectedItem->setMnemonicKey(KeyEventDetails::KEY_E);
	_ExportSelectedItem->connectActionPerformed(boost::bind(handleBasicAction, _1,TutorialWindow.get(),TutorialDrawingSurface.get()));



	// The Project Menu Definition
    _ProjectMenu = Menu::create();
	_ProjectMenu->setText("Project");
	_ProjectMenu->setMnemonicKey(KeyEventDetails::KEY_F);
	// Addition of the Project Menu Items 
	_ProjectMenu->addItem(_NewProjectItem);
	_ProjectMenu->addItem(_LoadProjectItem);
	_ProjectMenu->addItem(_SaveProjectItem);
	_ProjectMenu->addSeparator();
    _ProjectMenu->addItem(_LoadDataSetItem);
    _ProjectMenu->addSeparator();
	_ProjectMenu->addItem(_ExitItem);
    
	// The View Menu Definition
    _ViewMenu = Menu::create();
	_ViewMenu->setText("View");
    _ViewMenu->setMnemonicKey(KeyEventDetails::KEY_I);
	// Addition of the View Menu Items 
    _ViewMenu->addItem(_NotepadItem);
    
    // The Visualization Menu Definition
    _VisualizationMenu = Menu::create();
	_VisualizationMenu->setText("Visualization");
    _VisualizationMenu->setMnemonicKey(KeyEventDetails::KEY_Z);
	// Addition of the Visualization Menu Items 
    _VisualizationMenu->addItem(_3dBarsItem);
	_VisualizationMenu->addItem(_PearsonViewMenuItem);
    
	// The Export Menu Definition
    _ExportMenu = Menu::create();
	_ExportMenu->setText("Export");
    _ExportMenu->setMnemonicKey(KeyEventDetails::KEY_X);
	// Addition of the Export Menu Items 
    _ExportMenu->addItem(_ExportSelectedItem);

	
	// The Main Menu Bar Definitions
	_MainMenuBar = MenuBar::create();
	
    _MainMenuBar->addMenu(_ProjectMenu);
	_MainMenuBar->addMenu(_ViewMenu);
	_MainMenuBar->addMenu(_VisualizationMenu);
	_MainMenuBar->addMenu(_ExportMenu);



		// Create The Main InternalWindow
		// Create Background to be used with the Main InternalWindow
		ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
		MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

		InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
		MainInternalWindow->pushToChildren(ExampleSplitPanel);
		MainInternalWindow->setLayout(MainInternalWindowLayout);
		MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
		MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
		MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.f,1.f));
		MainInternalWindow->setMenuBar(_MainMenuBar);
		MainInternalWindow->setDrawTitlebar(false);
		MainInternalWindow->setResizable(false);
		MainInternalWindow->setAllInsets(5);

		StatisticsInternalWindow = createStatisticsWindow();
	
        
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
    	
	    TutorialDrawingSurface->openWindow(MainInternalWindow);
		TutorialDrawingSurface->openWindow(StatisticsInternalWindow);

		//setNotepadWindowVisible(true,TutorialDrawingSurface.get(),TutorialWindow.get());

        // Create the UI Foreground Object
        UIForegroundRefPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
		
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);
    		

        // Show the whole Scene
        sceneManager.showAll();


    	
        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize());
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "VizTool");
        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1,&sceneManager,ExampleSplitPanel.get(),TutorialWindow.get(),TutorialDrawingSurface.get()));

        commitChanges();

		

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}

// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}
