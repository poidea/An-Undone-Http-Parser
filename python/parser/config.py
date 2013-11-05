# -*- coding: utf-8 -*-

"""自动机逻辑结构的设计文档"""

import __builtin__

class Properties:

	"""属性分为unique, pair
	用来制定在C语言中缓存的类别

	unique:		( length )
	pair:		( length )"""

	def __getitem__(self, name):
		return self.__properties[name]

	def iteritems(self):
		return self.__properties.iteritems()

	def add_unique(self, key, length):
		self.__properties[key] = ('unique', length)

	def add_pair(self, key, length, parent=None):
		"""parent=None表示是完整的key-value pair。
		如果是一个字符串，表示该节点只是key或者pair本身，
		字符串的内容表示key-pair的父结构。"""

		self.__properties[key] = ('pair', length, parent)
		if self.outer.structures.has_key(key):
			for val in self.outer.structures[key]:
				self.__properties[val] = ('pair', length, key)

	def __init__(self, outer):
		self.__properties = {}
		self.outer = outer

		# ----- 可以修改以下属性 ------
		self.add_unique( 'method',     10  )
		self.add_unique( 'path',       256 )
		self.add_unique( 'protocol',   15  )
		self.add_pair  ( 'parameters', 256 )
		self.add_pair  ( 'query_str',  256 )


class Config:

	"""------- 以下是关于参数设置的说明 -------

	<strong>structures</strong> = 对自动机逻辑结构的定义
	比如，header的大框架里分为method, path, protocol这样
	几个小结构。

	<strong>links</strong> = 自动机的转换条件
	状态机节点名称:  (转换条件, 目的状态 ,行为元组)

	<strong>parameters_id</strong> = 对于协议属性的对应常量，用在C语言里可以加速。

	<strong>properties</strong> = 关于属性的说明请看Properties内部类的文档"""

	def __init__(self):
		self.structures = {

			'header':	( 'method', 'path', 'protocol' ),
			'parameters':	( 'p_key',  'p_val',  'break_1' ),
			'query_str':	( 'q_key',  'q_val',  'break_2' )
		}

		self.links = {

			# ----- Header -----

			'method':	[( 'SP',     	'path',      ['record']), \
					 ( '#ELSE_TAG',  None,	     ['save_char'])],

			'path':		[( 'SP',     	'protocol',  ['record']), \
					 ( '#ELSE_TAG',  None,	     ['save_char'])],

			'protocol':	[( '#CRLF',  	'p_key',     ['record']), \
					 ( '#ELSE_TAG',  None,	     ['save_char'])],

			# ----- Parameters -----

			'p_key':	[( "':'",    	'p_val',     ['record']), \
					 ( '#CRLF',	'break_2',   ['record']), \
					 ( "'&'",	'q_key',     ['record'] ), \
					 ( '#ELSE_TAG',  None,	     ['save_char'])],

			'p_val':	[( '#CRLF',  	'break_1',   ['record']), \
					 ( '#ELSE_TAG',  None,	     ['save_char'])],

			'break_1':	[( '#CRLF',     'q_key',     ['do_nothing'] ), \
					 ( '#ELSE_TAG', 'p_key',     ['save_char'] )],

			# ----- Query Strings -----

			'q_key':	[( "'='",    	'q_val',     ['record']), \
					 ( '#ELSE_TAG',  None,	     ['save_char'])],

			'q_val':	[( "'&'",    	'q_key',     ['record']), \
					 ( "#CRLF",	'break_2',   ['record']),
					 ( "#ELSE_TAG",  None,       ['save_char']) ],

			'break_2':	[( "#CRLF",	None,	     ['do_nothing'] )]

		}

		self.properties = Properties(self)


#  声明全局变量

__builtin__.configuration = Config()



