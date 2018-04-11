include ../../../Makefile.variables

FaroShell = ../../..

all: objRepo $(FaroShell)/$(bin)/$(cmd)/echo

objRepo:
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/echo

$(FaroShell)/$(bin)/$(cmd)/echo: $(FaroShell)/$(objCmd)/echo/echo.o \
		$(FaroShell)/$(objCmd)/echo/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/echo $^ $(LDFLAGS)

$(FaroShell)/$(objCmd)/echo/%.o: $(FaroShell)/$(src)/$(cmd)/echo/%.c
	@echo "Building echo"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/echo
	$(CC) -c -o $@ $< $(CFLAGS)
