#include "XPM2.hpp"
#include "sstream"
#include "fstream"
#include "map"
using namespace std;

namespace prog {

    int hex_to_decimal(const std::string& str) {
        int res = 0;
        int x = 0;
        for (int i = 0; i < 2; i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                x = str[i] - '0';
            }
            else if (str[i] >= 'a' && str[i] <= 'f') {
                x = str[i] - 87;
            }
            else if (str[i] >= 'A' && str[i] <= 'F') {
                x = str[i] - 55;
            }
            res = res*16 + x;
        }
        return res;
    }

    Color hex_to_color(const std::string& str) {
        Color res;
        std::string str_;
        if (str[0] == '#')
            str_ = str.substr(1, 6);

        std::string r = str_.substr(0, 2);
        std::string g = str_.substr(2, 2);
        std::string b = str_.substr(4, 2);
        res.red() = hex_to_decimal(r);
        res.blue() = hex_to_decimal(b);
        res.green() = hex_to_decimal(g);
        return res;
    }


    Image* loadFromXPM2(const std::string& file) {
        ifstream in(file);
        string line, caracter, str, useless;
        map<string, Color> mapa;
        int png_height, png_width, colors, chars;
        getline(in,line); 
        getline(in,line);
        istringstream aux(line);
        aux >> png_width >> png_height >> colors >> chars; 
        for(int i=0; i<colors; i++){
            getline(in, line);
            istringstream aux(line);
            aux >> caracter >> useless >> str;
            mapa[caracter] = hex_to_color(str);
        }
        Image* image = new Image(png_width, png_height);
        for(int row = 0; row < png_height; row++){
            getline(in, line);
            for(int col = 0; col < png_width; col++){
                image->at(col, row) = mapa[string({line.at(col)})];
            }
        }

        return image;
    }

    void saveToXPM2(const std::string& file, const Image* image) {

        for(int row = 0; row)
    }
}

