include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/echo $(FaroShell)/$(binCmd)/$(static)/echo.a

$(FaroShell)/$(binCmd)/echo: $(FaroShell)/$(objCmd)/echo/echo.o \
		$(FaroShell)/$(objCmd)/echo/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/echo $^ $(LDFLAGS)

$(FaroShell)/$(objCmd)/echo/%.o: $(FaroShell)/$(src)/$(cmd)/echo/%.c
	@echo "Building echo"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/echo
	$(CC) -c -o $@ $< $(CFLAGS)

$(FaroShell)/$(binCmd)/$(static)/echo.a:
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@
