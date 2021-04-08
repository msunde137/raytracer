// Raytracer framework from https://raytracing.github.io by Peter Shirley, 2018-2020
// alinen 2021, modified to use glm and ppm_image class

#include "ppm_image.h"
#include "AGLM.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "camera.h"
#include "material.h"
#include "hittable_list.h"

using namespace glm;
using namespace agl;
using namespace std;

color ray_color(const ray& r, const hittable_list& world, int depth)
{
   hit_record rec;
   if (depth <= 0)
   {
      return color(1, 1, 1);
   }

   if (world.hit(r, 0.001f, infinity, rec))
   {
      ray scattered;
      color attenuation;
      if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      {
         color recurseColor = ray_color(scattered, world, depth - 1);
         return recurseColor * attenuation;
      }
      return attenuation;
   }
   vec3 unit_direction = normalize(r.direction());
   auto t = 0.5f * (unit_direction.y + 1.0f);
   return (1.0f - t) * color(1, 1, 1) + t * color(0.5f, 0.7f, 1.0f);
}

color normalize_color(const color& c, int samples_per_pixel)
{
   // todo: implement me!
   float scale = 1.0f / samples_per_pixel;
   float r = std::min(0.999f, std::max(0.0f, c.r * scale));
   float g = std::min(0.999f, std::max(0.0f, c.g * scale));
   float b = std::min(0.999f, std::max(0.0f, c.b * scale));

   // apply gamma correction 
   r = sqrt(r);
   g = sqrt(g);
   b = sqrt(b);

   return color(r, g, b);
}

void ray_trace(ppm_image& image)
{
   // Image
   int height = image.height();
   int width = image.width();
   float aspect = width / float(height);
   int samples_per_pixel = 2; // higher => more anti-aliasing
   int max_depth = 6; // higher => less shadow acne

   // World
   shared_ptr<material> gray = make_shared<lambertian>(color(0.5f));
   shared_ptr<material> asdf = make_shared<lambertian>(color(1, 1, 0.5f));
   shared_ptr<material> phong_test = make_shared<phong>(
       glm::vec3(0, 1, 0),
       glm::vec3(1, 1, 1),
       glm::vec3(.1, 0, 0),
       glm::vec3(-1, .4, 1),
       glm::vec3(0, 0, 0),
       .5, .5, .5, 20);
   shared_ptr<material> matte_test = make_shared<matte>(glm::vec3(.1, 1, .5));
   shared_ptr<material> matte_test1 = make_shared<matte>(glm::vec3(1, .1, .5));

   shared_ptr<material> metal_test = make_shared<metal>(glm::vec3(1, .1, .1), 0.1);
   shared_ptr<dielectric> glass_test = make_shared<dielectric>(0.9995);
   shared_ptr<smoke> smoke_test = make_shared<smoke>(glm::vec3(.5));

   hittable_list world;
   //world.add(make_shared<sphere>(point3(.5, 0, -1), 0.5f, glass_test));
   world.add(make_shared<sphere>(point3(-.2, 0, -1), 0.5f, smoke_test));
   world.add(make_shared<triangle>(
       glm::vec3(1,  -0.5, -1),
       glm::vec3(0, -0.5,  -1),
       glm::vec3(0,   0.5, -1),
       smoke_test));
   //world.add(make_shared<triangle>(
       //glm::vec3(-10, -.5, 0),
       //glm::vec3(10,  -.5, 0),
       //glm::vec3(0,   -.5, -10),
       //asdf));
   world.add(make_shared<plane>(glm::vec3(0, -.5, 0), glm::vec3(0, 1, 0), gray));
   //world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, asdf));
   
   // Camera
   vec3 camera_pos(0);
   float viewport_height = 2.0f;
   float focal_length = 1.0; 
   camera cam(camera_pos, viewport_height, aspect, focal_length);

   // Ray trace
   for (int j = 0; j < height; j++)
   {
      for (int i = 0; i < width; i++)
      {
         color c(0, 0, 0);
         //if (i == 180 && j == 240) __debugbreak();
         for (int s = 0; s < samples_per_pixel; s++) // antialias
         {
            float u = float(i + random_float()) / (width - 1);
            float v = float(height - j - 1 - random_float()) / (height - 1);

            ray r = cam.get_ray(u, v);
            c += ray_color(r, world, max_depth);
         }
         c = normalize_color(c, samples_per_pixel);
         image.set_vec3(j, i, c);
      }
   }

   image.save("../res/basic.png");
}
