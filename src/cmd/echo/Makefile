include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/echo $(FaroShell)/$(binCmd)/$(static)/libecho.a \
			$(FaroShell)/$(binCmd)/$(shared)/libecho.so

$(FaroShell)/$(binCmd)/echo: $(FaroShell)/$(objCmd)/echo/echo.o \
		$(FaroShell)/$(objCmd)/echo/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/echo $^ $(FaroShell)/$(obj)/$(utilsObj)

$(FaroShell)/$(objCmd)/echo/%.o: $(FaroShell)/$(src)/$(cmd)/echo/%.c
	@echo "Building echo"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/echo
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libecho.a: $(FaroShell)/$(objCmd)/echo/echo.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libecho.so: $(FaroShell)/$(objCmd)/echo/echo.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
