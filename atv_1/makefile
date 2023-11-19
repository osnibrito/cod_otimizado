dyn:
	@gcc ./dynamic/standard_dyn.c -o ./bin/standard_dyn 
	@gcc ./dynamic/unrolling_dyn.c -o ./bin/unrolling_dyn
	@gcc ./dynamic/interchange_dyn.c -o ./bin/interchange_dyn
stc:
	@gcc ./static/standard_static.c -o ./bin/standard_static 
	@gcc ./static/unrolling_static.c -o ./bin/unrolling_static
	@gcc ./static/interchange_static.c -o ./bin/interchange_static

all:
	@make dyn 
	@make stc

clean:
	rm ./bin/*
