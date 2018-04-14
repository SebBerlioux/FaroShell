include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/mkdir $(FaroShell)/$(binCmd)/$(static)/libmkdir.a \
			$(FaroShell)/$(binCmd)/$(shared)/libmkdir.so

$(FaroShell)/$(binCmd)/mkdir: $(FaroShell)/$(objCmd)/mkdir/mkdir.o \
		$(FaroShell)/$(objCmd)/mkdir/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/mkdir $^

$(FaroShell)/$(objCmd)/mkdir/%.o: $(FaroShell)/$(src)/$(cmd)/mkdir/%.c
	@echo "Building mkdir"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/mkdir
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libmkdir.a: $(FaroShell)/$(objCmd)/mkdir/mkdir.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libmkdir.so: $(FaroShell)/$(objCmd)/mkdir/mkdir.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
