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
    mut bar = MemoryBar(40);
    bar.bind(window, 0, 0);
    for(size_t i = 0; i <= 1000; ++i){
        sys.update();
        window.render();
        std::this_thread::sleep_for(std::chrono::duration<float>(0.1));
    }
    std::this_thread::sleep_for(std::chrono::duration<float>(1.));
}
