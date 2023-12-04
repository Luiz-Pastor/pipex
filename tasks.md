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

# Falta
1. [X] Gestionar errores del primer comando
2. [X] Gestionar errores del segundo comando
3. [X] Gestionar varios argumentos con comillas (comandos como el `awk` lo necesitan)
5. [ ] Cambiar los fds a donde deberían ir
6. [ ] Revisar leaks (probar todas las posibles combinaciones)
7. [ ] Norminette