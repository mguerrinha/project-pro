#include "Color.hpp"

namespace prog {
    Color::Color() {
        this-> r_ = 0;
        this-> g_ = 0;
        this-> b_ = 0;
    }
    Color::Color(const Color& other) {
        this->r_ = other.red();
        this->g_ = other.green();
        this->b_ = other.blue();
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        this->r_ = red;
        this->g_ = green;
        this->b_ = blue;
    }
    rgb_value Color::red() const {
        return this->r_;
    }
    rgb_value Color::green() const {
        return this->g_;
    }
    rgb_value Color::blue() const {
        return this->b_;
    }

    // TODO: remove this DUMMY variable once you have appropriate fields for representing colors. >>DONE

    rgb_value& Color::red()  {
        return this-> r_;
    }
    rgb_value& Color::green()  {
      return this-> g_;
    }
    rgb_value& Color::blue()  {
      return this-> b_;
    }
}

