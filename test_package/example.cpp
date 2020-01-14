#include <imgui-SFML.h>
#include <imgui.h>
#include <imgui_plot.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

int main(int, char **) {
  ImGuiContext *context = ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();

  // Build atlas
  unsigned char *tex_pixels = NULL;
  int tex_w, tex_h;
  io.Fonts->GetTexDataAsRGBA32(&tex_pixels, &tex_w, &tex_h);

  for (int n = 0; n < 50; n++) {
    printf("NewFrame() %d\n", n);
    io.DisplaySize = ImVec2(1920, 1080);
    io.DeltaTime = 1.0f / 60.0f;
    ImGui::NewFrame();

    static float f = 0.0f;
    ImGui::Text("Hello, world!");
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / io.Framerate, io.Framerate);
    ImGui::ShowDemoWindow(NULL);

    ImGui::PlotConfig conf;
    // conf.values.xs = x_data; // this line is optional
    // conf.values.ys = y_data;
    // conf.values.count = data_count;
    // conf.scale.min = -1;
    // conf.scale.max = 1;
    // conf.tooltip.show = true;
    // conf.tooltip.format = "x=%.2f, y=%.2f";
    // conf.grid_x.show = true;
    // conf.grid_y.show = true;
    // conf.frame_size = ImVec2(400, 400);
    // conf.line_thickness = 2.f;

    ImGui::Plot("plot", conf);

    ImGui::Render();
  }

  printf("DestroyContext()\n");
  ImGui::DestroyContext(context);
  return 0;
}
