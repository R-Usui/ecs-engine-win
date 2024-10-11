#include <stdexcept>

#include "Animation.hpp"

Animation::Animation(const std::string &texture_key,
                     int duration,
                     Vec2 frame_size,
                     int frames_total,
                     int frames_colomn,
                     int frame_offset,
                     bool will_zigzag)
    : texture_key{texture_key},
      duration{duration},
      frame_size{frame_size},
      frames_total{frames_total},
      frames_colomn{frames_colomn},
      frame_offset{frame_offset},
      will_zigzag{will_zigzag}
{
  if (duration <= 0)
  {
    throw std::range_error("Parameter 'duration' must be positive. (You tried to set " + std::to_string(duration) + ".) (Thrown by Animation::Animation())");
  }
  else if (frame_size.x <= 0 || frame_size.y <= 0)
  {
    throw std::range_error("Parameter 'frame_size' must be positive. (You tried to set " + static_cast<std::string>(frame_size) + ".) (Thrown by Animation::Animation())");
  }
  else if (frames_total <= 0)
  {
    throw std::range_error("Parameter 'frames_total' must be positive. (You tried to set " + std::to_string(frames_total) + ".) (Thrown by Animation::Animation())");
  }
  else if (frames_colomn <= 0)
  {
    throw std::range_error("Parameter 'frames_colomn' must be positive. (You tried to set " + std::to_string(frames_colomn) + ".) (Thrown by Animation::Animation())");
  }
}
