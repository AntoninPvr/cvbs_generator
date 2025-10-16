#include "cvbs.h"
#include <stdexcept>

CVBS::CVBS(std::size_t width,
            std::size_t height,
            std::uint32_t fps,
            double black_level,
            double white_level,
            double sync_level,
            double sync_pulse,
            double back_porch,
            double front_porch,
            uint32_t sample_rate)
    : width_(width),
      height_(height),
      fps_(fps),
      black_level_(black_level),
      white_level_(white_level),
      sync_level_(sync_level),
      sync_pulse_(sync_pulse),
      back_porch_(back_porch),
      front_porch_(front_porch),
      sample_rate_(sample_rate)

{
    // Sanitize and validate input parameters
    if (width_ == 0) {
        throw std::invalid_argument("CVBS: width must be >= 1");
    }
    if (height_ == 0) {
        throw std::invalid_argument("CVBS: height must be >= 1");
    }
    if (fps_ == 0) {
        throw std::invalid_argument("CVBS: fps must be >= 1");
    }
    if (black_level_ >= white_level_) {
        throw std::invalid_argument("CVBS: black_level must be less than white_level");
    }
    if (sync_level_ >= black_level_) {
        throw std::invalid_argument("CVBS: sync_level must be less than black_level");
    }
    if (sync_pulse_ < 0.0 ) {
        throw std::invalid_argument("CVBS: sync_pulse must be >= 0.0");
    }
    if (back_porch_ < 0.0 ) {
        throw std::invalid_argument("CVBS: back_porch must be >= 0.0");
    }
    if (front_porch_ < 0.0 ) {
        throw std::invalid_argument("CVBS: front_porch must be >= 0.0");
    }

    // We consider that sync pulse, back porch and front porch are "wasted time"
    double unactive_line_time = sync_pulse + back_porch + front_porch;

    double line_duration = static_cast<double>(fps_ * height_);

    double active_line_time = line_duration - unactive_line_time;

    double pixel_time = active_line_time / width_;

    // Minimum sample rate to satisfy Nyquist theorem
    uint32_t min_sample_rate = (2 / pixel_time);

    if (sample_rate_ <= min_sample_rate) {
        throw std::invalid_argument("CVBS: sample_rate must be >= 1");
    }

    // Calculate the size of the CVBS buffer WIP must add vertical sync
    std::size_t buffer_size = static_cast<std::size_t>(sample_rate_ / fps_);
    cvbs_buffer.resize(buffer_size, 0);
}