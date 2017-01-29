#include "../include/ColorSampler.h"

void ColorSampler::update(const Mat& frame) {
    // empty as fuck
}

Point ColorSampler::current() const {
    return dynconf.samplingRegion.tl() + Point(dynconf.samplingRegion.width/2, dynconf.samplingRegion.height/2);
}

Mat ColorSampler::takeSample(Mat& frame) {
    /* INTENTO DE HISTOGRAMA 3D */
    Mat roi = frame(dynconf.samplingRegion);

    int nimages = 1; // only one 3-channel image
    const int channels[3] = {0,1,2};
    int dims = 3; // 3 dims: B, G and R.
    int histSize[] = {256, 256, 256}; // each color is in uchar range 0..255
    float singleBinRange[2] = {0, 256};
    const float* ranges[3] = {singleBinRange, singleBinRange, singleBinRange};

    Mat hist;
    calcHist(&roi, nimages, channels, Mat(), hist, dims, histSize, ranges);

    return hist;
}
