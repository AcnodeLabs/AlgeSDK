
class DataBuffer {
public:
    float dat[64];
    void pushDat(float f) {
        for (int i=0; i<64; i++) {
            dat[i] = dat[i+1];
        }
        dat[63] = f;
    }
    void clear() {
        memset(dat,0,sizeof(dat));
    }
    
};

class StarShipAppGui {
    bool my_tool_active = true;
public:
    GameObject gob;
    void RenderGui(float dt, int rightSide, int bottomSide, DataBuffer& bufHeight, StarShip& starship) {
        if (gob.Visible()) {
            GuiStarts();
#ifndef NO_IMGUI
        // Create a window called "My First Tool", with a menu bar.
        Begin("Starship Parameters", &my_tool_active, ImGuiWindowFlags_MenuBar);
        ImGui::SetWindowSize(ImVec2((float)rightSide/2, (float)bottomSide/3));
        // Edit a color (stored as ~4 floats)
        //ColorEdit4("Color", my_color);

        // Plot some values
        
        PlotLines("Height", bufHeight.dat, sizeof(bufHeight.dat));

        // Display contents in a scrolling region
        TextColored(ImVec4(1,1,0,1), "Altitude");
        for (auto b : starship.ship.prsInstances) {
            ImGui::Text("Alt@ [%d m]", starship.Alt());
        }
       
        BeginChild("Controls");
        if (starship.burner_on)
            ImGui::SliderFloat("Thrust [2-3]", &starship.force, 2., 3.);
        ImGui::SliderFloat("Torque", &starship.torque, -0.01,0.01);
        ImGui::Checkbox("Burners", &starship.burner_on);
        starship.burners.hidden = !starship.burner_on;
        if (!starship.burner_on) starship.force = 0;
        if (ImGui::Button("Redo")) starship.reset();
            
        EndChild();
        
        End();
#endif // !NO_IMGUI
           
        GuiEnds();
        }
    }
};
