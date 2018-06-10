# snake-io

## Compilation

Le projet étant multi-plateforme voici les instructions concernant les plateformes Windows et Linux.

#### Requiert pour compiler:

##### Windows

[mingw64](https://sourceforge.net/projects/mingw-w64/)  
[CMake](https://cmake.org/)  
[Les modules FindSDL2](https://github.com/tcbrindle/sdl2-cmake-scripts) pour CMake a déposer dans le dossier d'installer de CMake,
comme dans l'exemple qui suit.
> C:\Program Files\CMake\share\cmake-3.11\Modules

[CLion](https://www.jetbrains.com/clion/)  
L'IDE utilisé pour ce projet ce qui pourrait simplifié l'utilisation de CMake.


Compilation via le [CMakeLists](CMakeLists.txt) proposé.

##### Unix
 
Les paquets et (leurs dépendances) suivantes:

libsdl2-dev  
libsdl2-image-dev  
libsdl2-mixer-dev  
libsdl2-ttf-dev  
zlib1g-dev  
libpng-dev

Compilation via le [Makefile](Makefile) proposé.

> make

Pour compiler.

> make clean

Pour effacer les binaires.

> make cclean

Pour effacer les binaires et l'executable.

#### Requiert pour executer:

##### Windows

Les dlls (binaires) dans le dossier où se trouve snake_io.exe:  
libfreetype-6.dll  
limpg123-0.dll  
libpng16-16.dll  
SDL2.dll  
SDL2_image.dll  
SDL2_mixer.dll  
SDL2_ttf.dll  
zlib1.dll  

##### Unix (seul a été testé Ubuntu (Budgie))

Les paquets et (leurs dépendances) suivantes:

libsdl2-2.0.0  
libsdl2-image-2.0.0  
libsdl2-mixer-2.0.0  
libsdl2-ttf-2.0.0

A noter qu'il faut executer l'application depuis le dossier /bin sans quoi rien ne se passe.  
> xxx/snake-io/bin $ ./snake-io