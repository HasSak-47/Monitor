#include <chrono>
#include <thread>

#include <system.hpp>
#include <renderer.hpp>
#include <progress_bar.hpp>


int main() {
    mut window = Window();
    mut bar = ProgressBar(24);

    bar.bind(window);
    bar.var_char = '#';
    System sys;
    sys.get_processes();

    for(size_t i = 0; i <= 100; ++i){
        sys.refresh();
        float per = float(sys._max_mem - sys._free_mem) / sys._max_mem;
        bar.set_per(per);
        window.render();
        std::this_thread::sleep_for(std::chrono::duration<float>(0.1));
    }
}
