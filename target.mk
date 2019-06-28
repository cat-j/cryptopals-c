include ../../global.mk


TMP := ../../build/tmp
BIN := ../../build/bin

# Create build directories if they don't exist
.IGNORE: build_dir
.PHONY: build_dir
build_dir:
	@mkdir -p $(TMP)
	@mkdir -p $(BIN)

# Clean build directories 
.IGNORE: clean
.PHONY: clean
clean:
	@$(RM_R) $(TMP)/*
	@$(RM_R) $(BIN)/*

# Static rules
$(TMP)/%.o : %.c
	$(CC) $(CFLAGS) -I$(TOOLS) -L$(TOOLS_LIB) -c $< -o $@