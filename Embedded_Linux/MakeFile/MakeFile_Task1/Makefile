#variable name to configure the compiler we are using (could be changed if a different target)
cc=gcc
#the includes files location in case we did not include them in the source file
INCS= -I ./include/calc.h
#the name of the output executable file which will run
filename= build/project.out

#Variable for the location of the source file
Sources=src/calc.c


#We will loop or iterate on the source files which are in (Sources) /src and use the
#function patsubst to change it to object files in /bin directory
#here we have only one file with *.c but if we have more than one file in ./src
#it will generate all *.o in the /bin
Objects=$(foreach file, $(Sources), $(patsubst src/%.c, bin/%.o, $(file)))


#the first rule and we take advantage of the first rule only is being executed if we write "make"
#so we make this being executed frirst and this will get the whole job done
all: $(filename)


#here we have this rule which will compile every .c in /src as pre requiste
# file into object file .o as target which are in /bin
bin/%.o: src/%.c
	$(cc) $(INCS) -c $< -o $@


#After we get the object file from the foreach function we will get it as pre requisite
#and the target will be the file name which is the exceutable file
#which will be gererated in /build
$(filename): $(Objects)
	$(cc) $(INCS) $^ -o $@




#Phony Tareget to easily remove the output files
.PHONY: clean
clean:
	@rm -f bin/*.o $(filename)
	@echo "Files Removed"

