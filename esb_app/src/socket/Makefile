OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
libl = -I/usr/include/libxml2 -lxml2
libm = `mysql_config --cflags --libs`
libt = -lpthread
cflags = gcc -c  -Wall -std=gnu11
VPATH = ../db_access : ../bmd_extract : ../adapter
#INCLUDE := ../db_access
myprog : check_data_location.o get_processing_attempts.o change_processing_attempts.o \
get_active_route_id.o fetch_transform_config_key_and_value.o fetch_transport_config_key_and_value.o \
update_esb_request.o xml_parser.o validate_bmd_request.o socket.o check_id_in_transform_config.o \
check_id_in_transport_config.o insert_into_esb_request.o check_status.o convert_to_json_file.o
	gcc -o myprog $^ $(libt) $(libm) $(libl)
socket.o : socket.c xml.h connector.h
	$(cflags) $< $(libt) $(libm) $(libl)
validate_bmd_request.o : validate_bmd_request.c xml.h
	$(cflags) $< $(libl)
xml_parser.o  : xml_parser.c xml.h
	$(cflags) $< $(libl)
update_esb_request.o : update_esb_request.c connector.h
	$(cflags) $< $(libm)
fetch_transport_config_key_and_value.o : fetch_transport_config_key_and_value.c connector.h
	$(cflags) $< $(libm);
fetch_transform_config_key_and_value.o : fetch_transform_config_key_and_value.c connector.h
	$(cflags) $< $(libm)
get_active_route_id.o : get_active_route_id.c connector.h
	$(cflags) $< $(libm)
change_processing_attempts.o : change_processing_attempts.c connector.h
	$(cflags) $< $(libm)
get_processing_attempts.o : get_processing_attempts.c connector.h
	$(cflags) $< $(libm)
check_data_location.o : check_data_location.c connector.h
	$(cflags) $< $(libm)
check_id_in_transform_config.o : check_id_in_transform_config.c connector.h
	$(cflags) $< $(libm)
insert_into_esb_request.o : insert_into_esb_request.c connector.h
	$(cflags) $< $(libm)
check_id_in_transport_config.o : check_id_in_transport_config.c connector.h
	$(cflags) $< $(libm)
check_status.o : check_status.c connector.h
	$(cflags) $< $(libm)
convert_to_json_file.o : convert_to_json_file.c adapter.h
	$(cflags) $< $(libl)
.PHONEY : clean
clean :
	rm myprog *.o
