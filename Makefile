CC = clang
CFLAGS = -Wall -Wextra -Werror -Wthread-safety

all: global pointer requires excludes acquire release overlock underlock overunlock underunlock

pass: 
	$(MAKE) CFLAGS="$(CFLAGS) -DTSA_PASS"

global:
	-$(CC) $(CFLAGS) global.c

pointer:
	-$(CC) $(CFLAGS) pointer.c

requires:
	-$(CC) $(CFLAGS) requires.c

excludes:
	-$(CC) $(CFLAGS) excludes.c

acquire:
	-$(CC) $(CFLAGS) acquire.c

release:
	-$(CC) $(CFLAGS) release.c

overlock:
	-$(CC) $(CFLAGS) overlock.c

underlock:
	-$(CC) $(CFLAGS) underlock.c

overunlock:
	-$(CC) $(CFLAGS) overunlock.c

underunlock:
	-$(CC) $(CFLAGS) underunlock.c

# http://astyle.sourceforge.net/
# The 1TBS is "One True Brace Style", which is K&R
# with the enforced "enbraced" statements after if/while/for.
# It is beautiful.  For the style to work with astyle you need
# at least 1.24 (February 2010).
astyle:
	astyle --style=1tbs *.h *.c

clean:
	$(RM) a.out

