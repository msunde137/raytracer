#include "material.h"

bool phong::scatter(const ray& r_in, const hit_record& hit,
    glm::color& attenuation, ray& scattered) const
{
    glm::vec3 lightDir = hit.p - lightPos;
    float light = std::max(0.0f, glm::dot(-hit.normal, glm::normalize(hit.p - lightPos)));

    glm::vec3 hlf = -glm::normalize(glm::normalize(lightDir) + glm::normalize(hit.p));
    float spec = pow(std::max(glm::dot(hit.normal, hlf), 0.0f), shininess) / (1 + pow(2.7, -100 * light + 5));

    attenuation = ambientColor + light * diffuseColor + spec * specColor;
    scattered.dir = random_hemisphere(hit.normal);
    scattered.orig = hit.p;
    return false;
}

bool lambertian::scatter(const ray& r_in, const hit_record& rec, glm::color& attenuation, ray& scattered) const
{
    if (rec.front_face)
    {
        attenuation = albedo;
        scattered.dir = random_hemisphere(rec.normal);
        scattered.orig = rec.p;
    }
    else
    {
        attenuation = glm::vec3(1, 1, 1);
        scattered.dir = r_in.direction();
        scattered.orig = rec.p;
    }
    return true;
}

glm::vec3 refract(const glm::vec3& uv, const glm::vec3& n, float etai_over_etat) {
    float cos_theta = fmin(glm::dot(-uv, n), 1.0f);
    glm::vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    glm::vec3 r_out_parallel = (float)-glm::sqrt(glm::abs(1.0f - pow(r_out_perp.length(), 2.0f))) * n;
    return r_out_perp + r_out_parallel;
}

bool dielectric::scatter(const ray& r_in, const hit_record& rec, glm::color& attenuation, ray& scattered) const
{
    //attenuation = glm::color(1);
    //glm::vec3 ray_dir = glm::normalize(r_in.direction());
    //glm::vec3 axis = glm::cross(rec.normal, ray_dir);
    //float sina = glm::length(axis);
    //if (rec.front_face)
    //{
    //    //float sinb = sina / ir;
    //    //float angle = glm::asin(sinb);
    //    //glm::mat4 quat = glm::rotate(glm::mat4(1), angle, axis);
    //    //scattered.dir = glm::rotate(glm::quat(quat), -rec.normal);
    //    scattered.dir = glm::reflect(scattered.dir, -rec.normal);
    //}
    //else
    //{
    //    //float sinb = sina * ir;
    //    //float angle = glm::asin(sinb);
    //    //glm::mat4 quat = glm::rotate(glm::mat4(1), angle, axis);
    //    //scattered.dir = glm::rotate(glm::quat(quat), rec.normal);

    //    scattered.dir = glm::reflect(scattered.dir, rec.normal);
    //}
    //scattered.orig = rec.p;
    //return true;

    attenuation = glm::vec3(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

    glm::vec3 unit_direction = glm::normalize(r_in.direction());
    scattered.dir = glm::normalize(refract(unit_direction, rec.normal, refraction_ratio));
    scattered.orig =  rec.p;
    return true;
}

bool matte::scatter(const ray& r_in, const hit_record& rec, glm::color& attenuation, ray& scattered) const
{
    if (rec.front_face)
    {
        attenuation = albedo;
        scattered.dir = random_hemisphere(rec.normal);
        scattered.orig = rec.p;
    }
    else
    {
        attenuation = glm::vec3(1, 1, 1);
        scattered.dir = r_in.direction();
        scattered.orig = rec.p;
    }
    return true;
}

bool metal::scatter(const ray& r_in, const hit_record& rec, glm::color& attenuation, ray& scattered) const
{
    attenuation = albedo;
    glm::vec3 bounce = glm::reflect(glm::normalize(r_in.direction()), rec.normal);
    glm::vec3 fuzz_vec = random_hemisphere(bounce) * fuzz;
    scattered.dir = bounce + fuzz_vec;
    scattered.orig = rec.p;
    return true;
}

bool smoke::scatter(const ray& r_in, const hit_record& rec, glm::color& attenuation, ray& scattered) const
{
    float len = glm::length(r_in.direction());
    glm::vec3 r_dir = r_in.direction() / len;
    float a = glm::length(glm::cross(rec.normal, r_dir));
    if (rec.front_face)
    {
        attenuation = glm::vec3(1);
        scattered.orig = rec.p + r_dir * 0.0001f;
        scattered.dir = r_dir;
    }
    else
    {
        if (glm::length(r_in.direction() * rec.t) < .01f)
        {
            attenuation = glm::vec3(1);
            scattered.orig = rec.p;
            scattered.dir = r_dir;
        }
        else
        {
            glm::vec3 fuzz_vec = random_hemisphere(r_dir) * .10f;
            glm::vec3 dir = glm::normalize(r_dir);
            attenuation = color;
            scattered.orig = r_in.origin() + dir * .08f;
            scattered.dir = dir;
        }
    }
    return true;
}
