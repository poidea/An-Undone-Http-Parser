# -*- coding: utf-8 -*-

"""调试"""

import __builtin__

req_buffer = ''

def add_req_line(val):
	global req_buffer
	req_buffer = req_buffer + val + '\\r\\n'

def add_br():
	global req_buffer
	req_buffer = req_buffer + '\\r\\n'


add_req_line('POST http://localhost/ HTTP/1.1')
add_req_line('Host: localhost')
add_req_line('Accept: text/html')
add_br()

add_req_line('test=1&test2=2')
add_br()

req_buffer = req_buffer + '\\0'


def c_main():
	return """
		int main()
		{
			char* text = "%s";
			while ( (int)*text != 0 )
			{
				http_state_machine( *text );
				text++;
			}

			printf("TEST VALUE: %%s\\n", buffer_q_val[0]);
			return 0;
		}

	""" % req_buffer

__builtin__.c_main = c_main


