# Esquema
1. [X] Hacer funcion para encontrar ruta del comando a ejecutar
2. [X] Ejecutar el primer comando
	- [X] Crear pipe `pipe1`
	- [X] Hacer un `fork`
		1. Padre se queda esperando a hijo
		2. Hijo:
			- [X] Leer argumentos de `infile`
			- [X] Guardar los argumentos + argumentos del comando en array NULL-terminated
			- [X] Rederigir salida `stdout` a `pipe1` 
			- [X] Ejecutar comando con `execv`

3. [X] Ejecutar el segundo comando
	- [X] Rederigir salida `stdout` a `outfile`
	- [X] Ejecutar `execv` con los argumentos de `pipe1`
<br><br><br>

# Checkeos
1. [X] Gestionar errores del primer comando
2. [X] Gestionar errores del segundo comando
3. [X] Gestionar varios argumentos con comillas (comandos como el `awk` lo necesitan)
4. [X] Cambiar los fds a donde deberían ir
5. [X] Revisar leaks normales 
6. [ ] Norminette
7. [ ] Probar todas las posibles combinaciones de errores, para ver leaks
	- Archivo de entrada no existe
	- Archivo de salida no existe
	- Comando 1 no existe
	- Comando 2 no existe
	- Comando 1 da error al compilar (?)
	- Comando 2 da error al compilar (?)