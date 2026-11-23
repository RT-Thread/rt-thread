CC ?= cc
CFLAGS ?= -std=c99 -O1 -g -Wall -Wextra \
          -Wno-unused-function -Wno-unused-parameter -Wno-pointer-to-int-cast
CPPFLAGS += -I mock

BIN := dhcpd_lease_test

.PHONY: all run clean

all: run

$(BIN): test_dhcpd_lease.c ../dhcp_server_raw.c mock/mock_lwip.h
	$(CC) $(CFLAGS) $(CPPFLAGS) test_dhcpd_lease.c -o $(BIN)

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN)