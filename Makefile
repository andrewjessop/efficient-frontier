CPPFLAGS+=-I.
CXXFLAGS+=-g
LDLIBS+=-lhtmlcxx -lcurl

APP=main

OBJS=\
    $(APP).o \
    ParseYahoo.o \
    URLRequest.o \

$(APP): $(OBJS)

process: $(APP) format.sh
	./$(APP) > out.html
	-./format.sh 2>&1 > /dev/null
	gnome-www-browser new.html

debug:
	gdb $(APP) core
clean:
	$(RM) $(APP) core $(OBJS) *.html
