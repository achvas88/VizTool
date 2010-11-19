
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

#include "OSGTextEditor.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

// Create a class to allow for the use of the Ctrl+q
void keyTyped(KeyEventDetails* const details,
			TextEditor* const theTextEditor)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
	 else if(details->getKey() == KeyEventDetails::KEY_1 && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
       theTextEditor->setClipboardVisible(!theTextEditor->getClipboardVisible());
    }
    else if(details->getKey() == KeyEventDetails::KEY_2 && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
       theTextEditor->setIsSplit(!theTextEditor->getIsSplit());
    }
}

void handleLoadButtonAction(ActionEventDetails* const details,
                            WindowEventProducer* const TutorialWindow,
							TextEditor* const theTextEditor)
{
	std::vector<WindowEventProducer::FileDialogFilter> Filters;
	Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));
	Filters.push_back(WindowEventProducer::FileDialogFilter("Lua Files","lua"));


	std::vector<BoostPath> FilesToOpen;
	FilesToOpen = TutorialWindow->openFileDialog("Open File Window",
												Filters,
												BoostPath(".."),
												false);

    if(FilesToOpen.size() > 0)
    {
	    theTextEditor->loadFile(FilesToOpen[0]);
    }
}

//
//void handleSaveButtonAction(ActionEventDetails* const details,
//                            WindowEventProducer* const TutorialWindow,
//                            TextEditor* const theTextEditor)
//{
//	std::vector<WindowEventProducer::FileDialogFilter> Filters;
//	Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));
//	Filters.push_back(WindowEventProducer::FileDialogFilter("Lua Files","lua"));
//
//	BoostPath SavePath = TutorialWindow->saveFileDialog("Save File Window",
//														Filters,
//														std::string("newFile.lua"),
//														BoostPath(".."),
//														true);
//	if(SavePath.string() != "")
//    {
//	    theTextEditor->saveFile(SavePath);
//    }
//
//}


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

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);


        // Make Torus Node (creates Torus in background of scene)
        //NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = Node::create();
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
				
		TextEditorRefPtr theTextEditor = TextEditor::create();
	    theTextEditor->setPreferredSize(Vec2f(200,200));
        theTextEditor->setBackgrounds(ExamplePanelBackground1);
        theTextEditor->setBorders(ExamplePanelBorder1);
        
   
	    ButtonRefPtr LoadButton = Button::create();

	    LoadButton->setMinSize(Vec2f(50, 25));
        LoadButton->setMaxSize(Vec2f(200, 100));
        LoadButton->setPreferredSize(Vec2f(100, 50));
        LoadButton->setToolTipText("Click to open a file browser window");
        LoadButton->setText("Load File");

		LoadButton->connectActionPerformed(boost::bind(handleLoadButtonAction, _1, TutorialWindow.get(), theTextEditor.get()));

	
		FlowLayoutRefPtr PanelFlowLayout = OSG::FlowLayout::create();
		PanelFlowLayout->setHorizontalGap(3);
		PanelFlowLayout->setVerticalGap(3);

		PanelRefPtr ExampleSplitPanelPanel1 = OSG::Panel::create();
		ExampleSplitPanelPanel1->pushToChildren(LoadButton);
		ExampleSplitPanelPanel1->pushToChildren(theTextEditor);
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

		// also, if you want to change the way the divider looks, you can always set a
		// DrawObjectCanvas in place of the default divider
		// ExampleSplitPanel->setDividerDrawObject(drawObjectName);

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

    	  
	    //ButtonRefPtr SaveButton = Button::create();

	    //SaveButton->setMinSize(Vec2f(50, 25));
     //   SaveButton->setMaxSize(Vec2f(200, 100));
     //   SaveButton->setPreferredSize(Vec2f(100, 50));
     //   SaveButton->setToolTipText("Click to save the currently opened file");
     //   SaveButton->setText("Save File");

     //   SaveButton->connectActionPerformed(boost::bind(handleSaveButtonAction, _1, TutorialWindow.get(),theTextEditor.get()));

    
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
        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1, theTextEditor.get()));

        commitChanges();

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}

// Callback functions

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
