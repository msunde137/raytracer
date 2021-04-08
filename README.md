![basic](https://user-images.githubusercontent.com/54864515/113961779-91de2000-97f4-11eb-8b31-c580af8ac2cb.png)
![reflections](https://user-images.githubusercontent.com/54864515/113961780-9276b680-97f4-11eb-97e2-f6d5c86bed04.png)
![reflections1](https://user-images.githubusercontent.com/54864515/113961781-9276b680-97f4-11eb-94fd-f3714b88ddb6.png)
# raytracer

Implements a raytracer based on the book [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html). 

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
raytracer $ mkdir build
raytracer $ cd build
raytracer/build $ cmake -G "Visual Studio 16 2019" ..
raytracer/build $ start CS312-Raytracer.sln
```

Your solution file should contain multiple projects, such as `gradient` and `normals`.
To run from the git bash command shell, 

```
raytracer/build $ ../bin/Debug/gradient
raytracer/build $ ../bin/Debug/normals
```

*macOS*

Open terminal to the directory containing this repository.

```
raytracer $ mkdir build
raytracer $ cd build
raytracer/build $ cmake ..
raytracer/build $ make
```

To run each program from build, you would type

```
raytracer/build $ ../bin/gradient
raytracer/build $ ../bin/normals
```

