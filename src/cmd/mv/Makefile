include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/mv $(FaroShell)/$(binCmd)/$(static)/libmv.a \
			$(FaroShell)/$(binCmd)/$(shared)/libmv.so

$(FaroShell)/$(binCmd)/mv: $(FaroShell)/$(objCmd)/mv/mv.o \
		$(FaroShell)/$(objCmd)/mv/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/mv $^ $(FaroShell)/$(obj)/$(utilsObj)

$(FaroShell)/$(objCmd)/mv/%.o: $(FaroShell)/$(src)/$(cmd)/mv/%.c
	@echo "Building mv"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/mv
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libmv.a: $(FaroShell)/$(objCmd)/mv/mv.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libmv.so: $(FaroShell)/$(objCmd)/mv/mv.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
