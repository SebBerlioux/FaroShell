include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/pwd $(FaroShell)/$(binCmd)/$(static)/libpwd.a \
			$(FaroShell)/$(binCmd)/$(shared)/libpwd.so

$(FaroShell)/$(binCmd)/pwd: $(FaroShell)/$(objCmd)/pwd/pwd.o \
		$(FaroShell)/$(objCmd)/pwd/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/pwd $^

$(FaroShell)/$(objCmd)/pwd/%.o: $(FaroShell)/$(src)/$(cmd)/pwd/%.c
	@echo "Building pwd"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/pwd
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libpwd.a: $(FaroShell)/$(objCmd)/pwd/pwd.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libpwd.so: $(FaroShell)/$(objCmd)/pwd/pwd.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
