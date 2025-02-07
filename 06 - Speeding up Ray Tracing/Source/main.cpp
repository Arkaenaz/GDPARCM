#include "pch.h"

#include "Threading/RayTracingThread.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "RTImage.h"

using namespace cv;

int main()
{
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

    int spheres = 0;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a / 2 + 0.4 * random_double(), 0.2, b / 2 + 0.4 * random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                spheres++;
            }
        }
    } // Test case 1 and 2

    /*for (int b = 1; b < 11; b++) {
        auto choose_mat = random_double();
        point3 center(0, (float)b / 2.0f, 0);

        if ((center - point3(4, 0.2, 0)).length() > 0.9) {
            shared_ptr<material> sphere_material;

            if (choose_mat < 0.8) {
                // diffuse
                auto albedo = color::random() * color::random();
                sphere_material = make_shared<lambertian>(albedo);
                world.add(make_shared<sphere>(center, 0.2, sphere_material));
            }
            else if (choose_mat < 0.95) {
                // metal
                auto albedo = color::random(0.5, 1);
                auto fuzz = random_double(0, 0.5);
                sphere_material = make_shared<metal>(albedo, fuzz);
                world.add(make_shared<sphere>(center, 0.2, sphere_material));
            }
            else {
                // glass
                sphere_material = make_shared<dielectric>(1.5);
                world.add(make_shared<sphere>(center, 0.2, sphere_material));
            }
            spheres++;
        }
    }*/

    std::cout << spheres << " Spheres added to world" << "\n";

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.5, 0.1, 0.6));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    auto material4 = make_shared<lambertian>(color(1.0, 0.5, 0.1));
    world.add(make_shared<sphere>(point3(-8, 1, 0), 1.0, material4)); // Test Case 1 and 2

    camera cam;

    cam.aspect_ratio = 1.0;
    cam.image_width = 1080;
    //cam.samples_per_pixel = 500;
    cam.samples_per_pixel = 200;
    cam.max_depth = 50;

    cam.vfov = 20;
    //cam.lookfrom = point3(13, 2, 3);
    cam.lookfrom = point3(20, 4, 8);
    cam.lookat = point3(0, 0, 0);// test case 1
    //cam.lookat = point3(4, 1, 0);// test case 2
    //cam.lookat = point3(0, 3, 0);
    cam.vup = vec3(0, 1, 0);

    //cam.defocus_angle = 0.1; // test case 3
    cam.defocus_angle = 0.0;// test case 1
    //cam.defocus_angle = 4; // test case 2
    cam.focus_dist = 10.0;

    cam.render(world);

}