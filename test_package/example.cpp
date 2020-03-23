#include <iostream>
#include "imgui_plot.h"
#include <cmath>

#include <memory>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <imgui-SFML.h>

constexpr size_t buf_size = 512;
static float x_data[buf_size];
static float y_data1[buf_size];
static float y_data2[buf_size];
static float y_data3[buf_size];

void generate_data() {
    constexpr float sampling_freq = 44100;
    constexpr float freq = 500;
    for (size_t i = 0; i < buf_size; ++i) {
        const float t = i / sampling_freq;
        x_data[i] = t;
        const float arg = 2 * M_PI * freq * t;
        y_data1[i] = sin(arg);
        y_data2[i] = y_data1[i] * -0.6 + sin(2 * arg) * 0.4;
        y_data3[i] = y_data2[i] * -0.6 + sin(3 * arg) * 0.4;
    }
}

void draw_multi_plot() {
    static const float* y_data[] = { y_data1, y_data2, y_data3 };
    static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
    static uint32_t selection_start = 0, selection_length = 0;

    ImGui::Begin("Example plot", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    // Draw first plot with multiple sources
    ImGui::PlotConfig conf;
    conf.values.xs = x_data;
    conf.values.count = buf_size;
    conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
    conf.values.ys_count = 3;
    conf.values.colors = colors;
    conf.scale.min = -1;
    conf.scale.max = 1;
    conf.tooltip.show = true;
    conf.grid_x.show = true;
    conf.grid_x.size = 128;
    conf.grid_x.subticks = 4;
    conf.grid_y.show = true;
    conf.grid_y.size = 0.5f;
    conf.grid_y.subticks = 5;
    conf.selection.show = true;
    conf.selection.start = &selection_start;
    conf.selection.length = &selection_length;
    conf.frame_size = ImVec2(buf_size, 200);
    ImGui::Plot("plot1", conf);

    // Draw second plot with the selection
    // reset previous values
    conf.values.ys_list = nullptr;
    conf.selection.show = false;
    // set new ones
    conf.values.ys = y_data3;
    conf.values.offset = selection_start;
    conf.values.count = selection_length;
    conf.line_thickness = 2.f;
    ImGui::Plot("plot2", conf);

    ImGui::End();
}



int main()
{
    // sf::RenderWindow window(sf::VideoMode(640, 480), "ImGui + SFML = <3");
    // window.setFramerateLimit(60);
    // ImGui::SFML::Init(window);

    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);

    // sf::Clock deltaClock;
    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         ImGui::SFML::ProcessEvent(event);

    //         if (event.type == sf::Event::Closed) {
    //             window.close();
    //         }
    //     }

    //     ImGui::SFML::Update(window, deltaClock.restart());

    //     // ImGui::Begin("Hello, world!");
    //     // ImGui::Button("Look at this pretty button");
    //     // ImGui::End();

    //     generate_data();
    //     draw_multi_plot();

    //     window.clear();
    //     window.draw(shape);
    //     ImGui::SFML::Render(window);
    //     window.display();
    // }

    // ImGui::SFML::Shutdown();
}
