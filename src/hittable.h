// hittable.h, from https://raytracing.github.io by Peter Shirley, 2018-2020
// modified 2021, by alinen, to support glm/float

#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include <sstream>

class material;

struct hit_record {
   glm::point3 p; // the hit position
   glm::vec3 normal; // the normal at the hit position
   float t = -1.0f; // the time t along the ray at which we hit the object
   bool front_face = false; // whether this is a front or back facing hit point
   std::shared_ptr<material> mat_ptr = 0; // save material of hit object

   inline void set_face_normal(const ray& r, const glm::vec3& outward_normal) {
      front_face = glm::dot(glm::normalize(r.direction()), outward_normal) < 0;
      //normal = front_face ? outward_normal :-outward_normal;
       normal = outward_normal;
   }

   inline std::string str() const {
      std::ostringstream ss;
      ss << "position: " << p << std::endl;
      ss << "normal: " << normal << std::endl;
      ss << "time: " << t << std::endl;
      ss << "front?: " << front_face << std::endl;
      return ss.str();
   }
};

class hittable {
public:
   virtual bool hit(const ray& r, hit_record& rec) const = 0;
   virtual ~hittable() {}
};

#endif

