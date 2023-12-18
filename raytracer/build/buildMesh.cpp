#include "../cameras/Perspective.hpp"


#include "../geometry/Sphere.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/Jittered.hpp"

#include "../materials/Matte.hpp"
#include "../materials/Phong.hpp"

#include "../utilities/Point3D.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"

#include "../lights/Ambient.hpp"
#include "../lights/Point.hpp"

#include "../world/World.hpp"

#include "../acceleration/BVH.hpp"

#include "../tracer/Basic.hpp"
#include "../tracer/Shadow.hpp"

void World::build(void) {
    // view plane
    vplane.top_left = Point3D(-20, 20, 20);
    vplane.bottom_right = Point3D(20, -20, 20);
    vplane.hres = 480;
    vplane.vres = 480;
    // vplane.set_maxdepth(5);

    // Background color.
      bg_color = black;

    RGBColor brown(0.71, 0.40, 0.16);  // brown
    RGBColor lightGreen(0.65, 1, 0.30);
    RGBColor lightPurple(0.65, 0.3, 1);

    // camera and sampler.
    set_camera(new Perspective(0, 0, 50));
    // set_tracer(new Basic(this));
    sampler_ptr = new Jittered(camera_ptr, &vplane,5);

	Matte* matte_ptr = new Matte;
	matte_ptr->set_ka(0.45);
	matte_ptr->set_kd(0.75);
	matte_ptr->set_diffuse_color(white);   // grey rockets

	float ka = 0.75;
	float kd = 0.75;
	float ks = 0.1;
	float e = 20.0;
	float kr = 1.0;

	Phong* phong_ptr = new Phong;
	phong_ptr->set_ka(ka);
	phong_ptr->set_kd(kd);
	// phong_ptr->set_cd(white);    		// white
	phong_ptr->set_ks(ks);
	phong_ptr->set_exp(e);
	// phong_ptr->set_kr(kr);

	srand(2);

	for (int i = 0; i < 150; i++){
        float offsetX = (-30) + (rand() % static_cast<int>(35 - (-30) + 1));;
        float offsetY = (-30) + (rand() % static_cast<int>(35 - (-30) + 1));
        Sphere* sphere_ptr = new Sphere(Point3D(offsetX, offsetY, -0.5), 0.25);
        sphere_ptr->set_material(phong_ptr);
        add_geometry(sphere_ptr);
	}

  RGBColor yellow = RGBColor(0.7, 0.7, 0.08); 

	Phong* phong_ptr1 = new Phong;
	phong_ptr1->set_ka(ka);
	phong_ptr1->set_kd(kd);
	phong_ptr1->set_ks(ks);
	phong_ptr1->set_diffuse_color(yellow);    	// yellow
	phong_ptr1->set_exp(e);
	// phong_ptr1->set_kr(kr);

	Sphere* sphere_ptr1 = new Sphere(Point3D(15.0, 18, 10.0), 4.866);
	sphere_ptr1->set_material(phong_ptr1);
	add_geometry(sphere_ptr1);

	Phong* phong_ptr2 = new Phong;
	phong_ptr2->set_ka(ka);
	phong_ptr2->set_kd(kd);
	phong_ptr2->set_diffuse_color(RGBColor(.8, 0.018, 0.164));     	// red
	phong_ptr2->set_ks(ks);
	phong_ptr2->set_exp(e);
	// phong_ptr2->set_kr(kr);

	Sphere* sphere_ptr2 = new Sphere(Point3D(10, -8, -0.5), 4.2);
	sphere_ptr2->set_material(phong_ptr2);
	add_geometry(sphere_ptr2);

	Phong* phong_ptr3 = new Phong;
	phong_ptr3->set_ka(ka);
	phong_ptr3->set_kd(kd);
	phong_ptr3->set_diffuse_color(RGBColor(.094, 0.7, 0.843));    		// blue
	phong_ptr3->set_ks(ks);
	phong_ptr3->set_exp(e);
	// phong_ptr3->set_kr(kr);

	Sphere* sphere_ptr3 = new Sphere(Point3D(-5, 8, -0.5), 5.866);
	sphere_ptr3->set_material(phong_ptr3);
	add_geometry(sphere_ptr3);

	Phong* phong_ptr4 = new Phong;
	phong_ptr4->set_ka(ka);
	phong_ptr4->set_kd(kd);
	phong_ptr4->set_diffuse_color(RGBColor(0.7,0,0.54));    		//purple
	phong_ptr4->set_ks(ks);
	phong_ptr4->set_exp(e);
	// phong_ptr4->set_kr(kr);

	Sphere* sphere_ptr4 = new Sphere(Point3D(-22, 22, -0.5), 4.866);
	sphere_ptr4->set_material(phong_ptr4);
	add_geometry(sphere_ptr4);

	//Mesh models
    add_mesh("3dmodels/babar_azam.ply", matte_ptr, Point3D(-25, -25, -10), Point3D(-15, -10, 10));

    // add_object("monke.obj", matte_ptr);

    //Lighting
	// Ambient* ambient_ptr = new Ambient(white,0.5);
	// ambient_ptr->scale_radiance(0.5);
  ambient_ptr = new Ambient(white, 0.5);
	// set_ambient_light(ambient_ptr);

	Point* light_ptr = new Point(Point3D(0,0,20));
	// light_ptr->set_position(0, 0, 20);
	// light_ptr->scale_radiance(20.0);
	add_light(light_ptr);

	Point* light_ptr2 = new Point(Point3D(0,0,0));
	// light_ptr2->set_position(0, 0, 0);
	// light_ptr2->scale_radiance(20.0);
	add_light(light_ptr2);

	Point* light_ptr3 = new Point(Point3D(-20, 18, 10));
	// light_ptr3->set_position(-20, 18, 10);
	// light_ptr3->scale_radiance(20.0);
	add_light(light_ptr3);

	// acceleration
	set_acceleration(new BVH(this));

	// set_tracer
	set_tracer(new Shadow(this));
}
