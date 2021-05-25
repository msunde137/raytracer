#include "sphere.h"

bool sphere::hit(const ray& r, hit_record& rec) const 
{
    glm::vec3 r_orig = r.origin();

    float len = glm::length(r.direction());
    glm::vec3 d = r.direction() / len;
    glm::vec3 el = center - r_orig;
    float s = glm::dot(el, d);
    float elSqr = glm::dot(el, el);
    float rSqr = radius * radius;
    float mSqr = elSqr - s * s;
    float q = sqrt(rSqr - mSqr);
    float t;
    if (s < 0 && elSqr > rSqr) t = -1;
    else if (mSqr > rSqr) t = -1;
    else if (elSqr > rSqr) t = (s - q) / len;
    else t = (s + q) / len;

    //glm::vec3 oc = r_orig - center;
    //float a = glm::dot(r.direction(), r.direction());
    //float half_b = glm::dot(oc, r.direction());
    //float c = glm::length2(oc) - radius * radius;
    //float discriminant = half_b * half_b - a * c;
    //if (discriminant < 0) return false;
    //float sqrtd = sqrt(discriminant);
    //float t = (-half_b - sqrtd) / a;
    //if (t < 0) t = (-half_b + sqrtd) / a;
    if (t < 0) return false;

    // save relevant data in hit record
    rec.t = t; // save the time when we hit the object
    rec.p = r.at(t); // ray.origin + t * ray.direction
    rec.mat_ptr = mat_ptr;

    // save normal
    glm::vec3 outward_normal = normalize(rec.p - center); // compute unit length normal
    rec.set_face_normal(r, outward_normal);
    
    //if (rec.front_face && r_orig.z <= .5 && rec.p.z < -1)
        //__debugbreak();
    //if (!rec.front_face && r_orig.z > .5 && rec.p.z > -1)
    //    __debugbreak();

    return true;
}
