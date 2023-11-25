# Esquema
1. [ ] Ejecutar el primer comando
	- [ ] Crear pipe `pipe1`
	- [ ] Hacer un `fork`
		1. Padre se queda esperando a hijo
		2. Hijo:
			- [ ] Rederigir entrada `stdin` a `infile`
			- [ ] Leer todo el contenido del archivo `infile` 
			- [ ] Rederigir salida `stdout` a `pipe1` 
			- [ ] Ejecutar comando con `execv`

2. [ ] Ejecutar el segundo comando
	- [ ] Rederigir salida `stdout` a `outfile`
	- [ ] Ejecutar `execv` con los argumentos de `pipe1`
