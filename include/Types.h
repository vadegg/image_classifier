#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <iostream>
#include <cmath>
#include <tuple>

#include "EasyBMP.h"

#include "matrix.h"

typedef std::pair<BMP*, int> TData;
typedef std::vector<TData> TDataSet;

typedef std::pair<std::string, int> TFile;
typedef std::vector<TFile> TFileList;

typedef float TSingleFeature;
typedef std::vector<float> TOneFileFeature;
typedef std::pair<TOneFileFeature, int> TFeature;
typedef std::vector<TFeature> TFeatures;

typedef std::tuple<uint, uint, uint> Pixel;
typedef Matrix<Pixel> Image;

typedef Matrix<double> Kernel;

typedef float GradientComponent;
typedef Matrix<GradientComponent> GradientComponentMatrix;
typedef std::pair<GradientComponent, GradientComponent> GradientVector;
typedef Matrix<GradientVector> GradientMatrix;

typedef std::vector<int> TLabels;
