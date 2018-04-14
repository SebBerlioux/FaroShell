include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/chmod $(FaroShell)/$(binCmd)/$(static)/libchmod.a \
			$(FaroShell)/$(binCmd)/$(shared)/libchmod.so

$(FaroShell)/$(binCmd)/chmod: $(FaroShell)/$(objCmd)/chmod/chmod.o \
		$(FaroShell)/$(objCmd)/chmod/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/chmod $^

$(FaroShell)/$(objCmd)/chmod/%.o: $(FaroShell)/$(src)/$(cmd)/chmod/%.c
	@echo "Building chmod"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/chmod
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libchmod.a: $(FaroShell)/$(objCmd)/chmod/chmod.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libchmod.so: $(FaroShell)/$(objCmd)/chmod/chmod.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
