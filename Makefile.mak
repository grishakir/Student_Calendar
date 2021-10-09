TARGET = compile
PROG_NAME = StudentSchedule
PREFIX = ~/ccc/test
vpath %  DateTime SubjectLesson Saves Auxiliary

.PHONY: install uninstall compile user_man in_instruct an_instruct\
	license docs configure all clear_tmp clear_config clear_compile \
	clear remove remove_all

compile: $(PROG_NAME)

$(PROG_NAME): Saves.o Auxiliary.o DateTime.o SubjectLesson.o main.o
	gcc Saves.o Auxiliary.o DateTime.o SubjectLesson.o main.o -o $(PROG_NAME) -lm
Saves.o: Saves.c Saves.h
	gcc -c Saves.c -lm
Auxiliary.o: Auxiliary.c Auxiliary.h
	gcc -c Auxiliary.c -lm
DateTime.o: DateTime.c DateTime.h
	gcc -c DateTime.c -lm
SubjectLesson.o: SubjectLesson.c SubjectLesson.h
	gcc -c SubjectLesson.c -lm
main.o: main.c
	gcc -c main.c -lm
	
user_man:

in_instruct:

an_instruct:

license:
	pdflatex license.tex
docs:
	user_man in_instruct license
configure:

install:
	install $(PROG_NAME) $(PREFIX)
all:
	compile docs configure
clear_tmp:
	rm *.o
clear_config:
	
clear_compile:
	clear_tmp
clear:
	clear_tmp clear_config
uninstall:
	
remove:

remove_all:


	
	
	

