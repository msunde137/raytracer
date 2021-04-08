// Aline Normoyle, 2020
// Convenience header for utilities and common includes 

#pragma once
#include <iostream>
#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/epsilon.hpp>
#include <limits>
#include <memory>
#include <random>
#include <cmath>

extern std::ostream& operator<<(std::ostream& o, const glm::mat4& m);
extern std::ostream& operator<<(std::ostream& o, const glm::mat3& m);
extern std::ostream& operator<<(std::ostream& o, const glm::vec3& v);
extern std::ostream& operator<<(std::ostream& o, const glm::vec4& v);
extern std::ostream& operator<<(std::ostream& o, const glm::vec2& v);

namespace glm
{
   using point3 = glm::vec3;
   using color = glm::vec3;
}
const float pi = glm::pi<float>();
const float infinity = std::numeric_limits<float>::infinity();

inline float random_float() 
{
   static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
   static std::mt19937 generator;
   return distribution(generator); 
}

inline float random_float(float min, float max) 
{
   static std::uniform_real_distribution<float> distribution(min, max);
   static std::mt19937 generator;
   return distribution(generator);
}

inline glm::vec3 random_unit_cube() 
{
   float x = random_float(-1,1);
   float y = random_float(-1,1);
   float z = random_float(-1,1);
   return glm::vec3(x, y, z);
}

inline glm::vec3 random_unit_square() 
{
   float x = random_float(-1,1);
   float y = random_float(-1,1);
   return glm::vec3(x, y, 0);
}


inline glm::vec3 random_unit_sphere() 
{
   glm::vec3 p = random_unit_cube();
   while (glm::length(p) >= 1.0f) 
   {
      p = random_unit_cube();
   } 
   return p;
}

inline glm::vec3 random_unit_disk()
{
    glm::vec3 p = random_unit_square();
    while (glm::length(p) >= 1.0f)
    {
        p = random_unit_square();
    }
    return p;
}

// Generate random direction in hemisphere around normal
// from https://raytracing.github.io/books/RayTracingInOneWeekend.html (Peter Shirley)
inline glm::vec3 random_hemisphere(const glm::vec3& normal) 
{
   glm::vec3 in_unit_sphere = random_unit_sphere();
   if (glm::dot(in_unit_sphere, normal) > 0.0f) // In the same hemisphere as the normal
   {
       return in_unit_sphere;
   }
   else
   {
       return -in_unit_sphere;
   }
}

// Generate random unit vector
// from https://raytracing.github.io/books/RayTracingInOneWeekend.html (Peter Shirley)
inline glm::vec3 random_unit_vector() 
{
   return glm::normalize(random_unit_sphere());
}

// test for vec3 close to zero (avoid numerical instability)
// from https://raytracing.github.io/books/RayTracingInOneWeekend.html (Peter Shirley)
inline bool near_zero(const glm::vec3& e) 
{
   // Return true if the vector is close to zero in all dimensions.
   const auto s = 1e-8;
   return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

inline bool near_zero(float f)
{
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(f) < s);
}

