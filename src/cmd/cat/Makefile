include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/cat $(FaroShell)/$(binCmd)/$(static)/libcat.a \
			$(FaroShell)/$(binCmd)/$(shared)/libcat.so

$(FaroShell)/$(binCmd)/cat: $(FaroShell)/$(objCmd)/cat/cat.o \
		$(FaroShell)/$(objCmd)/cat/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/cat $^ $(FaroShell)/$(obj)/$(utilsObj)

$(FaroShell)/$(objCmd)/cat/%.o: $(FaroShell)/$(src)/$(cmd)/cat/%.c
	@echo "Building cat"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/cat
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libcat.a: $(FaroShell)/$(objCmd)/cat/cat.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libcat.so: $(FaroShell)/$(objCmd)/cat/cat.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
