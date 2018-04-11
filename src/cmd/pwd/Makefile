include ../../../Makefile.variables

FaroShell = ../../..

all: objRepo $(FaroShell)/$(bin)/$(cmd)/pwd

objRepo:
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/pwd

$(FaroShell)/$(bin)/$(cmd)/pwd: $(FaroShell)/$(objCmd)/pwd/pwd.o \
		$(FaroShell)/$(objCmd)/pwd/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/pwd $^ $(LDFLAGS)

$(FaroShell)/$(objCmd)/pwd/%.o: $(FaroShell)/$(src)/$(cmd)/pwd/%.c
	@echo "Building pwd"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/pwd
	$(CC) -c -o $@ $< $(CFLAGS)
