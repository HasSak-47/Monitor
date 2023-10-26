#include <thread>
#include <iostream>

#include <utils.hpp>
#include <system.hpp>
// #include <renderer.hpp>
// #include <progress_bar.hpp>
// #include <system_render.hpp>

System sys;

int main() {
    // mut window = Window();
    // mut bar = MemoryBar(20);
    // bar.bind(window, 0, 0);
    for(size_t i = 0; i <= 1000; ++i){
        sys.update();
        // bar.write();
        // window.render();
        let procs = sys.get_processes();
        for(let proc in procs){
            // std::cout << proc._stat.pid << " : " << proc._stat.name << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::duration<float>(0.1));
    }
    std::this_thread::sleep_for(std::chrono::duration<float>(1.));
}
