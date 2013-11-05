# -*- coding: utf-8 -*-

import __builtin__

CR    = chr(13)
LF    = chr(10)
SP    = ' '

#  strs
CRLF  = chr(13) + chr(10)

#  生成常量

constants = {
	'CR':	 (CR, '(char)13'),
	'LF':	 (LF, '(char)10'),
	'SP':	 (SP, "' '"),
}

def gen_const():
	"""生成常量"""
	for (key, (index, val)) in constants.iteritems():
		yield '#define %s %s' % (key, val)

#  ----- 生成快速的strcmp函数 -----

def gen_strcmp_cond(size):
	"""gen_strcmp的子函数，不赘述。"""
	buffer = []
	for i in range(0, size):
		buffer.append('s[%s] == c%s' % (str(i), str(i)))
	return ' && '.join(buffer)

def gen_strcmp_list(size):
	"""gen_strcmp的子函数，不赘述。"""
	buffer = map(
		lambda val: 'c' + str(val),
		range(0, size)
	)
	return ', '.join(buffer)

def gen_strcmp(size):
	"""生成strcmp*函数"""
	for i in range( 1, size+1 ):
		yield '#define strcmp%s(s, %s) %s' \
			 % (str(i), gen_strcmp_list(i), gen_strcmp_cond(i))


#  声明全局变量

__builtin__.gen_const  = gen_const
__builtin__.gen_strcmp = gen_strcmp


