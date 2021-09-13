#pragma once
#include <cmath>
#include <algorithm>

#include "video.hpp"

#include <glm/glm.hpp>



// linearly interpolates between value a and b over the progress p
inline float Lerp(float a, float b, float p)
{
    return a + p * (b - a);
}


// returns the progress of x between a and b
inline float InvLerp(float x, float a, float b)
{
    return (x - a) / (b - a);
}


// combines Lerp and InvLerp to convert x from range [a, b] to [c, d]
inline float Remap(float x, float a, float b, float c, float d)
{
    return Lerp(c, d, InvLerp(x, a, b));
}


// linearly interpolates two SDL_Color values
inline VIDEO_Color Lerp(const VIDEO_Color& a, const VIDEO_Color& b, float p)
{
    return VIDEO_Color
    {
        (Uint8)Lerp((float)a.r, (float)b.r, p),
        (Uint8)Lerp((float)a.g, (float)b.g, p),
        (Uint8)Lerp((float)a.b, (float)b.b, p),
        (Uint8)Lerp((float)a.a, (float)b.a, p),
    };
}


// linearly interpolates two glm::vec2 values
inline glm::vec2 Lerp(const glm::vec2& a, const glm::vec2& b, float p)
{
    return a + p * (b - a);
}


// linearly interpolates two glm::vec3 values
inline glm::vec3 Lerp(const glm::vec3& a, const glm::vec3& b, float p)
{
    return a + p * (b - a);
}


// linearly interpolates two glm::vec4 values
inline glm::vec4 Lerp(const glm::vec4& a, const glm::vec4& b, float p)
{
    return a + p * (b - a);
}


// if x is smaller than a or greater than b, it is clamped back to that range
inline float Clamp(float x, float a, float b)
{
    return std::max(std::min(x, b), a);
}


// converts an SDL_Color to a glm::vec4
inline glm::vec4 ToVec4(const VIDEO_Color& color)
{
    return glm::vec4
    {
        float(color.r),
        float(color.g),
        float(color.b),
        float(color.a),
    };
}


// converts a glm::vec4 to an SDL_Color
inline VIDEO_Color ToColor(const glm::vec4& color)
{
    return VIDEO_Color
    {
        Uint8(Clamp(color.x, 0.0f, 255.0f)),
        Uint8(Clamp(color.y, 0.0f, 255.0f)),
        Uint8(Clamp(color.z, 0.0f, 255.0f)),
        Uint8(Clamp(color.w, 0.0f, 255.0f)),
    };
}


// blends two SDL_Color values together
inline VIDEO_Color Blend(const VIDEO_Color& a, const VIDEO_Color& b)
{
    return ToColor(((ToVec4(a) / 255.0f) * (ToVec4(b) / 255.0f)) * 255.0f);
}