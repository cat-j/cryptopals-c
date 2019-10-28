INCLUDE=include/

INC_DIRS=utils/
INC_PARAMS=$(foreach d, $(INC_DIRS), -I$(INCLUDE)$d)