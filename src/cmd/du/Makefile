include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/du $(FaroShell)/$(binCmd)/$(static)/libdu.a \
			$(FaroShell)/$(binCmd)/$(shared)/libdu.so

$(FaroShell)/$(binCmd)/du: $(FaroShell)/$(objCmd)/du/du.o \
		$(FaroShell)/$(objCmd)/du/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/du $^ $(FaroShell)/$(obj)/$(utilsObj)

$(FaroShell)/$(objCmd)/du/%.o: $(FaroShell)/$(src)/$(cmd)/du/%.c
	@echo "Building du"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/du
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libdu.a: $(FaroShell)/$(objCmd)/du/du.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libdu.so: $(FaroShell)/$(objCmd)/du/du.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
