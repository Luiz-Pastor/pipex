# Esquema
1. [X] Hacer funcion para encontrar ruta del comando a ejecutar
1. [ ] Ejecutar el primer comando
	- [X] Crear pipe `pipe1`
	- [X] Hacer un `fork`
		1. Padre se queda esperando a hijo
		2. Hijo:
			- [X] Leer argumentos de `infile`
			- [X] Guardar los argumentos + argumentos del comando en array NULL-terminated
			- [X] Rederigir salida `stdout` a `pipe1` 
			- [X] Ejecutar comando con `execv`

2. [X] Ejecutar el segundo comando
	- [X] Rederigir salida `stdout` a `outfile`
	- [X] Ejecutar `execv` con los argumentos de `pipe1`

# Falta
1. [ ] Gestionar errores del primer comando
2. [ ] Gestionar errores del segundo comando