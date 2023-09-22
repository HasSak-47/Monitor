#include <chrono>
#include <renderer.hpp>
#include <thread>


int main() {
    auto window = Window();
    auto bar = ProgressBar(window.get_size().x);
    bar.bind(window);
    bar.set_per(0.1);
    bar.write();
    window.render();

    std::this_thread::sleep_for(std::chrono::duration<int>(1));

}
