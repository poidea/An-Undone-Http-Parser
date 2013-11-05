# -*- coding: utf-8 -*-

"""储存静态内容的文档"""

import __builtin__

incs = """
	#include <stdio.h>
	#include <string.h>
"""

static_code = """

	char buffer[4096];
	int  buffer_len = 0;
	
	int  stat     = stat_method;

	void init_buffer(int size)
	{
		buffer[0] = 0;
		buffer_len = 0;
	}

	void add_buffer(char ch)
	{
		buffer[buffer_len++] = ch;
	}

	void clear_buffer()
	{
		buffer[0] = 0;
		buffer_len = 0;
	}
"""

__builtin__.incs        = incs
__builtin__.static_code = static_code





