include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/ls $(FaroShell)/$(binCmd)/$(static)/libls.a \
			$(FaroShell)/$(binCmd)/$(shared)/libls.so

$(FaroShell)/$(binCmd)/ls: $(FaroShell)/$(objCmd)/ls/ls.o \
		$(FaroShell)/$(objCmd)/ls/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/ls $^

$(FaroShell)/$(objCmd)/ls/%.o: $(FaroShell)/$(src)/$(cmd)/ls/%.c
	@echo "Building ls"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/ls
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libls.a: $(FaroShell)/$(objCmd)/ls/ls.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libls.so: $(FaroShell)/$(objCmd)/ls/ls.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
