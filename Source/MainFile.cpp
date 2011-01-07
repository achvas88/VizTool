
// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"
#include <sstream>
#include "OSGBaseFunctions.h"
#include "OSGTransform.h"
#include "OSGTypedGeoVectorProperty.h"
#include "OSGTypedGeoIntegralProperty.h"

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
		std::cout<<"\nCluster ID: "<<itr->clusterID<<" Node label: "<<itr->label<<std::endl;
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
		std::cout<<"\nCluster ID: "<<itr->clusterID<<" Node label: "<<itr->label<<std::endl;
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
		std::cout<<"\nCluster ID: "<<itr->clusterID<<" Node label: "<<itr->label<<std::endl;
		result.push_back(*itr);
	}

	return result;
}

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

std::map< Int32,Pnt3f > cubePoints;
static float cubeSize = 25.f;
enum cameraManipulation {FROM,AT,BOTH};
node_set nodeDetailsTable;
NodeRefPtr allTranNode;
static Int32 biggestCluster = 0;
static Int32 biggestClusterNoOfNodes = 0;
static Int32 smallestCluster = 99999;
static Int32 smallestClusterNoOfNodes = 99999;
std::vector<NodeRefPtr> highlightedNodes;
ViewportRefPtr TutorialViewport;
ChunkMaterialRefPtr GreenBackgroundMaterial,YellowBackgroundMaterial;
UIFontRefPtr _Font;
AdvancedTextDomAreaRefPtr detailsTextDOMArea;
InternalWindowRefPtr NotepadInternalWindow;

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
MenuItemRefPtr _PearsonViewItem;

// The Export Menu Items Declarations
MenuItemRefPtr _ExportSelectedItem;

bool NotepadVisible;

ChunkMaterialRefPtr createGreenMaterial(void);
ChunkMaterialRefPtr createYellowMaterial(void);


void handleBasicAction(ActionEventDetails* const details)
{
    if(details->getSource() == _ExitItem)
    {
		dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
	}
}

void createMenuBar(void)
{
	
	// The Project Menu Items Definitions
	_NewProjectItem = MenuItem::create();				
	_NewProjectItem->setFont(_Font);
    _NewProjectItem->setText("New Project");
	_NewProjectItem->setAcceleratorKey(KeyEventDetails::KEY_N);
    _NewProjectItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _NewProjectItem->setMnemonicKey(KeyEventDetails::KEY_N);
	_NewProjectItem->connectActionPerformed(boost::bind(handleBasicAction, _1));

	_LoadProjectItem = MenuItem::create();				
	_LoadProjectItem->setFont(_Font);
    _LoadProjectItem->setText("Load Dataset");
	_LoadProjectItem->setAcceleratorKey(KeyEventDetails::KEY_L);
    _LoadProjectItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _LoadProjectItem->setMnemonicKey(KeyEventDetails::KEY_L);
	_LoadProjectItem->connectActionPerformed(boost::bind(handleBasicAction, _1));

	_SaveProjectItem = MenuItem::create();				
	_SaveProjectItem->setFont(_Font);
    _SaveProjectItem->setText("Load Dataset");
	_SaveProjectItem->setAcceleratorKey(KeyEventDetails::KEY_S);
    _SaveProjectItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _SaveProjectItem->setMnemonicKey(KeyEventDetails::KEY_S);
	_SaveProjectItem->connectActionPerformed(boost::bind(handleBasicAction, _1));

	_LoadDataSetItem = MenuItem::create();				
	_LoadDataSetItem->setFont(_Font);
    _LoadDataSetItem->setText("Load Dataset");
	_LoadDataSetItem->setAcceleratorKey(KeyEventDetails::KEY_L);
    _LoadDataSetItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _LoadDataSetItem->setMnemonicKey(KeyEventDetails::KEY_L);
	_LoadDataSetItem->connectActionPerformed(boost::bind(handleBasicAction, _1));

	_ExitItem = MenuItem::create();				
    _ExitItem->setText("Exit");
	_ExitItem->setFont(_Font);
    _ExitItem->setAcceleratorKey(KeyEventDetails::KEY_Q);
    _ExitItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _ExitItem->setMnemonicKey(KeyEventDetails::KEY_Q);
	_ExitItem->connectActionPerformed(boost::bind(handleBasicAction, _1));
	
	// The View Menu Items Definitions
	_NotepadItem = MenuItem::create();				
    _NotepadItem->setText("View Notepad");
	_NotepadItem->setFont(_Font);
    _NotepadItem->setAcceleratorKey(KeyEventDetails::KEY_N);
    _NotepadItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _NotepadItem->setMnemonicKey(KeyEventDetails::KEY_N);
	_NotepadItem->connectActionPerformed(boost::bind(handleBasicAction, _1));

	// The Visualization Menu Items Definitions
	_3dBarsItem = MenuItem::create();				
    _3dBarsItem->setText("3D Bars");
	_3dBarsItem->setFont(_Font);
    _3dBarsItem->setAcceleratorKey(KeyEventDetails::KEY_B);
    _3dBarsItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _3dBarsItem->setMnemonicKey(KeyEventDetails::KEY_B);
	_3dBarsItem->connectActionPerformed(boost::bind(handleBasicAction, _1));
	
	_PearsonViewItem = MenuItem::create();				
    _PearsonViewItem->setText("Pearson Visualization");
	_PearsonViewItem->setFont(_Font);
    _PearsonViewItem->setAcceleratorKey(KeyEventDetails::KEY_P);
    _PearsonViewItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _PearsonViewItem->setMnemonicKey(KeyEventDetails::KEY_P);
	_PearsonViewItem->connectActionPerformed(boost::bind(handleBasicAction, _1));

	// The Export Menu Items Definitions
	_ExportSelectedItem = MenuItem::create();				
    _ExportSelectedItem->setText("Export Selected Nodes");
	_ExportSelectedItem->setFont(_Font);
    _ExportSelectedItem->setAcceleratorKey(KeyEventDetails::KEY_N);
    _ExportSelectedItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
    _ExportSelectedItem->setMnemonicKey(KeyEventDetails::KEY_N);
	_ExportSelectedItem->connectActionPerformed(boost::bind(handleBasicAction, _1));

	// The Project Menu Definition
    _ProjectMenu = Menu::create();
	_ProjectMenu->setFont(_Font);
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
	_ViewMenu->setFont(_Font);
    _ViewMenu->setMnemonicKey(KeyEventDetails::KEY_I);
	// Addition of the View Menu Items 
    _ViewMenu->addItem(_NotepadItem);
    
    // The Visualization Menu Definition
    _VisualizationMenu = Menu::create();
	_VisualizationMenu->setText("Visualization");
	_VisualizationMenu->setFont(_Font);
    _VisualizationMenu->setMnemonicKey(KeyEventDetails::KEY_Z);
	// Addition of the Visualization Menu Items 
    _VisualizationMenu->addItem(_3dBarsItem);
	_VisualizationMenu->addItem(_PearsonViewItem);
    
	// The Export Menu Definition
    _ExportMenu = Menu::create();
	_ExportMenu->setText("Export");
	_ExportMenu->setFont(_Font);
    _ExportMenu->setMnemonicKey(KeyEventDetails::KEY_X);
	// Addition of the Export Menu Items 
    _ExportMenu->addItem(_ExportSelectedItem);
    

	// The Main Menu Bar Definitions
	_MainMenuBar = MenuBar::create();
    _MainMenuBar->addMenu(_ProjectMenu);
	_MainMenuBar->addMenu(_ViewMenu);
	_MainMenuBar->addMenu(_VisualizationMenu);
	_MainMenuBar->addMenu(_ExportMenu);
	
}
void xmlExportScene()
{
    rapidxml::xml_document<> doc;

    // xml declaration
    rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
    decl->append_attribute(doc.allocate_attribute("version", "1.0"));
    decl->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
    doc.append_node(decl);

	// root node
    rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element,
                                                   "VizTool Scene");
    root->append_attribute(doc.allocate_attribute("version", "1.0"));
    doc.append_node(root);

	rapidxml::print(std::cout, doc, rapidxml::print_newline_attributes);

}

void mousePressed(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
	if(e->getButton() == MouseEventDetails::BUTTON1)
    {
		if(!(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CONTROL))
		{
			for(int i=0;i<highlightedNodes.size();i++)
			{
				dynamic_cast<Geometry*>(highlightedNodes[i]->getCore())->setMaterial(createGreenMaterial());
			}
			highlightedNodes.clear();
		}

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
					node result = get_by_theNode(nodeDetailsTable,theNode); 
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
			else
			{
				dynamic_cast<Geometry*>(theNode->getCore())->setMaterial(createYellowMaterial());
				highlightedNodes.push_back(theNode);
				node result = get_by_theNode(nodeDetailsTable,theNode); 
				detailsTextDOMArea->clear();
				std::stringstream in;
				in<<result.clusterID;
				std::string ins;
				in>>ins;
				detailsTextDOMArea->write("Cluster: " + ins +"\r\n");
				detailsTextDOMArea->write("Label: " + result.label+"\r\n");
				detailsTextDOMArea->write("_________________\r\n");
			}
	    }
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
			AdvancedTextDomAreaRefPtr theNotepad = AdvancedTextDomArea::create();
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
	if(details->getKey() == KeyEventDetails::KEY_N && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
	{
		if(isNotepadWindowVisible() == true)
			setNotepadWindowVisible(false,TutorialDrawingSurface,TutorialWindow);
		else
			setNotepadWindowVisible(true,TutorialDrawingSurface,TutorialWindow);
	}
	//mgr->redraw();
	
}


void handleLoadButtonAction(ActionEventDetails* const details,
                            WindowEventProducer* const TutorialWindow,
                            TableDomArea* const ExampleTableDomArea)
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
	    ExampleTableDomArea->loadFile(FilesToOpen[0]);
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



void create3DScene(TableDomArea* const ExampleTableDomArea,
							SimpleSceneManager* mgr,
							Node* scene,
							WindowEventProducer* const TutorialWindow)
{
	CellRefPtr rootCell = ExampleTableDomArea->getTableDOMModel()->getRootCell();
	Int32 rows = rootCell->getMaximumRow();
	Int32 cols = rootCell->getMaximumColumn();

	Matrix mat;
	mat.setTranslate(-1* cubeSize/2.f, -1* rows * cubeSize/2.f ,-1* cubeSize/2.f);
	TransformRefPtr allTranCore = Transform::create();
	allTranCore->setMatrix(mat);
    allTranNode = Node::create();
	allTranNode->setCore(allTranCore);

	for(Int32 i=0;i<rows;i++)
	{
		Matrix mat;
		mat.setTranslate(0.0,((rows - 1 - i) * cubeSize) + ((rows - 1 - i) * 3.0),0.0);
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
						NodeRefPtr theCuboid = createCube(cubeSize,TutorialWindow);//	makeBox(cubeSize/*column_width*/, cubeSize, cubeSize, 1, 1, 1);
						//dynamic_cast<Geometry*>(theCuboid->getCore())->setMaterial(createGreenMaterial());
						//tableToNodesMap[i][theString] = theCuboid;
						nodeDetailsTable.insert(node(i,theString,theCuboid));

						Matrix mat;
						mat.setTranslate((count * cubeSize/*column_width*/) + (count * 3.0),0.0,0.0);
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
                            TableDomArea* const ExampleTableDomArea,
							SimpleSceneManager* mgr,
							Node* scene)
{
	
	nodeDetailsTable.clear();
	biggestCluster = 0;
	biggestClusterNoOfNodes = 0;
	smallestCluster = 99999;
	smallestClusterNoOfNodes = 99999;

	removingPreviouScene(scene);
	create3DScene(ExampleTableDomArea,mgr,scene,TutorialWindow);

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

void handleclusterIDGoButtonButtonAction(ActionEventDetails* const details,TableDomArea *ExampleTableDomArea,TextField* clusterIDField)
{
	for(int i=0;i<highlightedNodes.size();i++)
	{
		dynamic_cast<Geometry*>(highlightedNodes[i]->getCore())->setMaterial(createGreenMaterial());
	}
	highlightedNodes.clear();

	CellRefPtr rootCell = ExampleTableDomArea->getTableDOMModel()->getRootCell();
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


PanelTransitPtr createExampleSplitPanelPanel2(TableDomArea* ExampleTableDomArea)
{

	LabelRefPtr statLabel = Label::create();
	statLabel->setMinSize(Vec2f(50, 25));
    statLabel->setMaxSize(Vec2f(200, 100));
	statLabel->setPreferredSize(Vec2f(150, 20));
	statLabel->setAlignment(Vec2f(0.0f,0.5f));
	statLabel->setText("Statistics");

	ButtonRefPtr viewLargestClusterButton = Button::create();
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
	clusterIDGoButton->connectActionPerformed(boost::bind(handleclusterIDGoButtonButtonAction, _1,ExampleTableDomArea,clusterIDTextField.get()));

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

	PanelRefPtr ExampleSplitPanelPanel2 = OSG::Panel::create();
	ExampleSplitPanelPanel2->pushToChildren(statLabel);
	ExampleSplitPanelPanel2->pushToChildren(viewLargestClusterButton);
	ExampleSplitPanelPanel2->pushToChildren(viewSmallestClusterButton);
	ExampleSplitPanelPanel2->pushToChildren(clusterIDLabel);
	ExampleSplitPanelPanel2->pushToChildren(clusterIDTextField);
	ExampleSplitPanelPanel2->pushToChildren(clusterIDGoButton);
	ExampleSplitPanelPanel2->pushToChildren(nodeIDLabel);
	ExampleSplitPanelPanel2->pushToChildren(nodeIDTextField);
	ExampleSplitPanelPanel2->pushToChildren(nodeIDGoButton);
	ExampleSplitPanelPanel2->pushToChildren(detailsLabel);
	ExampleSplitPanelPanel2->pushToChildren(detailsTextDOMAreaScrollPanel);
	ExampleSplitPanelPanel2->setLayout(PanelFlowLayout2);

	return PanelTransitPtr(ExampleSplitPanelPanel2);
}

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

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

		createMenuBar();

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

			    
	
		TableDomAreaRefPtr ExampleTableDomArea = TableDomArea::create();
		ExampleTableDomArea->setPreferredSize(Vec2f(300,200));
	    ExampleTableDomArea->loadFile(BoostPath("D:\\Work_Office_RA\\OpenSGToolBox\\Examples\\Tutorial\\TableDom\\Data\\SampleOutput.csv"));
		ScrollPanelRefPtr TableAreaScrollPanel = ScrollPanel::create();
        TableAreaScrollPanel->setPreferredSize(Vec2f(200,200));
	    TableAreaScrollPanel->setViewComponent(ExampleTableDomArea);


	    ButtonRefPtr LoadButton = Button::create();
	    LoadButton->setMinSize(Vec2f(50, 25));
        LoadButton->setMaxSize(Vec2f(200, 100));
        LoadButton->setPreferredSize(Vec2f(200, 50));
        LoadButton->setToolTipText("Click to open a file browser window");
        LoadButton->setText("Load Cluster File");
		LoadButton->connectActionPerformed(boost::bind(handleLoadButtonAction, _1, TutorialWindow.get(), ExampleTableDomArea.get()));


		LabelRefPtr tableLabel = Label::create();
		tableLabel->setMinSize(Vec2f(50, 25));
        tableLabel->setMaxSize(Vec2f(200, 100));
		tableLabel->setPreferredSize(Vec2f(100, 50));
		tableLabel->setText("Cluster Data");

		ButtonRefPtr VisualizeButton = Button::create();
	    VisualizeButton->setMinSize(Vec2f(50, 25));
        VisualizeButton->setMaxSize(Vec2f(200, 100));
        VisualizeButton->setPreferredSize(Vec2f(100, 50));
        VisualizeButton->setToolTipText("Click to visualize the data");
        VisualizeButton->setText("Visualize Data");
		VisualizeButton->connectActionPerformed(boost::bind(handleVisualizeButtonAction, _1, TutorialWindow.get(), ExampleTableDomArea.get(),&sceneManager,scene.get()));
	
		FlowLayoutRefPtr PanelFlowLayout = OSG::FlowLayout::create();
		PanelFlowLayout->setHorizontalGap(3);
		PanelFlowLayout->setVerticalGap(3);

		PanelRefPtr ExampleSplitPanelPanel1 = OSG::Panel::create();
		ExampleSplitPanelPanel1->pushToChildren(LoadButton);
		ExampleSplitPanelPanel1->pushToChildren(tableLabel);
		ExampleSplitPanelPanel1->pushToChildren(TableAreaScrollPanel);
		ExampleSplitPanelPanel1->pushToChildren(VisualizeButton);
		ExampleSplitPanelPanel1->setLayout(PanelFlowLayout);


		PanelRefPtr ExampleSplitPanelPanel2 = createExampleSplitPanelPanel2(ExampleTableDomArea.get());

	    BorderLayoutConstraintsRefPtr ExampleSplitPanel2Constraints = OSG::BorderLayoutConstraints::create();
		ExampleSplitPanel2Constraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

		SplitPanelRefPtr ExampleSplitPanel2 = OSG::SplitPanel::create();
		ExampleSplitPanel2->setConstraints(ExampleSplitPanel2Constraints);
		ExampleSplitPanel2->setMaxComponent(ExampleSplitPanelPanel2);
		ExampleSplitPanel2->setDividerPosition(.80); // this is a percentage
		ExampleSplitPanel2->setDividerSize(5);
		ExampleSplitPanel2->setExpandable(false);
		//ExampleSplitPanel2->setMaxDividerPosition(0.80);
		//ExampleSplitPanel2->setMinDividerPosition(0.80);


		BorderLayoutRefPtr MainInternalWindowLayout = OSG::BorderLayout::create();
		BorderLayoutConstraintsRefPtr ExampleSplitPanelConstraints = OSG::BorderLayoutConstraints::create();
		ExampleSplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);


		SplitPanelRefPtr ExampleSplitPanel = OSG::SplitPanel::create();

		ExampleSplitPanel->setConstraints(ExampleSplitPanelConstraints);
		ExampleSplitPanel->setMinComponent(ExampleSplitPanelPanel1);
		ExampleSplitPanel->setMaxComponent(ExampleSplitPanel2);
		
		ExampleSplitPanel->setDividerPosition(.20); // this is a percentage
		ExampleSplitPanel->setDividerSize(5);
		ExampleSplitPanel->setExpandable(false);
		//ExampleSplitPanel->setMaxDividerPosition(0.20);
		//ExampleSplitPanel->setMinDividerPosition(0.20);

		// Create The Main InternalWindow
		// Create Background to be used with the Main InternalWindow
		ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
		MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

		InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
		MainInternalWindow->pushToChildren(ExampleSplitPanel);
		MainInternalWindow->setLayout(MainInternalWindowLayout);
		MainInternalWindow->setBackgrounds(NULL);
		MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
		MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.f,1.f));
		MainInternalWindow->setMenuBar(_MainMenuBar);
		MainInternalWindow->setDrawTitlebar(false);
		MainInternalWindow->setResizable(false);
		MainInternalWindow->setAllInsets(5);

    	  
	
        // Create the Drawing Surface
        UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
    	
	    TutorialDrawingSurface->openWindow(MainInternalWindow);

		setNotepadWindowVisible(true,TutorialDrawingSurface.get(),TutorialWindow.get());

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

		xmlExportScene();

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
