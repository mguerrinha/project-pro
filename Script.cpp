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
            if (command == "invert"){
                invert();
                continue;
            }
            if (command == "to_gray_scale"){
                to_gray_scale();
                continue;
            }
            if (command == "replace"){
                replace();
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
            if (command == "rotate_left") {
                rotate_left();
                continue;
            }
            if (command == "rotate_right") {
                rotate_right();
                continue;
            }
            if (command == "xpm2_open") {
                std::string file;
                input >> file;
                image = loadFromXPM2(file);
                continue;
            }
            if (command == "xpm2_save") {
                std::string file;
                input >> file;
                saveToXPM2(file, image);
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
        for(int row = 0; row < image->height(); row++){
            for(int col = 0; col < image->width(); col++){
                image->at(col,row).red()=255-image->at(col,row).red();
                image->at(col,row).green()=255-image->at(col,row).green();
                image->at(col,row).blue()=255-image->at(col,row).blue();
            }
        }    
    }

    void Script::to_gray_scale() {
        for(int row = 0; row < image->height(); row++){
            for(int col = 0; col < image->width(); col++){
                unsigned int r=image->at(col,row).red();
                unsigned int g=image->at(col,row).green();
                unsigned int b=image->at(col,row).blue();
                image->at(col,row).red()=(r+g+b)/3;
                image->at(col,row).green()=(r+g+b)/3;
                image->at(col,row).blue()=(r+g+b)/3;
            }
        }
    }

    void Script::replace() {
        unsigned int r1, g1, b1, r2, g2, b2;
        input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
        for(int row = 0; row < image->height(); row++){
            for(int col = 0; col < image->width(); col++){
                unsigned int r=image->at(col,row).red();
                unsigned int g=image->at(col,row).green();
                unsigned int b=image->at(col,row).blue();
                if(r==r1 && g==g1 && b==b1){
                    image->at(col,row).red()=r2;
                    image->at(col,row).green()=g2; 
                    image->at(col,row).blue()=b2;
                }
            }
        }
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
        Image *cropped_image = new Image(w, h); // imagem onde vai ser gravado o resultado
        for (int row = y; row < y+h; row++) {
            for(int col = x; col < x+w; col++) {
                cropped_image->at(col-x, row-y) = image->at(col, row);
            }
        }
        clear_image_if_any();
        image = cropped_image;
    }

    void Script::rotate_left() {
        Image *rotate90 = new Image(image->height(), image->width());   // imagem onde vai ser guardado o resultado
        for (int row = 0; row < (int)image->height(); row++) {
            for (int col = 0; col < (int)image->width(); col++) {
                rotate90->at(row, col) = image->at(image->width()-col-1, row);
            }
        }
        clear_image_if_any();
        image = rotate90;
    }

    void Script::rotate_right() {
        Image *rotate90 = new Image(image->height(), image->width());   // imagem onde vai ser guardado o resultado
        for (int row = 0; row < (int)image->height(); row++) {
            for (int col = 0; col < (int)image->width(); col++) {
                rotate90->at(row, col) = image->at(col, image->height()-row-1);
            }
        }
        clear_image_if_any();
        image = rotate90;
    }
}
