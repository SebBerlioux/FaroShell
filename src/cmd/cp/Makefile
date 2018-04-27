include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/cp $(FaroShell)/$(binCmd)/$(static)/libcp.a \
			$(FaroShell)/$(binCmd)/$(shared)/libcp.so

$(FaroShell)/$(binCmd)/cp: $(FaroShell)/$(objCmd)/cp/cp.o \
		$(FaroShell)/$(objCmd)/cp/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/cp $^ $(FaroShell)/$(obj)/$(utilsObj)

$(FaroShell)/$(objCmd)/cp/%.o: $(FaroShell)/$(src)/$(cmd)/cp/%.c
	@echo "Building cp"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/cp
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libcp.a: $(FaroShell)/$(objCmd)/cp/cp.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libcp.so: $(FaroShell)/$(objCmd)/cp/cp.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
