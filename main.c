#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

typedef struct
{
  char title[51];
  char autor[51];
  char genre[51];
  int ISBN;
  char location[51];
  char status[51];
  char holder[51];
  List* reserves;
} Libro; // Estructura del libro. Con las variables para sus datos.

void registrarLibro(List* libreria) // Se registra el libro.
{
  Libro* libro = (Libro *) malloc(sizeof(Libro)); // Se asigna la memoria para el libro.
  if (libro == NULL) // Si no se puede asignar la memora
  {
    printf("\nError al reservar memoria");
    exit(EXIT_FAILURE);
  }

  printf("Ingrese el nombre\n"); // Se solicita el nombre del libro.
  scanf(" %50[^\n]", libro->title);

  printf("Ingrese al autor\n"); // Se solicita el autor del libro.
  scanf(" %50[^\n]", libro->autor);
  getchar();

  printf("Ingrese el género\n"); // Se solicita el género del libro.
  scanf(" %50[^\n]", libro->genre);

  printf("Ingrese ISBN\n"); // Se solicita el código del libro.
  scanf(" %d", &libro->ISBN);

  printf("Ingrese ubicación\n"); // Se solicita la ubicación del libro.
  scanf(" %50[^\n]", libro->location);
  
  strcpy(libro->status, "Disponible"); // Se establece el estado del libro en "Disponible" al ser uno nuevo.
  libro->reserves = createList(); // Se crea la lista de reservas del libro.

  pushFront(libreria, libro); // Se añade el libro a la lista.
}

void* LibroEncontrado(List* libreria, const char* title, const char* autor) // Se busca el libro.
{
  Libro* libroActual = firstList(libreria); // Se establece un "auxiliar" para marcar el primer libro de la lista.
  while (libroActual != NULL)
  {
    if (strcmp(libroActual->title, title) == 0 && strcmp(libroActual->autor, autor) == 0) // Si el título y el autor coinciden
    {
      return libroActual; // Se regresa el "nodo" del libro
    }
    libroActual = nextList(libreria); // Si no, se avanza al siguiente.
  }
  return NULL; // En caso de no encontrar coincidente, no se regresa nada.
}

void* reservaEncontrada(List* reserves, const char* nombreReserva) // Se busca la reserva.
{
  char* nombreActual = firstList(reserves); // Se establece un "auxiliar" para marcar la primera reserva del libro.
  while (nombreActual != NULL)
    {
      if (strcmp(nombreActual, nombreReserva) == 0) // Si el nombre coincide
      {
        return nombreActual; // Se retorna el nombre. (Se puede usar cualquiera de las 2 variables).
      }
      nombreActual = nextList(reserves); // Caso contrario, se avanza en los nombres de la lista.
    }
  return NULL; // En caso de no encontrar coincidente, no se regresa nada.
}

void reserves(List* reserves) // Función para imprimir el nombre de las personas que han reservado en el libro.
{
  void* nombreActual = firstList(reserves); //  Se estable el "auxiliar" para el primer nombre de la lista.
  printf("\n");
  while (nombreActual != NULL) // Si hay reservas
    {
      printf("%s\n", (char*)nombreActual); // Se imprime el nombre y se hace un salto de linea.
      nombreActual = nextList(reserves); // Se avanza al siguiente nombre en la lista.
    }
}

void mostrarDatosLibro(List* libreria) // Se busca un libro y se imprimen sus datos.
{
  char tituloBuscado[51];
  char autorBuscado[51];

  printf("Ingrese titulo\n");
  scanf(" %50[^\n]", tituloBuscado);
  printf("Ingrese autor\n");
  scanf(" %50[^\n]", autorBuscado);

  Libro* libro = LibroEncontrado(libreria, tituloBuscado, autorBuscado); // Se busca el libro.
  if (libro != NULL) // Si el libro existe (Está registrado)
  { // Se imprimen los datos
    printf("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    printf("\nDatos del libro");
    printf("\nTítulo: %s ", libro->title);
    printf("\nAutor: %s", libro->autor);
    printf("\nGénero: %s", libro->genre);
    printf("\nISBN: %d", libro->ISBN);
    printf("\nUbicación: %s", libro->location);
    printf("\nEstado: %s\n", libro->status);

    if (strcmp(libro->status, "Disponible") == 0) // Si el estado es "Disponible", la función finaliza
    {
      return;
    }
    if (strcmp(libro->status, "Prestado") == 0) // Si el estado es "Prestado", se imprime el nombre de la persona que lo tiene.
    {
      printf("Prestado a: %s\n", libro->holder);
    }
    if (firstList(libro->reserves) != NULL) // Si hay reservas
    {
    printf("\nReservado por:"); 
    reserves(libro->reserves);
    }
  }
  else
  {
    printf("\nEl libro no está registrado.\n");
  }
}

void mostrarLibros(List* libreria) // Se muestran todos los libros de la lista.
{
  Libro* libroActual = firstList(libreria); // Auxiliar al primer nodo de la lista.
  if (libroActual == NULL) // Si no hay libros.
  {
    printf("\nNo hay libros\n");
    return;
  }

  while (libroActual != NULL) // Si hay libros
    { // Solo se imprime el título, el autor y se avanza al siguiente nodo.
      printf("\nTitulo: %s", libroActual->title);
      printf("\nAutor: %s\n", libroActual->autor);
      libroActual = nextList(libreria);
    }
}

void reservarLibro(List* libreria) // Función para reservar libros.
{
  char tituloReservar[51];
  char autorReservar[51];

  printf("Ingrese titulo\n");
  scanf(" %50[^\n]", tituloReservar);
  printf("Ingrese autor\n");
  scanf(" %50[^\n]", autorReservar);

  Libro* libroReservar = LibroEncontrado(libreria, tituloReservar, autorReservar); // Se busca el libro.

  if (libroReservar != NULL) // Si el libro existe
  {
    char nombre[51];
    printf("\nIngrese el nombre\n"); // Se solicita el nombre
    scanf(" %50[^\n]", nombre);
    if(strcmp(libroReservar->status, "Prestado") != 0) // Si el libro no está prestado, se cambia su estado a reservado.
    {
      strcpy(libroReservar->status, "Reservado");
    }
    pushBack(libroReservar->reserves, strdup(nombre)); // Se añade el nombre al final de la lista
    
    printf("\nReserva Exitosa\n");
  }
}

void cancelarReserva(List* libreria) // Función para cancelar reservas.
{
  char tituloCancelar[51];
  char autorCancelar[51];

  printf("Ingrese titulo\n");
  scanf(" %50[^\n]", tituloCancelar);
  printf("Ingrese autor\n");
  scanf(" %50[^\n]", autorCancelar);

  Libro* libroCancelar = LibroEncontrado(libreria, tituloCancelar, autorCancelar); // Se busca el libro.

  if (libroCancelar != NULL) // Si existe el libro
  {
    char nombre[51];
    printf("\nIngrese el nombre\n");
    scanf(" %50[^\n]", nombre);
    char* reserva = reservaEncontrada(libroCancelar->reserves, nombre); // Se busca el nombre en la lista de reservas.
    if (reserva != NULL) // Si existe la reserva a ese nombre.
    {
      popCurrent(libroCancelar->reserves); // Se elimina de la lista.
      free(reserva); // Se libera su memoria
    }
    if (firstList(libroCancelar->reserves) == NULL && strcmp(libroCancelar->status, "Prestado") != 0) // Si la lista no tiene más reservas y el estado NO es prestado, se actualiza a disponible.
    {
      strcpy(libroCancelar->status, "Disponible");
    }
    printf("\nReserva cancelada\n");
  }
}

void retirarLibro(List* libreria) // Función para retirar un libro.
{
  char tituloRetirar[51];
  char autorRetirar[51];

  printf("Ingrese titulo\n");
  scanf(" %50[^\n]", tituloRetirar);
  printf("Ingrese autor\n");
  scanf(" %50[^\n]", autorRetirar);

  Libro* libroRetirar = LibroEncontrado(libreria, tituloRetirar, autorRetirar); // Se busca el libro.
  if (libroRetirar != NULL) // Si el libro existe
  {
    char nombre[51];
    printf("\nIngrese el nombre\n");
    scanf(" %50[^\n]", nombre);

    if (strcmp(libroRetirar->status, "Disponible") == 0) // Si el estado es disponible
    {
      strcpy(libroRetirar->status, "Prestado"); // Se actualiza a prestado
      strcpy(libroRetirar->holder, nombre); // En el struct, se guarda el nombre de la persona que lo tiene
      printf("\nLibro retirado\n");
      return;
    }
    else if (strcmp(libroRetirar->status, "Reservado") == 0) // Si el estado es reservado
    {
      if (strcmp(firstList(libroRetirar->reserves), nombre) == 0) // Si el nombre coincide con el primero de la lista de reservas
      {
        strcpy(libroRetirar->status, "Prestado"); // Se actualiza el estado a prestado
        strcpy(libroRetirar->holder, nombre); // Se guarda el nombre del estudiante como poseedor del libro.
        popFront(libroRetirar->reserves); // Se elimina de la lista de reservas.
        printf("\nLibro retirado\n");
        return;
      }
    }
    printf("\nEl libro no está disponible o no eres el próximo para retirar\n"); // Si no se cumple ninguna de las 2 condiciones...
  }
}

void devolverLibro(List* libreria) // Función para devolver el libro.
{
  char tituloDevolver[51];
  char autorDevolver[51];

  printf("Ingrese titulo\n");
  scanf(" %50[^\n]", tituloDevolver);
  printf("Ingrese autor\n");
  scanf(" %50[^\n]", autorDevolver);

  Libro* libroDevolver = LibroEncontrado(libreria, tituloDevolver, autorDevolver); // Se busca el libro.
  if (libroDevolver != NULL) // Si el libro existe
  {
    if (firstList(libroDevolver->reserves) == NULL) // Si no tiene reservas, se establece como disponible.
    {
      strcpy(libroDevolver->status, "Disponible");
    }
    else // Si tiene, se establece como reservado.
    {
      strcpy(libroDevolver->status, "Reservado");
    }
    printf("\nEl libro ha regresado a la biblioteca\n");
  }
}

void mostrarPrestados(List* libreria) // Función para mostrar los libros que han sido prestados.
{
  Libro* libroActual = firstList(libreria); // Se va al primer elemento de la lista.
  int cPrestados = 0;
  if (libroActual != NULL) // Si existe una lista de libros.
  {
    while (libroActual != NULL)
      {
        if (strcmp(libroActual->status, "Prestado") == 0) // Si el estado es prestado.
        { // Se imprime el título, el autor y la persona que lo tiene.
          printf("\nTítulo: %s\n", libroActual->title);
          printf("Autor: %s\n", libroActual->autor);
          printf("Prestado a: %s\n", libroActual->holder);
          cPrestados++; // Se aumenta el contador de prestados.
        }
        libroActual = nextList(libreria); // Se avanza al siguiente libro.
      }
  }
  if (cPrestados == 0) // Si no se prestaron libros.
    printf("\nNo se han prestado libros\n");
}

void importar(List* libreria) // Función para importar un archivo.
{
  char nombreArchivo[54];

  printf("\nIngrese el nombre del archivo con la extensión. Tiene que ser un archivo csv\n");
  scanf(" %53[^\n]", nombreArchivo);

  FILE* archivo = fopen(nombreArchivo, "r"); // Se abre el archivo.
  if (archivo != NULL) // Si no hubo problemas para abrir el archivo
  {
    char linea[1024];
    fgets(linea, sizeof(linea), archivo); // Se elimina la linea de categorias del archivo.

    while (fgets(linea, sizeof(linea), archivo) != NULL) // Se avanza linea por linea
      {
        char* newLine = strchr(linea, '\n'); // Se elimina el caracter de salto de linea
        if (newLine != NULL)
        {
          *newLine = '\0';
        }
        if (strlen(linea) == 0) // Se saltan las lineas vacias. Sin esto, se crean espacios en el struct vacios.
        {
          continue;
        }
        
        Libro* libro = (Libro *) malloc(sizeof(Libro)); // Se asigna la memoria para el libro.
        if (libro == NULL)
        {
          printf("\nNo se pudo reservar la memoria para el libro\n");
          exit(EXIT_FAILURE);
        }
        libro->reserves = createList(); // Se crea la lista de reservas del libro

        char* contenido;
        int categoria = 0; // Para ver en que categoria va.

        contenido = strtok(linea, ","); // El separador de categorias en la linea.
        while (contenido != NULL) // Si no se llegó al final de la linea.
          { // Se guarda el título, el autor, el género, el código ISBN, la ubicación, el estado y las reservas que tenga el libro.
            if (categoria == 0) strcpy(libro->title, contenido);
            if (categoria == 1) strcpy(libro->autor, contenido);
            if (categoria == 2) strcpy(libro->genre, contenido);
            if (categoria == 3) libro->ISBN = atoi(contenido);
            if (categoria == 4) strcpy(libro->location, contenido);
            if (categoria == 5) strcpy(libro->status, contenido);
            if (categoria > 5) pushBack(libro->reserves, strdup(contenido));

            contenido = strtok(NULL, ","); // Se avanza a la siguiente palabra.
            categoria++; // Se avanza en la categoria.
          }
        pushFront(libreria, libro); // Se añade el libro a la lista.
      }
    fclose(archivo); // Se cierra el archivo
    printf("\nArchivo importado\n");
  }
  else
  {
    printf("\nNo se pudo abrir el archivo\n");
  }
}

void exportar(List* libreria) // Función para exportar hacia un archivo.
{
  char nombreArchivo[54];
  printf("\nIngresa el nombre del archivo con la extensión. Tiene que ser un archivo csv\n");
  scanf(" %53[^\n]", nombreArchivo);

  FILE* archivo = fopen(nombreArchivo, "w"); // Se abre el archivo
  if (archivo != NULL)
  {
    fprintf(archivo, "Título,Autor,Género,ISBN,Ubicación,Estado,Reservas\n"); // Se crea la linea de categorias del archivo.
    Libro* libroActual = firstList(libreria); // Auxiliar al primer libro de la lista.
    while (libroActual != NULL)
      { // Se añade al archivo, el título, autor, género, código ISBN, estado.
        fprintf(archivo, "%s,", libroActual->title);
        fprintf(archivo, "%s,", libroActual->autor);
        fprintf(archivo, "%s,", libroActual->genre);
        fprintf(archivo, "%d,", libroActual->ISBN);
        fprintf(archivo, "%s", libroActual->status);
        if (strcmp(libroActual->status, "Prestado") == 0) // Si el estado es prestado, se añade el nombre de la persona que lo tiene antes de las reservas.
        {
          fprintf(archivo, ",%s", libroActual->holder);
        }

        char* reserva = firstList(libroActual->reserves); // Auxiliar al primer nombre en reservar.
        while (reserva != NULL)
          {
            fprintf(archivo, ",%s", reserva); // Se añade el nombre.
            reserva = nextList(libroActual->reserves); // Se avanza al siguiente nombre en la lista.
          }
        fprintf(archivo, "\n");
        libroActual = nextList(libreria); // Se avanza al siguiente libro.
      }
    fclose(archivo); // Se cierra el archivo.
    printf("\nDatos exportados\n");
  }
  else
  {
    printf("\nNo hay un archivo para exportar\n");
  }
}

void action(List* libreria, int option) // Función central para llamar al resto de funciones.
{
  printf("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n");
  printf("Haz seleccionado la opción: %d\n", option);

  switch(option)
    {
      case 1:
        registrarLibro(libreria);
        break;
      case 2:
        mostrarDatosLibro(libreria);
        break;
      case 3:
        mostrarLibros(libreria);
        break;
      case 4:
        reservarLibro(libreria);
        break;
      case 5:
        cancelarReserva(libreria);
        break;
      case 6:
        retirarLibro(libreria);
        break;
      case 7:
        devolverLibro(libreria);
        break;
      case 8:
        mostrarPrestados(libreria);
        break;
      case 9:
        importar(libreria);
        break;
      case 10:
        exportar(libreria);
        break;
      
    }
}

int main()
{
  int option = -1;
  List* libreria = createList(); // Se crea la lista.

  while (option != 0) // Mientras la opción no sea "0", el programa continuará
    {
      printf("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
      printf("\nSelecciona una opción:");
      printf("\n");
      printf("\n1.- Registrar libro");
      printf("\n2.- Mostrar datos de libro");
      printf("\n3.- Mostrar todos los libros");
      printf("\n4.- Reservar Libro");
      printf("\n5.- Cancelar reserva de libro");
      printf("\n6.- Retirar libro");
      printf("\n7.- Devolver libro");
      printf("\n8.- Mostrar libros prestados");
      printf("\n9.- Importar libros desde un archivo CSV");
      printf("\n10.- Exportar libros a un archivo CSV");
      printf("\n0.- Para salir del programa");
      printf("\n");
      scanf("%d", &option);
      if (option > 0 && option <= 10) // Si la opción está dentro de los parametros
      {
        action(libreria, option);
      }
      else if (option == 0) // Si la opción es "0", el programa finalizará
      {
        break;
      }
      else // Si no está dentro de los parametros, se solicita nuevamente el ingreso de la opción.
      {
        printf("\nOpción no válida.");
        printf("\nIngrese nuevamente\n");
      }
    }
  printf("Programa finalizado.");
  
  return 0;
}