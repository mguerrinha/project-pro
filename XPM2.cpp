#include "XPM2.hpp"
#include "fstream"

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

    Color hex_to_color(std::string str) {
        Color res;
        

        if (str[0] == '#')
            str = str.erase(0, 1);

        std::string r = str.substr(0, 2);
        std::string b = str.substr(2, 2);
        std::string g = str.substr(4, 2);
        res.red() = hex_to_decimal(r);
        res.blue() = hex_to_decimal(b);
        res.green() = hex_to_decimal(g);
        return res;
    }

    Image* loadFromXPM2(const std::string& file) {
        std::ifstream ifs (file);
        
        return nullptr;
    }

    void saveToXPM2(const std::string& file, const Image* image) {
        int h = image->height(), w = image->width();
        std::ofstream ofs (file);
        ofs << "! XPM2";
        
    }
}
