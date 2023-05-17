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

    string int_to_hex(const int& value) {
        std::string res = "";
        char ch;
        int aux, value_ = value;
        for (int i = 0; i < 2; i++) {
            aux = value_ % 16;
            if (aux >= 0 && aux <= 9) {
                ch = aux + '0';
            }
            else if (aux >= 10 && aux <= 15) {
                aux -= 10;
                ch = aux + 'a';
            }
            res.push_back(ch);
            value_ /= 16;
        }
        swap(res[1], res[0]);
        return res;
    }

    string color_to_hex(const Color& color) {
        int r = color.red(), g = color.green(), b = color.blue();
        std::string res;
        res.append("#");
        res.append(int_to_hex(r));
        res.append(int_to_hex(g));
        res.append(int_to_hex(b));
        return res;
    }

    void saveToXPM2(const std::string& file, const Image* image) {
        ofstream out(file);
        out << "! XPM2" << '\n';
        int xpm2_height, xpm2_width, colors = 0;
        xpm2_height = image->height();
        xpm2_width = image->width();
        map<Color, char> mapa;
        for(int row = 0; row<xpm2_height; row++) {
            for(int col = 0; col<xpm2_width; col++) {
                if(mapa.count(image->at(col, row))==0) {
                    mapa[image->at(col, row)] = 'a' + colors;
                    colors++;
                }
            }
        }
        out << xpm2_width << " " << xpm2_height << " " << colors << " 1" << '\n'; 
        for (const auto& pair : mapa) {
            out << pair.second << " c " << color_to_hex(pair.first) << '\n';
        }
        for(int row = 0; row<xpm2_height; row++){
            for(int col = 0; col<xpm2_width; col++){
                out << mapa[image->at(col, row)];
            }
            out << '\n';
        }
        out.close();
    }
}

