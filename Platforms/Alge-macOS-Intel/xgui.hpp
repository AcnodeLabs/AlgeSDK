// XGui stuff
#include "../../../imgui/imgui.h"
#include "../../../imgui/backends/imgui_impl_glut.h"
#include "../../../imgui/backends/imgui_impl_opengl2.h"

static bool show_demo_window = true;
static bool show_another_window = false;
static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void ImGui_ImplAlgeSDK_Main(int x, int y, int framebufferScale ) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.DisplaySize.x = x;
    io.DisplaySize.y = y;
#ifdef MACOSX
    io.DisplayFramebufferScale = ImVec2(framebufferScale, framebufferScale); //
#endif
    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();
    //ImGui::SetWindowFontScale(2);
    ImGui_ImplGLUT_Init();
    
    ImGui_ImplOpenGL2_Init();
}

void ImGui_ImplAlgeSDK_AfterRender()
{
    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();

  //      glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
  //      glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  //     glClear(GL_COLOR_BUFFER_BIT);
    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}


void ImGui_ImplAlgeSDK_BeforeRender()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();
//    ImGui::NewFrame();
}

void ImGui_ImplAlgeSDK_Shutdown() {
    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}

void GuiStarts() {
    ImGui_ImplAlgeSDK_BeforeRender();
}

void GuiEnds() {
    ImGui_ImplAlgeSDK_AfterRender();
}


////////////////////////
