# Esquema
1. [X] Hacer funcion para encontrar ruta del comando a ejecutar
1. [ ] Ejecutar el primer comando
	- [X] Crear pipe `pipe1`
	- [X] Hacer un `fork`
		1. Padre se queda esperando a hijo
		2. Hijo:
			- [ ] Leer argumentos de `infile`
			- [ ] Guardar los argumentos + argumentos del comando en array NULL-terminated
			- [ ] Rederigir salida `stdout` a `pipe1` 
			- [ ] Ejecutar comando con `execv`

2. [ ] Ejecutar el segundo comando
	- [ ] Rederigir salida `stdout` a `outfile`
	- [ ] Ejecutar `execv` con los argumentos de `pipe1`
