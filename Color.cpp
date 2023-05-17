#include "Color.hpp"

namespace prog {
    Color::Color() {
        r_ = 0;
        g_ = 0;
        b_ = 0;
    }
    Color::Color(const Color& other) {
        r_ = other.red();
        g_ = other.green();
        b_ = other.blue();
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        r_ = red;
        g_ = green;
        b_ = blue;
    }
    bool Color::operator<(const Color& rgb) const{
        return r_ < rgb.r_;
    }
    rgb_value Color::red() const {
        return r_;
    }
    rgb_value Color::green() const {
        return g_;
    }
    rgb_value Color::blue() const {
        return b_;
    }

    // TODO: remove this DUMMY variable once you have appropriate fields for representing colors. >>DONE

    rgb_value& Color::red()  {
        return r_;
    }
    rgb_value& Color::green()  {
        return g_;
    }
    rgb_value& Color::blue()  {
        return b_;
    }
}
