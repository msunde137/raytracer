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
    attenuation = albedo;
    glm::vec3 ray_dir = glm::normalize(r_in.direction());
    //scattered.dir = glm::reflect(ray_dir, rec.normal);
    glm::vec3 axis = -glm::cross(ray_dir, rec.normal);
    float angle = glm::acos(glm::dot(rec.normal, -ray_dir));
    glm::mat4 quat = glm::rotate(glm::mat4(1), angle, axis);
    glm::vec3 bounce = glm::rotate(glm::quat(quat), rec.normal);
    scattered.dir = bounce;
    scattered.orig = rec.p;
    return true;
}

bool dielectric::scatter(const ray& r_in, const hit_record& rec, glm::color& attenuation, ray& scattered) const
{
    attenuation = glm::color(1);
    glm::vec3 ray_dir = glm::normalize(r_in.direction());
    glm::vec3 axis = glm::cross(rec.normal, ray_dir);
    float sina = glm::length(axis);
    if (rec.front_face)
    {
        float sinb = sina / ir;
        float angle = glm::asin(sinb);
        glm::mat4 quat = glm::rotate(glm::mat4(1), angle, axis);
        scattered.dir = glm::rotate(glm::quat(quat), -rec.normal);
    }
    else
    {
        float sinb = sina * ir;
        float angle = glm::asin(sinb);
        glm::mat4 quat = glm::rotate(glm::mat4(1), angle, axis);
        scattered.dir = glm::rotate(glm::quat(quat), rec.normal);
    }
    glm::vec3 fuzz_vec = random_hemisphere(scattered.dir) * fuzz;
    scattered.dir = scattered.dir + fuzz_vec;
    scattered.orig = rec.p;
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
    glm::vec3 ray_dir = glm::normalize(r_in.direction());
    glm::vec3 axis = -glm::cross(ray_dir, rec.normal);
    float angle = glm::acos(glm::dot(rec.normal, -ray_dir));
    glm::mat4 quat = glm::rotate(glm::mat4(1), angle, axis);
    glm::vec3 bounce = glm::rotate(glm::quat(quat), rec.normal);
    glm::vec3 fuzz_vec = random_hemisphere(bounce) * fuzz;
    scattered.dir = bounce + fuzz_vec;
    scattered.orig = rec.p;
    return true;
}

bool smoke::scatter(const ray& r_in, const hit_record& rec, glm::color& attenuation, ray& scattered) const
{
    float len = glm::length(r_in.direction());
    glm::vec3 r_dir = r_in.direction() / len;
    glm::vec3 fuzz_vec = random_hemisphere(r_dir) * 1.0f;
    glm::vec3 dir = glm::normalize(r_dir);
    if (rec.front_face)
    {
        attenuation = glm::vec3(1);
        scattered.orig = rec.p;
        scattered.dir = r_dir;
    }
    else
    {
        //if (glm::length(r_in.direction() * rec.t) < .5f)
        //{
        //    attenuation = color;
        //    scattered.orig = rec.p;
        //    scattered.dir = r_dir;
        //}
        //else
        //{
        //}
        attenuation = glm::vec3(0);
        scattered.orig = rec.p;
        scattered.dir = r_in.direction();
    }
    return true;
}
