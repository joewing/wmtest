
all: wmtest

wmtest:
	(cd src && $(MAKE) wmtest)

clean:
	(cd src && $(MAKE) clean)


