// Copyright (c) 2021 Bilal Ahsan

/* 
   com.perfectcircle.pcsclient
*/

//Shift to AlgeBASE
class iAlge {
    
public:
    class UIMaker {
    
    };
    
    UIMaker uimaker;

};
//

#include "PCSClient.hpp"

class /*PCSClient*/ App : public AlgeApp {
    
    PCSClientApp pcs;
    iAlge* iapp ;
    
    bool my_tool_active;
    float my_color[4];
    ImFont *roboto;
    i2 msize;
    i2 mou;
    bool done = false;

    //Gfx Objects
	GameObject background, gui;

public:
    virtual void Init(char* path) {
        iapp = (new PCSClientApp)->init();
        mpath = path;
        AlInit(STANDARD);
        SetTitle("XGui");
    
    AddDefaultCamera(Camera::CAM_MODE_2D,OrthoTypes::ORIGIN_IN_TOP_LEFT_OF_SCREEN);
        
        AddResource(&background, "juices",
            "green_natural.jpg",
            XFunction_AutoScalingToFullScreen::AUTO_SCALING_FULLSCREEN
            );


        AddResource(&gui, "gui");
        gui.hidden = false;
        ImGui::GetIO().Fonts->AddFontDefault();
        roboto = ImGui::GetIO().Fonts->AddFontFromFileTTF((string(path)+"/Roboto-Bold.ttf").c_str(), 16.0f);
    }
    
    //App Specifics
    class ImWindows {
        i2 msize;
        i2 mou;
        ImFont *roboto;
    public:
        void MyFirstToolWindow(float dt) {
            
               static float f = 0.0f;
               static int counter = 0;
               
               ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
               ImGui::PushFont(roboto);
               ImGui::Text("Screen Size = {%d x %d}", msize.x, msize.y);               // Display some text (you can use a format strings too)
               ImGui::PopFont();
               ImGui::Text("Mouse Pos = {%d x %d}", mou.x, mou.y);               // Display some text
            
               ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
               ImGui::Checkbox("Another Window", &show_another_window);

               ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
               ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

               if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                   counter++;
               ImGui::SameLine();
               ImGui::Text("counter = %d", counter);

               ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::SetWindowPos(ImVec2(0, 50), true);
            ImGui::End();
        }
    };
    void MyFirstToolWindow(float dt) {
    
        static float f = 0.0f;
        static int counter = 0;
        
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        ImGui::PushFont(roboto);
        ImGui::Text("Screen Size = {%d x %d}", msize.x, msize.y);               // Display some text (you can use a format strings too)
        ImGui::PopFont();
        ImGui::Text("Mouse Pos = {%d x %d}", mou.x, mou.y);               // Display some text
    
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Hayai"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        {
            
          }
        
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::SetWindowPos(ImVec2(0, 50), true);
    ImGui::End();
}

public:
    char* mpath;
    //Primary Functions

    void processInput(PEG::CMD* p, float deltaT) {
		if (p->command == CMD_SCREENSIZE) {
            msize.x = p->i1;
            msize.y = p->i2;
		}
  	}
	void UpdateCustom(GameObject* gob,int instanceNo, float deltaT) {
        if (gob->is(gui) && !gui.hidden)
        {
            GuiStarts();
                MyFirstToolWindow(deltaT);
                if (show_demo_window) ImGui::ShowDemoWindow();
            GuiEnds();
        }

	}

    //Secondary Functions
    i2 getBackgroudSize() {return msize;}
};
