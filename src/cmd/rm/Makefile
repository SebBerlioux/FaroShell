include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/rm $(FaroShell)/$(binCmd)/$(static)/librm.a \
			$(FaroShell)/$(binCmd)/$(shared)/librm.so

$(FaroShell)/$(binCmd)/rm: $(FaroShell)/$(objCmd)/rm/rm.o \
		$(FaroShell)/$(objCmd)/rm/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/rm $^ $(FaroShell)/$(obj)/$(utilsObj)

$(FaroShell)/$(objCmd)/rm/%.o: $(FaroShell)/$(src)/$(cmd)/rm/%.c
	@echo "Building rm"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/rm
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/librm.a: $(FaroShell)/$(objCmd)/rm/rm.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/librm.so: $(FaroShell)/$(objCmd)/rm/rm.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
