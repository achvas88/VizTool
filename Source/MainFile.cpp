
// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGSimpleStatisticsForeground.h"

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
#include "OSGAdvancedTextDomArea.h"
#include "OSGButton.h"
#include "OSGColorLayer.h"
#include "OSGLineBorder.h"
#include "OSGTextDomLayoutManager.h"
#include "OSGGlyphView.h"
#include "OSGSplitPanel.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"


#include "OSGPlainTableDOM.h"
#include "OSGCell.h"
#include "OSGTableFileHandler.h"
#include "OSGTableDomArea.h"
#include "OSGTableDomLayoutManager.h"
#include "OSGCellView.h"


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);


void mousePressed(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
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

// Create a class to allow for the use of the Ctrl+q
void keyTyped(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
	
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

ChunkMaterialRefPtr createGreenMaterial(void){

    ChunkMaterialRefPtr GreenBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkRefPtr GreenBackgroundMaterialChunk = MaterialChunk::create();
    GreenBackgroundMaterialChunk->setAmbient(Color4f(0.0,1.0,0.0,1.0));
    GreenBackgroundMaterialChunk->setDiffuse(Color4f(0.0,1.0,0.0,1.0));
    GreenBackgroundMaterialChunk->setSpecular(Color4f(0.0,1.0,0.0,1.0));
    GreenBackgroundMaterial->addChunk(GreenBackgroundMaterialChunk);

    return GreenBackgroundMaterial;

}


void create3DObjects(Node* scene)
{
    // Make Object Nodes
    //NodeRefPtr ExampleSphereGeo = makeSphere(4, 100);
    NodeRefPtr ExampleBoxGeo = makeBox(100, 100, 100, 1, 1, 1);

    dynamic_cast<Geometry*>(ExampleBoxGeo->getCore())->setMaterial(createGreenMaterial());

    Matrix mat;
    mat.setTranslate(0.0,0.0,-100.0);

    TransformRefPtr ExampleBoxTranCore = Transform::create();
    ExampleBoxTranCore->setMatrix(mat);
    
    NodeRefPtr ExampleBox = Node::create();
    ExampleBox->setCore(ExampleBoxTranCore);
    ExampleBox->addChild(ExampleBoxGeo);
	scene->addChild(ExampleBox);

}

void handleVisualizeButtonAction(ActionEventDetails* const details,
                            WindowEventProducer* const TutorialWindow,
                            TableDomArea* const ExampleTableDomArea,
							SimpleSceneManager* mgr,
							Node* scene)
{
	std::cout<<"Visualizing Data"<<std::endl;
	CellRefPtr rootCell = ExampleTableDomArea->getTableDOMModel()->getRootCell();
	UInt32 rows = rootCell->getMaximumRow();
	UInt32 cols = rootCell->getMaximumColumn();
	std::cout<<"rows: "<<rows<<"\tcols: "<<cols<<std::endl;
	for(UInt32 i=0;i<rows;i++)
	{
		for(UInt32 j=0;j<cols;j++)
		{
			CellRefPtr theRow = rootCell->getCell(i);
			if(theRow)
			{	
				CellRefPtr theCell = theRow->getCell(j);
				if(theCell)
				{
					std::string theString = boost::any_cast<std::string>(theCell->getValue());
					std::cout<<theString<<"\t";
				}
			}
		}
		std::cout<<"\n";
	}
	create3DObjects(scene);
	mgr->showAll();
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


        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

		//NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

		NodeRefPtr scene;
        // Make Main Scene Node and add the Torus
        scene = Node::create();
        scene->setCore(Group::create());
        //scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRefPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

			    
		ColorLayerRefPtr ExamplePanelBackground1 = ColorLayer::create();
        ExamplePanelBackground1->setColor(Color4f(0.0,0.0,0.0,1.0));

	    LineBorderRefPtr ExamplePanelBorder1 = LineBorder::create();
        ExamplePanelBorder1->setColor(Color4f(0.9, 0.9, 0.9, 1.0));
        ExamplePanelBorder1->setWidth(3);
		
		TableDomAreaRefPtr ExampleTableDomArea = TableDomArea::create();
		ExampleTableDomArea->setPreferredSize(Vec2f(300,200));
        ColorLayerRefPtr TableDomBg = ColorLayer::create();
        TableDomBg->setColor(Color4f(0.95f,0.95f,0.95f,1.0f));
        ExampleTableDomArea->setBackgrounds(TableDomBg);
	    ExampleTableDomArea->loadFile(BoostPath("D:\\Work_Office_RA\\OpenSGToolBox\\Examples\\Tutorial\\TableDom\\Data\\SampleOutput.csv"));
		ScrollPanelRefPtr TableAreaScrollPanel = ScrollPanel::create();
        TableAreaScrollPanel->setPreferredSize(Vec2f(200,200));
        //TableAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
	    TableAreaScrollPanel->setViewComponent(ExampleTableDomArea);


	    ButtonRefPtr LoadButton = Button::create();
	    LoadButton->setMinSize(Vec2f(50, 25));
        LoadButton->setMaxSize(Vec2f(200, 100));
        LoadButton->setPreferredSize(Vec2f(100, 50));
        LoadButton->setToolTipText("Click to open a file browser window");
        LoadButton->setText("Load Cluster File");
		LoadButton->connectActionPerformed(boost::bind(handleLoadButtonAction, _1, TutorialWindow.get(), ExampleTableDomArea.get()));


		LabelRefPtr tableLabel = Label::create();
		tableLabel->setMinSize(Vec2f(50, 25));
        tableLabel->setMaxSize(Vec2f(200, 100));
		tableLabel->setPreferredSize(Vec2f(100, 50));
		tableLabel->setText("Cluster Data");


		LabelRefPtr noteLabel = Label::create();
		noteLabel->setMinSize(Vec2f(50, 25));
        noteLabel->setMaxSize(Vec2f(200, 100));
		noteLabel->setPreferredSize(Vec2f(100, 50));
		noteLabel->setText("Notepad");
		

		AdvancedTextDomAreaRefPtr theTextEditor = AdvancedTextDomArea::create();
	    theTextEditor->setPreferredSize(Vec2f(200,200));
		theTextEditor->setText("Type your observations here");

		ScrollPanelRefPtr theTextEditorScrollPanel = ScrollPanel::create();
        theTextEditorScrollPanel->setPreferredSize(Vec2f(200,200));
	    theTextEditorScrollPanel->setViewComponent(theTextEditor);

        

		ButtonRefPtr SaveButton = Button::create();
	    SaveButton->setMinSize(Vec2f(50, 25));
        SaveButton->setMaxSize(Vec2f(200, 100));
        SaveButton->setPreferredSize(Vec2f(100, 50));
        SaveButton->setToolTipText("Click to save the currently opened file");
        SaveButton->setText("Save Note");
        SaveButton->connectActionPerformed(boost::bind(handleSaveButtonAction, _1, TutorialWindow.get(),theTextEditor.get()));

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
		ExampleSplitPanelPanel1->pushToChildren(noteLabel);
		ExampleSplitPanelPanel1->pushToChildren(theTextEditorScrollPanel);
		ExampleSplitPanelPanel1->pushToChildren(SaveButton);
		ExampleSplitPanelPanel1->pushToChildren(VisualizeButton);
		ExampleSplitPanelPanel1->setLayout(PanelFlowLayout);

	    BorderLayoutRefPtr MainInternalWindowLayout = OSG::BorderLayout::create();

		BorderLayoutConstraintsRefPtr ExampleSplitPanelConstraints = OSG::BorderLayoutConstraints::create();
		ExampleSplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);


		SplitPanelRefPtr ExampleSplitPanel = OSG::SplitPanel::create();

		ExampleSplitPanel->setConstraints(ExampleSplitPanelConstraints);
		ExampleSplitPanel->setMinComponent(ExampleSplitPanelPanel1);
		
		// ExampleSplitPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
		ExampleSplitPanel->setDividerPosition(.25); // this is a percentage
		ExampleSplitPanel->setDividerSize(5);
		// ExampleSplitPanel->setExpandable(false);
		ExampleSplitPanel->setMaxDividerPosition(0.5);
		ExampleSplitPanel->setMinDividerPosition(0.1);

		// Create The Main InternalWindow
		// Create Background to be used with the Main InternalWindow
		ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
		MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

		InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
		MainInternalWindow->pushToChildren(ExampleSplitPanel);
		MainInternalWindow->setLayout(MainInternalWindowLayout);
		MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
		MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
		MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
		MainInternalWindow->setDrawTitlebar(false);
		MainInternalWindow->setResizable(false);
		MainInternalWindow->setAllInsets(5);

    	  
	
        // Create the Drawing Surface
        UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
    	
	    TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRefPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
		
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRefPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);
    		

        // Show the whole Scene
        sceneManager.showAll();

    	
        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "VizTool");
        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

        commitChanges();

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}

// Callback functions
// react to mouse motions with pressed buttons
/*void motion(int x, int y)
{
    sceneManager.mouseMove(x, y);
	sceneManager.showAll();   
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        sceneManager.mouseButtonRelease(button, x, y);
    else
        sceneManager.mouseButtonPress(button, x, y);
        
    sceneManager.showAll();
}*/

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
