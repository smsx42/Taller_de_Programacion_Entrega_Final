# MANUAL DEL PROYECTO
## Distribución
Originalmente, Si bien todo el equipo trabajo en todo el proyecto, distribuimos al equipo en dos subequipos: uno encargado de la parte del cliente, desde su código hasta su interfaz visual y sonidos, mientras que el otro equipo se encargó del lado del servidor, incluyendo desde el manejo de las conexiones y las partidas, hasta el desarrollo y balanceo del juego, así como también del testeo de las partes del mismo.

Por mencionar individualmente:
- Santiago Janon: Renderizado de objetos, cargado de texturas, creacion de sonidos y animaciones
- Tomás Della Vecchia: Lógica del servidor, protocolo, testing e integración.
- Patricio Silva: Lógica de juego, lobby del cliente y editor de mapas.
- Kevin Carbajal: Cliente, creacion y carga de mapa, interfaz del juego y cámara.

## Documentación de apoyo
Para el uso de **SDL** utilizamos las siguientes fuentes

https://lazyfoo.net/tutorials/SDL/

https://github.com/libSDL2pp/libSDL2pp-tutorial

Para **QT**

https://doc.qt.io/qt-5/qtexamplesandtutorials.html

y, por último, para **GTEST**

https://github.com/google/googletest/tree/main/googletest/samples


## Partes problemáticas
### Código
En cuanto al código, la mayor parte de problemas se dio al ponernos de acuerdo con el protocolo de comunicación del cliente-servidor. Fue una parte que tuvo constantes cambios debido a que cada agregado en cualquiera de las dos partes, ya sea un nuevo enemigo, un nuevo mapa, la posibilidad de elegir distintos personajes o partidas, incluía una modificación en el protocolo de comunicación.

### SDL 
La libreria de sdl fue tan vital para el desarrollo del proyecto como problematica. Problemas de inclusión y de instalación de la misma sumado a la inexperiencia en su uso nos llevaron a conflictos que dificultaron el avance.

### Integración
Surgieron algunos inconvenientes debidos a las diferencias de sistemas operativos de los integrantes. Esto llevó a conflictos como el no procesamiento de archivos de audio por su formato o la no visualización de imágenes si no eran de un formato específico; cuestión que, una vez solucionada, volvió a aparecer a la hora de crear el Vagrantfile.

## Errores conocidos
#### Vagrant
Para correr el juego utilizando Vagrant, se recomienda fuertemente utilizar la branch de este repositorio llamada del mismo nombre.
Existe un error en las dependencias del Vagrantfile que no permite hacer testing del proyecto, ni reproduce sonido al utilizar el juego, pero el resto de características del mismo funcionan con normalidad.

#### Colisiones
El sistema de colisiones si bien es funcional, a nuestro parecer toma mucha complejidad a la hora de calcularlas e incluso existe un pequeño error que no calcula bien las colisiones en las formas triangulares.

## ¿Qué cambiaríamos?
En normas generales, sentimos que, pese a los inconvenientes normales surgidos de un trabajo grupal, pudimos lograr con nuestro objetivo, desarrollando todas las features propuestas e incluso llegando a agregar extras.

Perdimos mucho tiempo en refactorizar el código. Tal vez planificarlo de antemano, como para tener el código más prolijo en una primera instancia, nos hubiese venido bien.

Si bien el uso de Github como sistema de control de versiones fue fundamental en el proyecto, tuvimos poca comunicación y eso hizo que, en ciertas circunstancias, pisáramos trabajo realizado por otro integrante, lo que nos llevó a hacer doblemente el trabajo en ciertas ocasiones. Una herramienta de gestión de proyectos como Trello podría habernos solucionado este inconveniente.

Por último, los problemas de integración mencionados arriba hicieron que tuviésemos muchos conflictos que generaron problemas difíciles de resolver, puesto que no estaban bajo nuestro control. Utilizar Docker o incluso Vagrant desde un comienzo pudo habernos ahorrado este inconveniente.
