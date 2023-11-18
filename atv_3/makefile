
N:=50000000

spectral:
	@gcc ./spectral_norm.c -lm -o ./bin/spectral_norm$(ARGS) $(ARGS)

n_body:
	@gcc ./n_body.c -lm -o ./bin/n_body$(ARGS) $(ARGS)

run_spectral:
	@./bin/spectral_norm$(ARGS)

run_n_body:
	@./bin/n_body$(ARGS) $(N)

clean:
	rm ./bin/*