#include "Image.hpp"

namespace prog
{
    Image::Image(int w, int h, const Color &fill)
    {
        image.assign(h, std::vector<Color>(w, fill));
    }

    Image::~Image()
    {
    }

    int Image::width() const
    {
        int w_max = image[0].size();
        return w_max;
    }

    int Image::height() const
    {
        int h_max = (int)image.size();
        return h_max;
    }

    // TODO: remove this DUMMY_color variable once you have appropriate fields for representing image pixels.
    Color DUMMY_color;

    Color& Image::at(int x, int y)
    {
        return DUMMY_color;
    }

    const Color& Image::at(int x, int y) const
    {
        return DUMMY_color;
    }
}
