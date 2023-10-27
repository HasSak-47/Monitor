#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#define let const auto
#define mut auto
#define self (*this)

#define in :

template<typename T>
struct Vector2{
    T x, y;
    Vector2(T _x, T _y):x(_x),y(_y){}
    Vector2(const Vector2<T>& other):x(other.x),y(other.y){}

    bool operator=(const Vector2<T>& other){
        return self.x == other.x && self.y == other.y;
    }
};



#endif
