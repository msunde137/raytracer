#include "plane.h"

bool plane::hit(const ray& r, hit_record& rec) const
{
    float len = glm::length(r.direction());
    glm::vec3 d = r.direction() / len;

    float i = glm::dot(d, n);
    if (i == 0) return false;

    float t = -1.0f * (glm::dot(r.origin() - a, n)) / i / len;
    rec.t = t;
    rec.p = r.at(t);
    rec.mat_ptr = mat_ptr;
    rec.set_face_normal(r, n);

    return true;
}
