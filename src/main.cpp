#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


struct GrayscaleCoeffs {
    double r, g, b;
    GrayscaleCoeffs(double r_=0.299, double g_=0.587, double b_=0.114) : r(r_), g(g_), b(b_) {}
};

std::vector<uint8_t> rgb_to_grayscale(const std::vector<unsigned char>& rgb, int width, int height, int channels, const GrayscaleCoeffs& coeffs) {
    std::vector<uint8_t> gray;
    if (channels < 3) return gray;
    gray.reserve(width * height);
    for (int i = 0; i < width * height; ++i) {
        int idx = i * channels;
        double val = coeffs.r * rgb[idx] + coeffs.g * rgb[idx+1] + coeffs.b * rgb[idx+2];
        gray.push_back(static_cast<uint8_t>(std::clamp(val, 0.0, 255.0)));
    }
    return gray;
}



int main(int argc, char* argv[]) {

    std::string inputFile;
    for (int i = 1; i < argc; ++i) {
        if ((std::string(argv[i]) == "-i" || std::string(argv[i]) == "--input") && i + 1 < argc) {
            inputFile = argv[++i];
        }
    }

    if (inputFile.empty()) {
        std::cerr << "Usage: " << argv[0] << " -i <input_file> or --input <input_file>" << std::endl;
        return 1;
    }

    std::vector<unsigned char> imageData;
    int width, height, channels;
    unsigned char* data = stbi_load(inputFile.c_str(), &width, &height, &channels, 0);
    if (data) {
        imageData.assign(data, data + (width * height * channels));
        std::cout << "Image loaded: " << width << "x" << height << " with " << channels << " channels." << std::endl;
            std::cout << (int)data[0] << std::endl;

            GrayscaleCoeffs coeffs;
            auto gray = rgb_to_grayscale(imageData, width, height, channels, coeffs);
            std::cout << "First grayscale value: " << (int)gray[0] << std::endl;
        stbi_image_free(data);
    } else {
        std::cerr << "Failed to load image." << std::endl;
        return -1;
    }
    return 0;
}