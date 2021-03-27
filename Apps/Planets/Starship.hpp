// Copyright (c) 2018 AcnodLabs Inc

/* 
 ALGE SDK JD4 Demo :: PoppingTime
 The Assets Folder Name is PoppingTime.Assets,
 macOS Note:- Navigate to App Folder by File > Show in Finder then Ctrl + UP to view peer .Assets Folder, Drop it in xcode project before run [this step is not required in Windows/VS]
 */

#include "SolarDb.hpp"



class Burners : public GameObject {
public:
    void LoadIn(AlgeApp* that) {
        that->AddResource(this, "burn", "burn.jpg", 0.5);
    }
};

class ShipAttitudeController {
public:
    int burner_rotz = 0;
    int ship_rotz = 0;
    int burner_rotx = 0;
    int ship_rotx = 0;
    
    void SetZTilt(int angle) {
        burner_rotz = angle;
        ship_rotz = angle;
    }
    void SetXTilt(int angle) {
        burner_rotx = angle;
        ship_rotx = angle;
    }
    
    int xx =0;
    
    void Transform(char thing, GameObject& obj) {
        if (thing=='b') {
            obj.rot.y = burner_rotz - 90;
            obj.rot.x = burner_rotx ;
        }
        if (thing=='s') {
            obj.rot.y = ship_rotz;
            obj.rot.x = ship_rotx;
        }
    }
        
};


class StarShip {
public:
    Burners burners;
    ShipAttitudeController controls;
    GameObject ship;
    void LoadIn(AlgeApp* that) {
        float density = 1.1;
        float restitution = 0.1;
        that->AddResourceEx(&ship, "Starship/DSC5164", "Starship/DSC5164", 1, false, /*oSize*/0.2, density, restitution);//false::Polygon/Box
        burners.LoadIn(that);
        ship.AddChild(&burners);
        burners.JuiceType = JuiceTypes::JUICE_ROTY;
        burners.JuiceSpeed = 200;
        burners.hidden = true;
        ship.getInstancePtr(0)->physBodyPtr->SetTransform(b2Vec2(that->rightSide*0.5*S2P, 0), 0);
    }
};

class AWindow {
public:
    GameObject gui;
    void Init(AlgeApp* that) {
        that->AddResource(&gui, "gui");
    }

    void Update(GameObject* check, float deltaT) {
        if (check->is(gui) && !gui.hidden)
        {
            //GuiStarts();
            //Show(deltaT);
            //GuiEnds();
        }
    }

    void Show(float dt) {
    //    {
    //        static string m_vehregno, m_result;
    //        static float f = 0.0f;
    //        static int counter = 0;

    //        ImGui::Begin("Vehicle Lookup");                          // Create a window called "Hello, world!" and append into it.

    //        ImGui::InputText("Enter Vehicle Reg No XX-NNN", (char*)m_vehregno.c_str(), 128, 0, 0, 0);
    //        bool clicked = ImGui::Button("Go!");
    //        if (clicked) {
    //            netmsg.Post("veh_regno=" + string(m_vehregno));
    //        }
    //        ImGui::Text("%s", m_result);

    //        //ImGui::Text("Screen Size = {%d x %d}", msize.x, msize.y);               // Display some text (you can use a format strings too)
    //        //ImGui::Text("Mouse Pos = {%d x %d}", mou.x, mou.y);               // Display some text

    //        //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    //        //ImGui::Checkbox("Another Window", &show_another_window);

    //        //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    //        //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    //        //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
    //        //    counter++;
    //        //ImGui::SameLine();
    //        //ImGui::Text("counter = %d", counter);

    //        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    //        ImGui::SetWindowPos(ImVec2(0, 50), true);
    //        ImGui::End();
    //    }
    }
};
