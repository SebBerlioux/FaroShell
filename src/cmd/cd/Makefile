include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/cd $(FaroShell)/$(binCmd)/$(static)/libcd.a \
			$(FaroShell)/$(binCmd)/$(shared)/libcd.so

$(FaroShell)/$(binCmd)/cd: $(FaroShell)/$(objCmd)/cd/cd.o \
		$(FaroShell)/$(objCmd)/cd/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/cd $^

$(FaroShell)/$(objCmd)/cd/%.o: $(FaroShell)/$(src)/$(cmd)/cd/%.c
	@echo "Building cd"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/cd
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libcd.a: $(FaroShell)/$(objCmd)/cd/cd.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libcd.so: $(FaroShell)/$(objCmd)/cd/cd.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
