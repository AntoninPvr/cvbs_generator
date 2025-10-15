#pragma once
#include <vector>
#include <cstdint>



class CVBS {
    public:
        using sample_t = int16_t;

        static constexpr std::size_t default_width  = 320;
        static constexpr std::size_t default_height = 240;
        static constexpr std::uint32_t default_fps  = 60;
        static constexpr double default_black_level = 0.0;
        static constexpr double default_white_level = 1.0;
        static constexpr double default_sync_level  = -0.3;
        static constexpr double default_sync_pulse  = -0.4;
        static constexpr double default_back_porch  = 0.0;
        static constexpr double default_front_porch = 0.0;
        static constexpr uint32_t default_sample_rate = 10'000'000; // in Hz


        explicit CVBS(std::size_t width  = default_width,
                    std::size_t height = default_height,
                    std::uint32_t fps = default_fps,
                    double black_level  = default_black_level,
                    double white_level  = default_white_level,
                    double sync_level   = default_sync_level,
                    double sync_pulse   = default_sync_pulse,
                    double back_porch   = default_back_porch,
                    double front_porch  = default_front_porch,
                    uint32_t sample_rate = default_sample_rate);

    private:
        // Video parameters
        unsigned int width_;
        unsigned int height_;
        unsigned int fps_;
        double black_level_;
        double white_level_;
        double sync_level_;
        double sync_pulse_;
        double back_porch_;
        double front_porch_;
        uint32_t sample_rate_;

        std::vector<sample_t> cvbs_buffer;

};