include ../../../Makefile.variables

FaroShell = ../../..

all: $(FaroShell)/$(binCmd)/chgrp $(FaroShell)/$(binCmd)/$(static)/libchgrp.a \
			$(FaroShell)/$(binCmd)/$(shared)/libchgrp.so

$(FaroShell)/$(binCmd)/chgrp: $(FaroShell)/$(objCmd)/chgrp/chgrp.o \
		$(FaroShell)/$(objCmd)/chgrp/main.o
	$(CC) -o $(FaroShell)/$(bin)/$(cmd)/chgrp $^

$(FaroShell)/$(objCmd)/chgrp/%.o: $(FaroShell)/$(src)/$(cmd)/chgrp/%.c
	@echo "Building chgrp"
	mkdir -p $(FaroShell)/$(obj)/$(cmd)/chgrp
	$(CC) -c -o $@ $< $(CFLAGS)

#Static library
$(FaroShell)/$(binCmd)/$(static)/libchgrp.a: $(FaroShell)/$(objCmd)/chgrp/chgrp.o
	@echo "Making static library $@"
	ar rc $@ $^
	ranlib $@

#Shared library
$(FaroShell)/$(binCmd)/$(shared)/libchgrp.so: $(FaroShell)/$(objCmd)/chgrp/chgrp.o
	@echo "Making shared library $@"
	$(CC) -shared -o $@ $^
