# coop

Un ejemplo de como **NO** programar en C. Aunque muestra algunos conceptos de programacion orientada a objetos.

El programa registra citas y consultas para un consultorio, cada Doctor debe de logearse primero. Claro los usuarios y contraseñas estan en el archivo usuario.txt

### C Object Oriented Programming

**Crear objetos**

Para crear un objeto usa la siguiente sintaxis
```
Clase objeto = clase_new();
```

Ejemplo
```
Paciente *paciente = paciente_new();
```

**Acceder a metodos**

Para acceder a los metodos de un objeto usa la siguiente sintaxis
```
$(objeto).metodo(argumentos);
```

Ejemplo
```
$(paciente).setNombre("Jorge");
```

**¿Como funciona esto?**

Tenemos una estructura donde definimos los atributos y una referencia a Class_vt, una "virtual table" la cual contiene una referencia a todos los metodos de la clase;

struct Class {
	//... atributos
	Class_vt class vt; // tabla de punteros a funciones
}

struct Class_vt {
	void (*setThis) (Paciente *);
	void (*setNombre) (const char *);
}

Los metodos usan una variable global llamada ``this`` para saber quien los llamo.

Cuando usamos la macro ``$(objeto)``
Se expande a ``((objeto->vt->setThis(objeto)), *(objeto->vt))``
Lo cual hace dos cosas:
 1. Llama al metodo setThis de nuestra tabla de punteros a metodos y llama a setThis()
 2. Desreferencia la tabla de punteros a metodos.


## Probar 

En linux solamenente

1. Descargar el binario aqui
2. Ejecutar

### Compilar

1. Clonar el repositorio o descargar como zip.
```
git clone https://github.com/alfr3dosv/coop.git
```
2. Abrir una consola y selecccionar la carpeta raiz del proyecto.

3. Ejecutar ``make``.

Los binarios estaran en la carpeta build.