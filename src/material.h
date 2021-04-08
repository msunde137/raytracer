#ifndef MATERIAL_H
#define MATERIAL_H

#include <cmath>
#include "AGLM.h"
#include "ray.h"
#include "hittable.h"

class material {
public:
  virtual bool scatter(const ray& r_in, const hit_record& rec, 
     glm::color& attenuation, ray& scattered) const = 0;
  virtual ~material() {}
};

class lambertian : public material {
public:
  lambertian(const glm::color& a) : albedo(a) {}

  virtual bool scatter(const ray& r_in, const hit_record& rec,
      glm::color& attenuation, ray& scattered) const override;

public:
  glm::color albedo;
};

class matte : public material {
public:
  matte(const glm::color& a) : albedo(a) {}

  virtual bool scatter(const ray& r_in, const hit_record& rec,
      glm::color& attenuation, ray& scattered) const override;

public:
  glm::color albedo;
};

class phong : public material {
public:
  phong(const glm::vec3& view) :
     diffuseColor(0,0,1), 
     specColor(1,1,1),
     ambientColor(.01f, .01f, .01f),
     lightPos(5,5,0),
     viewPos(view), 
     kd(0.45), ks(0.45), ka(0.1), shininess(10.0) 
  {}

  phong(const glm::color& idiffuseColor, 
        const glm::color& ispecColor,
        const glm::color& iambientColor,
        const glm::point3& ilightPos, 
        const glm::point3& iviewPos, 
        float ikd, float iks, float ika, float ishininess) : 
     diffuseColor(idiffuseColor), 
     specColor(ispecColor),
     ambientColor(iambientColor),
     lightPos(ilightPos),
     viewPos(iviewPos), kd(ikd), ks(iks), ka(ika), shininess(ishininess) 
  {}

  virtual bool scatter(const ray& r_in, const hit_record& hit,
      glm::color& attenuation, ray& scattered) const override;

public:
  glm::color diffuseColor;
  glm::color specColor;
  glm::color ambientColor;
  glm::point3 lightPos;
  glm::point3 viewPos; 
  float kd; 
  float ks;
  float ka; 
  float shininess;
};

class metal : public material {
public:
    metal(const glm::color& a, float f) : albedo(a), fuzz(f) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec,
        glm::color& attenuation, ray& scattered) const override;

public:
    glm::color albedo;
    float fuzz;
};


class dielectric : public material {
public:
  dielectric(float index_of_refraction) : ir(index_of_refraction) {}

  virtual bool scatter(const ray& r_in, const hit_record& rec,
      glm::color& attenuation, ray& scattered) const override;

public:
  float ir; // Index of Refraction
  float fuzz = 0;
};

class smoke : public material {
public:
    smoke(glm::vec3 c) : color(c) {}

    virtual bool scatter(const ray& r_in, const hit_record& rec,
        glm::color& attenuation, ray& scattered) const override;

public:
    glm::vec3 color;
};

#endif

