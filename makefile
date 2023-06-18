trabalhopratico2 : trabalhopratico2.o my_date.o medico.o paciente.o consulta.o
	gcc -o trabalhopratico2 trabalhopratico2.o my_date.o medico.o paciente.o consulta.o
	
trabalhopratico2.o: trabalhopratico2.c medico.h paciente.h consulta.h
	gcc -c trabalhopratico2.c

medico.o: medico.c medico.h
	gcc -c medico.c
	
paciente.o: paciente.c paciente.h
	gcc -c paciente.c

consulta.o: consulta.c consulta.h medico.h paciente.h my_date.h
	gcc -c consulta.c
	
my_date.o: my_date.c my_date.h
	gcc -c my_date.c
