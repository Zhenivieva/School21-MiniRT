# MiniRT (*Mini* *R*ay *T*racer)

This 42 school project is a preview of the graphic programming world.  
Here, we learned to compute visibility and color of 3D objects, casting rays
on a 3D scene.



## Installation

We need :
* On Linux : clang/gcc, Xlib (v11) and his extension (already installed on Ubuntu distros)
* On Mac OS : clang/gcc  
(you can change CC value in Makefile to set clang)  

Compile :
```bash
cd miniRT
make
```

## Usage

### GUI mode

The program takes a .rt file. More information about this format below...  
```bash
./miniRT [a format .rt scene file]
```

## USE THREAD 
```
in MAKEFILE
add FLAGS = -D TH="CNT THREAD"
```

## :wrench: BASIC INSTRUCTIONS

Zoom | Translation | Change camera | Rotation
--- | --- | --- | ---
**Move_up** : Zoom in | **W** : Move up | **Arrow left** : Previous camera | **Mouse** : Click on the desire direction you want the camera to look at. 
**Move_down** : Zoom out | **S** : Move down | **Arrow right** : Next camera
 | **A** : Move left  |**X** : Orientir_Back 	|**-** : light plus	|**[** : FOV +
 | **D** : Move right |**N** : Normalizate_cam 	|**+** : light minus	|**]** : FOV -
### BMP mode

You can just save the generated image of scene (RT.bmp) with :  
```bash
./miniRT yourfavoritescene.rt -save
```
**Caution** : this erases precedent RT.bmp  
The output image resolution is no longer limited by your display size in this mode !

### About .rt format

We have to run miniRT with a valid .rt file. Here is an example of valid *(and ugly)* .rt file.  

The school project subject defines how the input file must be formatted.

Each line defines one property or scene object, lines begin with uppercase letter  
mean a unique property and lowercase lines define a scene object:  
- **R** stands for image resolution. Here we have a resolution of 1920x1080
- **A** defines ambient light. It has a light ratio and a rgb code
- **c** places a camera, it is defined by :
	- his position vector
	- his orientation vector (sight-direction)
	- his field of view (FOV) in degrees
- **l** is an omnilight, its properties comprise :
	- a position vector
	- a light-ratio
	- a rgb code
- **pl** is a plane defined by :
	- his position vector
	- his orientation (one of their normals orientation)
	- his rgb color
- **sp** is a sphere, it is defined by :
	- a position vector
	- a diameter
	- an rgb color
- **sq** is a square with :
	- a position vector (one of his vertices)
	- an orientation vector
	- his side size
	- an rgb color
Actually, the subject underdefines the square, so i choose an arbitrary 2nd orientation vector,
and i planned to modify the file format to fix this flaw.
- **cy** places a cylinder with :
	- his position vector (i.e. his base center)
	- his axis orientation vector
	- his diameter
	- his height
- **tr** defines a triangle with his three vertices and his color.

If you want to create a scene, you have to pay attention at :
- vector format : f,f,f ; with f, an arbitrary float 
- rgb format : n,n,n ; with n in range [0,255]
- ratio : f, a float between [-1.0,1.0]
- fov is comprise between [0,180]
- each property must be separated by spaces/tabs

You can write empty lines and object order is meaningless, just don't forget
ambient and resolution. (If you dont like ambient light effect you can deactivate putting a 0 in ratio).

Enjoy !  



# Screen
![This is a alt text.](https://github.com/Zhenivieva/miniRT/blob/main/my_bmp0.bmp)
![This is a alt text.](https://github.com/Zhenivieva/miniRT/blob/main/my_bmp1.bmp)
![This is a alt text.](https://github.com/Zhenivieva/miniRT/blob/main/my_bmp2.bmp)
![This is a alt text.](https://github.com/Zhenivieva/miniRT/blob/main/my_bmp3.bmp)


# miniRT

- 42 Docs MiniLibX:  
https://harm-smits.github.io/42docs/libs/minilibx.html
- Трёхмерная графика с нуля. Часть 1: трассировка лучей:  
https://m.habr.com/ru/post/342510/
- Канонические уравнения поверхностей второго порядка:  
http://mathhelpplanet.com/static.php?p=kanonicheskie-uravneniya-poverhnosti-vtorogo-poryadka  
https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf  
https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/ray-tracing-practical-example
- Рендеринг:  
https://ru.wikipedia.org/wiki/%D0%A0%D0%B5%D0%BD%D0%B4%D0%B5%D1%80%D0%B8%D0%BD%D0%B3
- Рейкастинг:  
https://ru.wikipedia.org/wiki/Ray_casting
- Рейтрейснг:  
https://ru.wikipedia.org/wiki/%D0%A2%D1%80%D0%B0%D1%81%D1%81%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0_%D0%BB%D1%83%D1%87%D0%B5%D0%B9
- Запись картинки в файл:  
https://medium.com/sysf/bits-to-bitmaps-a-simple-walkthrough-of-bmp-image-format-765dc6857393
- Рендер форм( втч цилиндра):  
http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
- Пересечение луча и треугольника:  
https://www.youtube.com/watch?v=fK1RPmF_zjQ&t=164s
- Алгоритм для определения точек пересечения луча с цилиндром:  
https://studopedia.ru/10_216543_algoritm-dlya-opredeleniya-tochek-peresecheniya-lucha-s-tsilindrom.html
- Еще видео по рейтрейсеру фигур:  
https://www.youtube.com/watch?v=Ejpxgrv_9n8
- Создание камеры в OpenGL:  
https://ravesli.com/urok-9-kamera-v-opengl/
- Ray:  
https://www.youtube.com/watch?v=QkETiyYWh2o  
https://github.com/DinoZ1729/Ray
- Статьи по векторам и матрицам:  
Векторное произведение:  
https://ru.wikipedia.org/wiki/%D0%92%D0%B5%D0%BA%D1%82%D0%BE%D1%80%D0%BD%D0%BE%D0%B5_%D0%BF%D1%80%D0%BE%D0%B8%D0%B7%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5  
Обратная матрица:  
https://ru.wikipedia.org/wiki/%D0%9E%D0%B1%D1%80%D0%B0%D1%82%D0%BD%D0%B0%D1%8F_%D0%BC%D0%B0%D1%82%D1%80%D0%B8%D1%86%D0%B0  
Матрица поворота:  
https://ru.wikipedia.org/wiki/%D0%9C%D0%B0%D1%82%D1%80%D0%B8%D1%86%D0%B0_%D0%BF%D0%BE%D0%B2%D0%BE%D1%80%D0%BE%D1%82%D0%B0  
