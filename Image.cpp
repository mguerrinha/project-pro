#include "Image.hpp"

namespace prog
{
    Image::Image(int w, int h, const Color &fill)
    {
        std::vector<std::vector<Color>> image (h, std::vector<Color> (w, fill));
    }

    Image::~Image()
    {
    }

    int Image::width() const
    {
        return (int)image.size();
    }

    int Image::height() const
    {
        return (int)image[0].size();
    }

    // TODO: remove this DUMMY_color variable once you have appropriate fields for representing image pixels.
    Color DUMMY_color;

    Color& Image::at(int x, int y)
    {
        return image[y][x];
    }

    const Color& Image::at(int x, int y) const
    {
        return image[y][x];
    }
}

int main() {
    {}
}