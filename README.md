La distribución de los contenedores del ejercicio2 es de manera automatica.

Cuando se elige agregar un contenedor la función agreggarContenedor() se
encarga de encontrar automáticamente la primera pila con espacio disponible.

Al retirar un contenedor, los contenedores que están encima del que se retira
se almacenan temporalmente en una pila auxiliar (temp) y luego se colocan de nuevo
en las pilas mediante la función moverContenedores().

Por ejemplo:
Si se tiene 3 pilas con una capacidad máxima de 4 contenedores cada una, y decides
agregar 5 contenedores, ocurrira lo siguiente:
a) el primer contenedor se colocará en la pila 1.
b) el segundo también se colocará en la pila 1, si hay espacio.
c) Cuando la pila 1 esté llena, el siguiente contenedor se colocará en la pila 2, y así 
sucesivamente hasta que todas las pilas estén llenas o no haya más contenedores que agregar.
