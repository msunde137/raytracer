// ray.h, from https://raytracing.github.io by Peter Shirley, 2018-2020
#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "AGLM.h"

class sphere : public hittable {
public:
   sphere() : radius(0), center(0), mat_ptr(0) {}
   sphere(const glm::point3& cen, float r, std::shared_ptr<material> m) : 
      center(cen), radius(r), mat_ptr(m) {};

   virtual bool hit(const ray& r, hit_record& rec) const override;

public:
   glm::point3 center;
   float radius;
   std::shared_ptr<material> mat_ptr;
};
#endif

