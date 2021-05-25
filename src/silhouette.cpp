#include "ppm_image.h"
#include "AGLM.h"
#include "ray.h"
#include "material.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

using namespace glm;
using namespace agl;

color ray_color(const ray& r, const hittable_list& world, int depth)
{
    hit_record rec;

    if (world.hit(r, 0.001f, infinity, rec))
    {
        return color(1, 0, 0);
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
    float aspect = (float)width / (float)height;

    // Camera
    vec3 camera_pos(0);
    float viewport_height = 2.0f;
    float focal_length = 1.0;
    camera cam(camera_pos, viewport_height, aspect, focal_length);

    shared_ptr<material> matte_test = make_shared<matte>(glm::vec3(.1, 1, .5));

    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5f, matte_test));

    glm::vec3 c1(.9, .9, 1);
    glm::vec3 c2(.4, .4, 1);

    // Ray trace
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            float u = float(i + random_float()) / (width - 1);
            float v = float(height - j - 1 - random_float()) / (height - 1);
            ray r = cam.get_ray(u, v);
            color c = ray_color(r, world, 1);
            image.set_vec3(j, i, c);
        }
    }

    image.save("silhouette.ppm");
}
