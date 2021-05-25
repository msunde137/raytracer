#include <iostream>
#include "ppm_image.h"
#include "AGLM.h"
#include "ray.h"

using namespace glm;
using namespace agl;
using namespace std;

color ray_color(const ray& ray)
{
   return color(0);
}

void ray_trace(ppm_image& image)
{
   int height = image.height();
   int width = image.width();
   glm::vec3 c1(.9, .9, 1);
   glm::vec3 c2(.4, .4, 1);

   for (int i = 0; i < height; i++)
   {
	   for (int j = 0; j < width; j++)
	   {
		   ppm_pixel p = {
			   unsigned char(((float)i * -(c2.x - c1.x) / (float)height + c2.x) * 255.0f),
			   unsigned char(((float)i * -(c2.y - c1.y) / (float)height + c2.y) * 255.0f),
			   unsigned char(((float)i * -(c2.z - c1.z) / (float)height + c2.z) * 255.0f)
		   };
		   image.set(i, j, p);
	   }
   }

   image.save("gradient.png");
}
