#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>

#include "Vec2.hpp"

class Animation
{
public:
    std::string texture_key;
    int duration;
    Vec2 frame_size;
    int frames_total;
    int frames_colomn;
    int frame_offset; // Ex) If offset = 3, first 3 frames will be ignored, not 2.(Because first frame is 0, or 0 origin.)
    bool will_zigzag;

    Animation(const std::string &texture_key,
              int duration,
              Vec2 frame_size,
              int frames_total = 1,
              int frames_colomn = 1,
              int frame_offset = 0,
              bool will_zigzag = false);
};

#endif