#tengo un pdf con todas las imagenes que se llama Resultados_hw3.pdf

Resultados_hw3.pdf : Resultados_hw3.tex Ondas_30.pdf Orbitas.pdf
	pdflatex Resultados_hw3.tex

Ondas_30.pdf : Onda.py
	python Onda.py 

Orbitas.pdf : Plots_Planetas.py
	python Plots_Planetas.py


Plots_Planetas.py : datos.txt Planetas.x
	./Planetas.x > datos.txt 

Planetas.x : Planetas.c
	cc Planetas.c -o Planetas.x -lm

