#include "triangle.h"

bool triangle::hit(const ray& r, hit_record& rec) const
{
    glm::vec3 o = r.origin();
    float len = glm::length(r.direction());
    glm::vec3 d = r.direction() / len;
    glm::vec3 e1 = p1 - p0;
    glm::vec3 e2 = p2 - p0;
    glm::vec3 q = glm::cross(d, e2);
    float a = glm::dot(e1, q);
    if (near_zero(a)) return false;

    float f = 1 / a;
    glm::vec3 s = o - p0;
    float u = f * glm::dot(s, q);
    if (u < 0) return false;

    glm::vec3 x = glm::cross(s, e1);
    float v = f * glm::dot(d, x);           
    if (v < 0 || u + v > 1.0f) return false;

    float t = f * glm::dot(e2, x) / len;
    glm::point3 p = r.at(t);
    glm::vec3 n = glm::normalize(glm::cross(e1, e2));
    rec = { p, n, t, glm::dot(n, d) < 0, mat_ptr };
    return true;
}
