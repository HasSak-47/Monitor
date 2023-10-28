#include <string>
#include <thread>
#include <iostream>

#include <utils.hpp>
#include <system.hpp>
#include <renderer.hpp>
#include <text_line.hpp>
#include <progress_bar.hpp>
#include <system_render.hpp>

System sys;

char text[] = "test text with a lot of chars!";

int main() {
    mut window = Window();
    mut bar = ProgressBar(40);
    mut bar2 = ProgressBar(40);
    bar.bind(window, 0, 0);
    bar2.bind(window, 0, 1);
    for(size_t i = 0; i <= 1000; ++i){
        bar.set_per(i / 1000.);
        bar2.set_per(i / 1000.);
        bar.color.foreground.b = i;
        bar2.color.foreground.b = 1000 - i;
        window.render();
        std::this_thread::sleep_for(std::chrono::duration<float>(0.01));
    }
    std::this_thread::sleep_for(std::chrono::duration<float>(2.));
}
