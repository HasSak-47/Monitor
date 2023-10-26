#include <thread>

#include <system.hpp>
#include <renderer.hpp>
#include <progress_bar.hpp>

System sys;

int main() {
    mut window = Window();
    mut bar = ProgressBar(20);
    bar.bind(window, 0, 0);
    bar.opts = (Opts)1;
    for(size_t i = 0; i <= 10; ++i){
        bar.set_per(i / 10.);
        bar.write();
        window.render();
        std::this_thread::sleep_for(std::chrono::duration<float>(0.01));
    }
    std::this_thread::sleep_for(std::chrono::duration<float>(1.));
}
