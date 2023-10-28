#ifndef __DIVIDED_BAR_HPP__
#define __DIVIDED_BAR_HPP__

#include "progress_bar.hpp"


class DividedBar: public ProgressBar{
private:
    std::vector<ProgressBar> Sections;
public:
    DividedBar(size_t len);

    [[deprecated("It does fucking nothing")]]
    void set_per(float per);


    void get_pers(std::vector<float> pers);

};

#endif

