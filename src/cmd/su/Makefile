include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/su $(FaroShell)/$(binCmd)/$(static)/libsu.a \
			$(FaroShell)/$(binCmd)/$(shared)/libsu.so

$(FaroShell)/$(binCmd)/su: $(FaroShell)/$(objCmd)/su/su.o \
		$(FaroShell)/$(objCmd)/su/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/su $^ $(C99FLAG)

$(FaroShell)/$(objCmd)/su/%.o: $(FaroShell)/$(src)/$(cmd)/su/%.c
	@echo "Building su"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/su
	$(CC) -c -o $@ $< $(CFLAGS) $(C99FLAG)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libsu.a: $(FaroShell)/$(objCmd)/su/su.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libsu.so: $(FaroShell)/$(objCmd)/su/su.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
