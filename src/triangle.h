#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "hittable.h"
#include "AGLM.h"

class triangle : public hittable {
public:
   triangle() : p0(0), p1(0), p2(0), mat_ptr(0) {}
   triangle(const glm::point3& v0, const glm::point3& v1, const glm::point3& v2, 
      std::shared_ptr<material> m) : p0(v0), p1(v1), p2(v2), mat_ptr(m) {};

   virtual bool hit(const ray& r, hit_record& rec) const override;

public:
   glm::point3 p0;
   glm::point3 p1;
   glm::point3 p2;
   std::shared_ptr<material> mat_ptr;
};

#endif
