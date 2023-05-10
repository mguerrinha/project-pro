#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"
#include <algorithm>

using namespace std;

namespace prog {
    // Use to read color values from a script file.
    istream& operator>>(istream& input, Color& c) {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string& filename) :
            image(nullptr), input(filename) {

    }
    void Script::clear_image_if_any() {
        if (image != nullptr) {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script() {
        clear_image_if_any();
    }

    void Script::run() {
        string command;
        while (input >> command) {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open") {
                open();
                continue;
            }
            if (command == "blank") {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save") {
                save();
                continue;
            } 
            if (command == "h_mirror") {
                h_mirror();
                continue;
            }
            if (command == "v_mirror") {
                v_mirror();
                continue;
            }
            if (command == "crop") {
                crop();
                continue;
            }

        }
    }
    void Script::open() {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank() {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save() {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }

    void Script::invert() {
         
    }

    void Script::h_mirror() {
        for (int row = 0; row < image->height(); row++) {
            int middle_col = image->width() / 2;    // index da coluna do meio
            for (int col = 0; col < middle_col; col++) {   // itera até à coluna do meio
                std::swap(image->at(col, row), image->at(image->width() - 1 - col, row));
            }
        }
    }

    void Script::v_mirror() {
        for (int col = 0; col < image->width(); col++) {
            int middle_row = image->height() / 2;   // index da linha do meio
            for (int row = 0; row < middle_row; row++) {    // itera até à linha do meio
                std::swap(image->at(col, row), image->at(col, image->height() - 1 - row));
            }
        }
    }

    void Script::crop() {
        int x, y, w, h;
        input >> x >> y >> w >> h;
        Image *cropped_image = new Image(w, h);
        for (int row = y; row < y+h; row++) {
            for(int col = x; col < x+w; col++) {
                cropped_image->at(col-x, row-y) = image->at(col, row);
            }
        }
        clear_image_if_any();
        image = cropped_image;
    }
}