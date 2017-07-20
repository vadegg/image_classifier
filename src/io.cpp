#include "io.h"

// This file is borrowed from Task 1
//
// Changes:
// 1 - This code was removed:
//===========================
// BMP in;
// if (!in.ReadFromFile(path))
// throw string("Error reading file ") + string(path);
//============================
// 2 (26th row):
// Image load_image(const char * path) -> Image load_image(BMP *in)
// 3 (29th row):
// Image res(in.TellHeight(), in.TellWidth()); -> Image res(in->TellHeight(), in->TellWidth());
// 4 (33th row):
// RGBApixel *p = in(j, i); -> RGBApixel *p = (*in)(j, i);

#include <string>
using std::string;

using std::tuple;
using std::make_tuple;
using std::tie;

Image load_image(BMP *in)
{

    Image res(in->TellHeight(), in->TellWidth());

    for (uint i = 0; i < res.n_rows; ++i) {
        for (uint j = 0; j < res.n_cols; ++j) {
            RGBApixel *p = (*in)(j, i);
            res(i, j) = make_tuple(p->Red, p->Green, p->Blue);
        }
    }

    return res;
}

void save_image(const Image &im, const char *path)
{
    BMP out;
    out.SetSize(im.n_cols, im.n_rows);

    uint r, g, b;
    RGBApixel p;
    p.Alpha = 255;
    for (uint i = 0; i < im.n_rows; ++i) {
        for (uint j = 0; j < im.n_cols; ++j) {
            tie(r, g, b) = im(i, j);
            p.Red = r; p.Green = g; p.Blue = b;
            out.SetPixel(j, i, p);
        }
    }

    if (!out.WriteToFile(path))
        throw string("Error writing file ") + string(path);
}
