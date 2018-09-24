# MPointers
MPointers es un proyecto cuya finalidad es diseñar e implementar clases que encapsulen el uso de punteros en C++. Con este proyecto además será posible aplicar conceptos de manejo de memoria, investigar y desarrollar una aplicación en el lenguaje de programación C++, investigar acerca de programación orientada a objetos en C++ y aplicar patrones de diseño en la solución de un problema.

## Descripción del problema
El proyecto consiste en el diseño e implementación de un nuevo tipo de dato en C++ denominado `MPointer`. `MPointer` es una clase template (`MPointer<T>`) que encapsula un puntero. En el proyecto se implementa una biblioteca para `MPointer` que pueda ser utilizada por cualquier programador para el desarrollo de una aplicación en C++. Se sobrecargan operadores como, `&` y `*` para `MPointer`. Además, el proyecto se realiza en dos iteraciones.

### Primera iteración:  encapsulamiento de punteros de C++
`MPointer<T>` tiene al menos un atributo de tipo `T*`. El programador que utiliza la biblioteca, crea un nuevo `MPointer` de la siguiente manera:

```c++
MPointer<int> myPtr = MPointer<int>::New();
```

En este caso, aparte de reservar la memoria para `MPointer`, también se reserva la memoria para almacenar un `int`. Posteriormente, el programador puede almacenar el dato deseado utilizando:

```c++
*myPtr = 5;
```

En este caso, el operador `*` es sobrecargado y se almacena el valor `5` en el espacio reservado para un `int`. De la misma forma, si se desea obtener el valor guardado en `myPtr`, el programador haría lo siguiente:

```c++
int valor = &myPtr;
```

El operador `=` debe verificar el tipo de los operandos. Si ambos son `MPointer`, copia el puntero y el id de `MPointer` dentro del `MPointerGC` (más sobre esto adelante).

```c++
MPointer<int> myPtr = MPointer<int>::New();
MPointer<int> myPtr2 = MPointer<int>::New();
*myPtr = 5;
myPtr2 = myPtr; //Deja en myPtr2 una referencia a la misma dirección de memoria donde está 5 y copia el id
```

Ahora bien, si el operando de la derecha es de tipo distinto a `MPointer`, se verifica si el tipo es el mismo a lo interno de `MPointer`. De ser así se guarda el valor en el puntero interno:

```c++
myPtr = 6; // es equivalente a *myPtr = 6
```

El operador `&` se sobrecarga y se obtiene el valor guardado. `MPointer` tiene un destructor que se encarga de liberar la memoria del pointer guardado internamente. `MPointer` no requiere de ningún runtime especial. Sin embargo, antes de usar `MPointer`, el programador debe inicializar la clase singleton `MPointerGC` que se ejecuta como un thread cada n segundos. Cada vez que se llama el método `New` de `MPointer`, se guarda la dirección de memoria de la instancia de `MPointer` dentro de la clase `MPointerGC`. Con respecto a `MPointerGC` es importante tomar en cuenta lo siguiente:

* `MPointerGC` tiene una lista enlazada donde guarda direcciones de memoria de los MPointer conocidos.
* `MPointerGC` le da a la instancia de `MPointer`, un Id autogenerado.
* El destructor de `MPointer` llama a `MPointerGC` para indicar que la referencia se ha destruido. Una vez que el conteo de referencias de un `MPointer` llegue a cero, el `MPointerGC` lo libera, evitando memory leaks.
* Para probar la funcionalidad de `MPointer`, se implementará `QuickSort`, `BubbleSort` e `InsertionSort` utilizando listas doblemente enlazadas que utilizan `MPointers` internamente.

### Segunda iteración: memoria distribuida
En esta iteración, se tendrá memoria distribuida, de la siguiente forma:

![Server](/Enunciado/server.png)

En esta modalidad, la biblioteca MPointers se usa de la siguiente forma:
1. El server se inicia, pasando como parámetro la cantidad de bytes que debe reservar. El server hace un único `malloc` y guarda la referencia al inicio de la memoria reservada.
2. El programador llama a `MPointer_init` pasando como parámetro el IP y puerto donde está el servidor
3. Cuando el programador llama al método `New` de `MPointer`, en vez de hacer `malloc` para el dato, va a enviar un mensaje al servidor solicitando memoria para almacenar el dato: 
    ```c++
    MPointer<int> myPtr = MPointer<int>::New();
    ```
    ----> Envía mensaje al server en JSON indicando que reserve el espacio en el heap del server.
    <---- El server envía un id que se almacena internamente en `MPointer`. Este Id se utilizará posteriormente para leer o escribir memoria.
4. El servidor cuando recibe una solicitud de creación de memoria, utiliza el mapa de memoria para encontrar un espacio en el heap y crea una nueva entrada en el mapa de memoria.
5. Cuando el programador asigna un valor al `MPointer`, se envia un mensaje al server indicando que salve el valor en memoria:
    ```c++
    *myPtr = 5;
    ```
    ----> Se envía un mensaje al server indicando que se actualice la memoria. MPointer almacena el id que se envia al server junto con el dato por guardar.
    El server busca en el mapa de memoria el id indicado. Luego hace un desplazamiento en el heap y guarda el dato.

## Planificación y administración del proyecto
Todos los aspectos referentes a la planificación y administración del proyecto se pueden encontrar en la sección de [proyectos](https://github.com/edmobe/MPointers/projects) de este repositorio.

## Diagrama de clases
![Diagrama](/Enunciado/diagrama.jpeg)

## Estructuras de datos desarrolladas
### Listas doblemente enlazadas
Se utilizan listas doblemente enlazadas para probar el funcionamiento de `MPointer` así como para el manejo de pedidos de cada cliente con el servidor.

### Matrices
Se utilizó una matriz para mapear la memoria que se utiliza para guardar información en el servidor.

## Algoritmos desarrollados
### Algoritmos de ordenamiento
Se utilizan  `QuickSort`, `BubbleSort` e `InsertionSort` para verificar el funcionamiento de `MPointer` con listas doblemente enlazadas.

## Problemas encontrados
Todos los aspectos referentes a los problemas encontrados se pueden encontrar en la sección de [issues](https://github.com/edmobe/MPointers/issues) de este repositorio.